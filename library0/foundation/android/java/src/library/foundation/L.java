package src.library.foundation;

import android.util.Log;

import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class L {

    private static String formalize(String format, Object[] args) {
        try {
            return String.format(format, args);
        } catch (Exception e) {
            return "EXCEPTION OUTPUT";
        }
    }

    private static String merge(String file, int line, String message) {
        if (!StringUtil.isEmpty(file) && line > 0) {
            //get file name from path.
            file = file.substring(file.lastIndexOf("/") + 1);

            Object[] args = new Object[]{file, line, message};
            return formalize("%s|%04d|%s", args);

        } else {
            return message;
        }
    }

    public static void info(String file, int line, String message) {
        Log.i("zzz", merge(file, line, message));
    }

    public static void error(String file, int line, String message) {
        Log.e("zzz", merge(file, line, message));
    }

    public static void i(String format, Object... args) {
        StackTraceElement frame = Thread.currentThread().getStackTrace()[3];
        String file = frame.getFileName();
        int line = frame.getLineNumber();

        L.info(file, line, formalize(format, args));
    }

    public static void e(String format, Object... args) {
        StackTraceElement frame = Thread.currentThread().getStackTrace()[3];
        String file = frame.getFileName();
        int line = frame.getLineNumber();

        L.error(file, line, formalize(format, args));
    }

    public static String string(Object object) {
        if (object != null) {
            String name = object.getClass().getSimpleName();
            int hash = object.hashCode();
            return name + "@" + hash;
        } else {
            return "@";
        }
    }
}
