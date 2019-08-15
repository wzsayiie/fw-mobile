package src.app.components.services;

import android.content.ComponentName;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;

import src.app.com.ServiceHelper;
import src.library.foundation.L;

public class TaskServiceAdapter {

    private static class Singleton {
        static TaskServiceAdapter instance = new TaskServiceAdapter();
    }
    public static TaskServiceAdapter get() {
        return Singleton.instance;
    }

    private ServiceConnection mConnection;
    private ITaskService mITaskService;

    public void startupIfNeeded() {
        if (mConnection != null) {
            L.i("the task service was already running");
            return;
        }

        L.i("startup task service");
        mConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName component, IBinder binder) {
                L.i("task service is connected");
                mITaskService = ITaskService.Stub.asInterface(binder);
                initializeConnection();

            }
            @Override
            public void onServiceDisconnected(ComponentName component) {
                L.i("task service is disconnected");
                mITaskService = null;
            }
        };

        boolean serviceExists = ServiceHelper.get().startServiceIfNeeded(TaskService.class);
        if (serviceExists) {
            ServiceHelper.get().bindService(TaskService.class, mConnection);
        }
    }

    public void shutdown() {
        if (mConnection == null) {
            L.i("the task service was already stop");
            return;
        }

        L.i("shutdown task service");
        ServiceHelper.get().unbindService(mConnection);
        ServiceHelper.get().stopService(TaskService.class);
        mConnection = null;
    }

    protected void initializeConnection() {
        ITaskServiceAdapter switcher = new ITaskServiceAdapter.Stub() {
            @Override
            public void onMakeTaskFinished() {
                TaskServiceAdapter.this.onMakeTaskFinished();
            }
        };

        try {
            setCallbackAdapter(switcher);
        } catch (Exception e) {
            L.e("%s", e.toString());
        }
    }

    //task service's interfaces:

    public void setCallbackAdapter(ITaskServiceAdapter adapter) throws RemoteException {
        if (mITaskService == null) {
            L.e("service interface if null");
            return;
        }

        mITaskService.setCallbackAdapter(adapter);
    }

    public void makeTask() throws RemoteException {
        if (mITaskService == null) {
            L.e("service interface if null");
            return;
        }

        mITaskService.makeTask();
    }

    //interfaces needed by task service:

    protected void onMakeTaskFinished() {
        L.i("onTaskFinished");
    }
}
