package src.library.foundation;

public class L {

    public static void i(String format, Object... args) {
        String message = formalize(format, args);
        Logger.info(message, null, 0);
    }

    public static void e(String format, Object... args) {
        String message = formalize(format, args);
        Logger.error(message, null, 0);
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
