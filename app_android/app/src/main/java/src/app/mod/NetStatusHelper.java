package src.app.mod;

public class NetStatusHelper {

    private static class Singleton {
        static NetStatusHelper instance = new NetStatusHelper();
    }
    public static NetStatusHelper get() {
        return Singleton.instance;
    }

    public static final String ACTION_NET_STATUS_CHANGED = "src.app.mod.NetStatusHelper.ACTION_NET_STATUS_CHANGED";
    public static final String EXTRA_INT_NET_STATUS = "netStatus";
    public static final String EXTRA_STRING_IPV4 = "ipv4";
    public static final String EXTRA_STRING_IPV6 = "ipv6";

    public static final int NET_STATUS_NONE = 0;
    public static final int NET_STATUS_WWAN = 1;
    public static final int NET_STATUS_WiFi = 2;

    private int mNetStatus;
    private String mIPv4;
    private String mIPv6;

    private NetStatusHelper() {
    }

    public int getNetStatus() {
        return mNetStatus;
    }

    public String getIPv4() {
        return mIPv4;
    }

    public String getIPv6() {
        return mIPv6;
    }
}
