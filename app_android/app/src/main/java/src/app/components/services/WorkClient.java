package src.app.components.services;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;

import src.app.com.ServiceHelper;
import src.library.foundation.L;

public class WorkClient implements ServiceConnection {

    private static class Singleton {
        static WorkClient instance = new WorkClient();
    }
    public static WorkClient get() {
        return Singleton.instance;
    }

    public void connectServiceIfNeeded() {
        if (mServicePort != null) {
            L.i("the work service was already connected");
            return;
        }

        L.i("connect work service");
        ServiceHelper.get().startServiceIfNeeded(WorkService.class);
        ServiceHelper.get().bindService(WorkService.class, this);
    }

    public void disconnectService() {
        if (mServicePort == null) {
            L.i("the work service was already disconnected");
            return;
        }

        L.i("disconnect work service");
        ServiceHelper.get().unbindService(this);
        ServiceHelper.get().stopService(WorkService.class);
    }

    @Override
    public void onServiceConnected(ComponentName component, IBinder binder) {
        L.i("work service is connected");

        try {
            mServicePort = IWorkServicePort.Stub.asInterface(binder);
            mServicePort.setClientPort(mClientPort);
        } catch (RemoteException e) {
            L.e("%s", e.toString());
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName component) {
        L.i("work service is disconnected");

        mServicePort = null;
    }

    public IWorkServicePort getServicePort() {
        return mServicePort;
    }

    private IWorkServicePort mServicePort;
    private IWorkClientPort mClientPort = new IWorkClientPort.Stub() {

        @Override
        public void onAlphaFinished() {
        }

        @Override
        public void onBetaFinished() {
        }
    };
}
