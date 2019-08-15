package src.app.components.services;

import android.app.Application;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.support.v4.app.NotificationCompat;

import src.app.boot.AppWrapper;
import src.library.foundation.L;

public class TaskService extends Service {

    private ITaskServiceAdapter mIAdapter;

    @Override
    public void onCreate() {
        super.onCreate();
        L.i("task service onCreate");

        //since Android 8.0 (api 26), service must display a notification
        //let users known it exists.
        startForegroundNotification();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        L.i("task service onStartCommand");

        //if this service exist abnormally, doest not restart automatically.
        return START_NOT_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        L.i("task service onBind");

        //if there are multiple remote contexts bind to this service,
        //consider that keeping implementation of stub.
        return new ITaskService.Stub() {
            @Override
            public void setCallbackAdapter(ITaskServiceAdapter adapter) {
                TaskService.this.setCallbackAdapter(adapter);
            }
            @Override
            public void makeTask() {
                TaskService.this.makeTask();
            }
        };
    }

    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
        L.i("task service onRebind");
    }

    @Override
    public boolean onUnbind(Intent intent) {
        boolean callRebindOnNext = super.onUnbind(intent);
        L.i("task service onUnbind");

        mIAdapter = null;

        return callRebindOnNext;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        L.i("task service onDestroy");
    }

    protected void startForegroundNotification() {

        Application app = AppWrapper.getApp();
        NotificationManager manager = (NotificationManager) app.getSystemService(Context.NOTIFICATION_SERVICE);

        //since Android 8.0 (api 26), channel is necessary.
        if (Build.VERSION.SDK_INT >= 26) {
            NotificationChannel channel = new NotificationChannel(
                "channel_id", "channel_name", NotificationManager.IMPORTANCE_DEFAULT
            );
            manager.createNotificationChannel(channel);
        }

        NotificationCompat.Builder builder = new NotificationCompat.Builder(app, "channel_id");
        builder.setSmallIcon(android.R.drawable.stat_notify_chat);
        builder.setContentTitle("Task");
        builder.setContentText("Task notification from task service");

        Notification notification = builder.build();
        startForeground(1, notification);
    }

    //interfaces need to implement:

    protected void setCallbackAdapter(ITaskServiceAdapter adapter) {
        if (adapter == null) {
            L.i("set null adapter interface");
        }

        mIAdapter = adapter;
    }

    protected void makeTask() {
        L.i("makeTask");

        try {
            mIAdapter.onMakeTaskFinished();
        } catch (Exception e) {
            L.e("%s", e.toString());
        }
    }
}
