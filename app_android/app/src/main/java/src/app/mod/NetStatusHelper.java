package src.app.mod;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.NetworkRequest;
import android.os.Build;
import android.os.Bundle;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Collections;
import java.util.List;

import src.app.boot.AppWrapper;
import src.library.basis.StringUtil;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class NetStatusHelper {

    private static class Singleton {
        static NetStatusHelper instance = new NetStatusHelper();
    }
    public static NetStatusHelper get() {
        return Singleton.instance;
    }

    public static final String ACTION_NET_STATUS_CHANGED = (
        "src.app.mod.NetStatusHelper.ACTION_NET_STATUS_CHANGED"
    );
    public static final String EXTRA_INT_NET_STATUS      = "netStatus";
    public static final String EXTRA_STR_IPV4            = "ipv4";
    public static final String EXTRA_STR_IPV6_LINK_LOCAL = "ipv6LinkLocal";

    public static final int NET_STATUS_NONE = 0;
    public static final int NET_STATUS_CELL = 1;
    public static final int NET_STATUS_WIFI = 2;

    public static String StringFromNetStatus(int netStatus) {
        switch (netStatus) {
            case NET_STATUS_NONE: return "NetStatusNone";
            case NET_STATUS_CELL: return "NetStatusCell";
            case NET_STATUS_WIFI: return "NetStatusWiFi";
            default: {
                return "UnknownNetStatus:" + netStatus;
            }
        }
    }

    //Android only keeps one available network adapter,
    //cellular network and wifi are not are available at the same time.

    private int    mNetStatus;
    private String mIPv4;
    private String mIPv6LinkLocal;

    private NetStatusHelper() {

        //get current status.
        resetNetStatus();
        resetIPString();

        L.i("net status helper startup {");
        L.i("  status: %s", StringFromNetStatus(mNetStatus));
        L.i("  ipv4: %s", mIPv4);
        L.i("  ipv6 link local: %s", mIPv6LinkLocal);
        L.i("}");

        //set listener.
        if (Build.VERSION.SDK_INT >= AndroidVersion.LOLLIPOP_5_API_21) {

            NetworkRequest.Builder b = new NetworkRequest.Builder();
            b.addTransportType(NetworkCapabilities.TRANSPORT_CELLULAR);
            b.addTransportType(NetworkCapabilities.TRANSPORT_WIFI);

            ConnectivityManager m = (ConnectivityManager) AppWrapper.getApp().getSystemService(
                Context.CONNECTIVITY_SERVICE
            );
            m.registerNetworkCallback(b.build(), new ConnectivityManager.NetworkCallback() {
                @Override
                public void onAvailable(Network network) {
                    onNetStatusChanged();
                }
                @Override
                public void onLost(Network network) {
                    onNetStatusChanged();
                }
            });

        } else {

            IntentFilter filter = new IntentFilter();
            filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);

            BroadcastAssist.register(filter, new BroadcastReceiver() {
                @Override
                public void onReceive(Context context, Intent intent) {
                    onNetStatusChanged();
                }
            });
        }
    }

    public int getNetStatus() {
        return mNetStatus;
    }

    public String getIPv4() {
        return mIPv4;
    }

    public String getIPv6LinkLocal() {
        return mIPv6LinkLocal;
    }

    private void onNetStatusChanged() {

        //NOTE: when the network is changed from wifi to cellular (or cellular to wifi),
        //intermediate state of "no network connection" appears possibly.
        //try skip this state.
        TaskHelper.get().runOnMainThread(400, this::onNetStatusChangedDelay);
    }

    private void onNetStatusChangedDelay() {

        int netStatus = mNetStatus;
        String ipv4 = mIPv4;
        String ipv6LinkLocal = mIPv6LinkLocal;

        resetNetStatus();
        resetIPString();

        if (netStatus != mNetStatus
         || StringUtil.isNotEqual(ipv4, mIPv4)
         || StringUtil.isNotEqual(ipv6LinkLocal, mIPv6LinkLocal))
        {
            L.i("net status changed {");
            L.i("  status: %s", StringFromNetStatus(mNetStatus));
            L.i("  ipv4: %s", mIPv4);
            L.i("  ipv6 link local: %s", mIPv6LinkLocal);
            L.i("}");

            Bundle extras = new Bundle();
            extras.putInt(EXTRA_INT_NET_STATUS, mNetStatus);
            extras.putString(EXTRA_STR_IPV4, mIPv4);
            extras.putString(EXTRA_STR_IPV6_LINK_LOCAL, mIPv6LinkLocal);

            BroadcastAssist.send(ACTION_NET_STATUS_CHANGED, extras);
        }
    }

    private void resetNetStatus() {
        ConnectivityManager manager = (ConnectivityManager) AppWrapper.getApp().getSystemService(
            Context.CONNECTIVITY_SERVICE
        );
        NetworkInfo info = manager.getActiveNetworkInfo();
        if (info != null && info.isConnected()) {
            switch (info.getType()) {
                case ConnectivityManager.TYPE_MOBILE: mNetStatus = NET_STATUS_CELL; break;
                case ConnectivityManager.TYPE_WIFI  : mNetStatus = NET_STATUS_WIFI; break;
                default /* ...................... */: mNetStatus = NET_STATUS_NONE;
            }
        } else {
            mNetStatus = NET_STATUS_NONE;
        }
    }

    private void resetIPString() {
        mIPv4 = null;
        mIPv6LinkLocal = null;

        NetworkInterface networkInterface = null;
        try {
            //NOTE: resetIPString() depends mNetStatus.
            String interfaceName;
            switch (mNetStatus) {
                case NET_STATUS_CELL: interfaceName = "rmnet0"; break;
                case NET_STATUS_WIFI: interfaceName = "wlan0" ; break;
                default: return;
            }

            List<NetworkInterface> interfaces = Collections.list(
                NetworkInterface.getNetworkInterfaces()
            );
            for (NetworkInterface it : interfaces) {
                if (it.getDisplayName().equals(interfaceName)) {
                    networkInterface = it;
                    break;
                }
            }
            if (networkInterface == null) {
                return;
            }

        } catch (SocketException e) {
            L.e("%s", e.toString());
            return;
        }

        List<InetAddress> addresses = Collections.list(
            networkInterface.getInetAddresses()
        );
        for (InetAddress it : addresses) {
            if ((it instanceof Inet6Address) && it.isLinkLocalAddress()) {
                String ipv6LinkLocal = it.getHostAddress();
                int end = ipv6LinkLocal.indexOf('%');
                if (end > 0) {
                    mIPv6LinkLocal = ipv6LinkLocal.substring(0, end);
                } else {
                    mIPv6LinkLocal = ipv6LinkLocal;
                }
            } else if (it instanceof Inet4Address) {
                mIPv4 = it.getHostAddress();
            }
        }
    }
}
