package src.library.foundation;

import android.util.Log;

class LoggerImpl extends Logger {

    private static Logger sInfoLogger;

    public static Logger infoLogger() {
        if (sInfoLogger == null) {
            sInfoLogger = new LoggerImpl(Log.INFO);
        }
        return sInfoLogger;
    }

    private static Logger sErrorLogger;

    public static Logger errorLogger() {
        if (sErrorLogger == null) {
            sErrorLogger = new LoggerImpl(Log.ERROR);
        }
        return sErrorLogger;
    }

    private int mLevel;

    private LoggerImpl(int level) {
        mLevel = level;
    }

    @Override
    public void print(String message) {
        if (message == null) {
            return;
        }

        if (mLevel == Log.INFO) {
            Log.i("zzz", message);
        } else if (mLevel == Log.ERROR) {
            Log.e("zzz", message);
        }
    }
}
