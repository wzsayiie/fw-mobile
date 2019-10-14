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

import androidx.core.app.NotificationCompat;

import src.app.boot.AppWrapper;
import src.app.mod.AndroidVersion;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class WorkService extends Service {

    @Override
    public void onCreate() {
        super.onCreate();
        L.i("work service onCreate");

        //since Android 8.0 (api 26), service must display a notification
        //let users known it exists.
        startForegroundNotification();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        L.i("work service onStartCommand");

        //if this service exist abnormally, doest not restart automatically.
        return START_NOT_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        L.i("work service onBind");

        return mServicePort;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        boolean callRebindOnNext = super.onUnbind(intent);
        L.i("work service onUnbind");

        //reset client instance.
        mClientPort = null;

        return callRebindOnNext;
    }

    @Override
    public void onRebind(Intent intent) {
        super.onRebind(intent);
        L.i("work service onRebind");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        L.i("work service onDestroy");
    }

    protected void startForegroundNotification() {

        Application app = AppWrapper.getApp();
        NotificationManager manager = (NotificationManager) app.getSystemService(
            Context.NOTIFICATION_SERVICE
        );

        //since Android 8.0 channel is necessary.
        if (Build.VERSION.SDK_INT >= AndroidVersion.O_8_API_26) {
            NotificationChannel channel = new NotificationChannel(
                "channel_id", "channel_name", NotificationManager.IMPORTANCE_DEFAULT
            );
            if (manager != null) {
                manager.createNotificationChannel(channel);
            }
        }

        NotificationCompat.Builder builder = new NotificationCompat.Builder(app, "channel_id");
        builder.setSmallIcon(android.R.drawable.stat_notify_chat);
        builder.setContentTitle("Task");
        builder.setContentText("Task notification from work service");

        Notification notification = builder.build();
        startForeground(1, notification);
    }

    private IWorkClientPort mClientPort;
    private IWorkServicePort.Stub mServicePort = new IWorkServicePort.Stub() {

        @Override
        public void setClientPort(IWorkClientPort client) {
            mClientPort = client;
        }

        @Override
        public void makeAlpha() {
        }

        @Override
        public void makeBeta() {
        }
    };
}
