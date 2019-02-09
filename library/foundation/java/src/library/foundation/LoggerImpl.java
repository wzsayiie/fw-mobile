package src.library.foundation;

import android.util.Log;

class LoggerImpl extends Logger {

    public static void info(String message, String file, int line) {
        Log.i("zzz", message);
    }

    public static void error(String message, String file, int line) {
        Log.e("zzz", message);
    }
}
