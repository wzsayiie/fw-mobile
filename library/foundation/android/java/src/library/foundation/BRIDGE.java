package src.library.foundation;

@SuppressWarnings("unused") /* the methods will be called by native */
public class BRIDGE {

    //log:

    public static void cq_log_info(String file, int line, String message) {
        L.i("%s", message);
    }

    public static void cq_log_error(String file, int line, String message) {
        L.e("%s", message);
    }

    //file manager:

    public static String cq_document_directory() {
        return FileManager.documentDirectory();
    }

    public static String cq_caches_directory() {
        return FileManager.cachesDirectory();
    }

    public static String cq_temporary_directory() {
        return FileManager.temporaryDirectory();
    }

    public static String cq_append_path(String parent, String child) {
        return FileManager.appendPath(parent, child);
    }

    public static boolean cq_directory_exists(String path) {
        return FileManager.get().directoryExists(path);
    }

    public static boolean cq_file_exists(String path) {
        return FileManager.get().fileExists(path);
    }

    public static boolean cq_create_directory(String path, boolean intermediate) {
        return FileManager.get().createDirectory(path, intermediate);
    }

    public static void cq_remove_path(String path) {
        FileManager.get().removePath(path);
    }

    //thread:

    public static void cq_thread_run(long task, long data) {
        ThreadManager.run(() -> threadBody(task, data));
    }

    private static native void threadBody(long task, long data);

    public static void cq_thread_sleep(float seconds) {
        ThreadManager.sleepForSeconds(seconds);
    }

    //network:

    public static void cq_http_get(String url, float timeout) {
        int[] error = new int[1];
        byte[] bytes = URLSession.get().sendSyncGet(url, timeout, error);
        httpGetReturn(error[0], bytes);
    }

    public static native void httpGetReturn(int error, byte[] data);
}
