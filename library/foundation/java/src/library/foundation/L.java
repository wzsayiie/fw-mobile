package src.library.foundation;

import android.util.Log;

public class L {

    public static void i(String f, Object... a) { info (null, 0, formalize(f, a)); }
    public static void e(String f, Object... a) { error(null, 0, formalize(f, a)); }

    public static String string(Object object) {
        if (object != null) {
            String name = object.getClass().getSimpleName();
            int hash = object.hashCode();
            return name + "@" + hash;
        } else {
            return "@";
        }
    }

    private static String formalize(String format, Object[] args) {
        try {
            return String.format(format, args);
        } catch (Exception e) {
            return "EXCEPTION OUTPUT";
        }
    }

    public static void info (String file, int line, String message) { Log.i("zzz", message); }
    public static void error(String file, int line, String message) { Log.e("zzz", message); }
}
