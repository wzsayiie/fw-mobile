package src.app.host.cpp;

import android.app.Application;

import src.library.foundation.L;

public class CPPApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        L.i("host: application create()");
    }
}
