package src.app.host.lua;

import android.app.Application;

import src.library.foundation.L;

public class LuaApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        L.i("Android Host: Application onCreate");
    }
}
