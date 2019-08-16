package src.app.mod;

import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;

import src.app.boot.AppWrapper;
import src.library.foundation.L;

public class BroadcastAssist {

    public static BroadcastReceiver register(IntentFilter filter, BroadcastReceiver receiver) {
        if (filter == null) {
            L.e("do not specify intent needed to listen");
            return null;
        }
        if (receiver == null) {
            L.e("try listen broadcast but receiver is null");
            return null;
        }

        AppWrapper.getApp().registerReceiver(receiver, filter);
        return receiver;
    }

    public static void unregister(BroadcastReceiver receiver) {
        if (receiver == null) {
            L.e("try unregister a null broadcast receiver");
            return;
        }

        AppWrapper.getApp().unregisterReceiver(receiver);
    }

    public static void send(String action, Bundle extras) {
        if (action == null) {
            L.e("try send a broadcast but action is null");
            return;
        }

        Intent intent = new Intent();
        intent.setAction(action);
        if (extras != null) {
            intent.putExtras(extras);
        }

        AppWrapper.getApp().sendBroadcast(intent);
    }
}
