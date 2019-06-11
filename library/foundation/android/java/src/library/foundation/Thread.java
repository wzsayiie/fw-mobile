package src.library.foundation;

@SuppressWarnings("WeakerAccess") /* this is a library */
public class Thread {

    public static void run(Runnable task) {
        if (task != null) {
            new java.lang.Thread(task).start();
        }
    }

    public static void sleepForSeconds(float seconds) {
        if (seconds <= 0) {
            return;
        }

        try {
            java.lang.Thread.sleep((long) (1000 * seconds));
        } catch (InterruptedException ignored) {
        }
    }
}
