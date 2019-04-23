package src.library.foundation;

import android.util.Log;

public class L {

    public static void i(String format, Object... args) {
        Log.i("zzz", formalize(format, args));
    }

    public static void e(String format, Object... args) {
        Log.e("zzz", formalize(format, args));
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

    private static String formalize(String format, Object[] args) {
        try {
            return String.format(format, args);
        } catch (Exception e) {
            return "EXCEPTION OUTPUT";
        }
    }
}
