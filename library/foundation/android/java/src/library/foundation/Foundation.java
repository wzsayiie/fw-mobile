package src.library.foundation;

public class Foundation {

    public static void cq_log_info(String file, int line, String message) {
        L.i("%s", message);
    }

    public static void cq_log_error(String file, int line, String message) {
        L.e("%s", message);
    }
}
