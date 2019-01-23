package src.app.utility.application;

import src.library.foundation.Logger;

public class L {

    //NOTE: these static member designed for thread safe.

    public static void i(String format, Object... args) {
        String message = formalize(format, args);
        Logger.info(message);
    }

    public static void e(String format, Object... args) {
        String message = formalize(format, args);
        Logger.error(message);
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
