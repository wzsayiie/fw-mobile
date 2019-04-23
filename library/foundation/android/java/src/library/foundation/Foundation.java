package src.library.foundation;

public class Foundation {

    public void cq_log_info(String file, int line, String message) {
        L.i("%s", message);
    }

    public void cq_log_error(String file, int line, String message) {
        L.e("%s", message);
    }
}
