package src.library.foundation;

import android.util.Log;

class LoggerImpl extends Logger {

    private static Logger sInfo;

    public static Logger info() {
        if (sInfo == null) {
            sInfo = new LoggerImpl(Log.INFO);
        }
        return sInfo;
    }

    private static Logger sError;

    public static Logger error() {
        if (sError == null) {
            sError = new LoggerImpl(Log.ERROR);
        }
        return sError;
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
