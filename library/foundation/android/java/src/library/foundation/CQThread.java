package src.library.foundation;

@SuppressWarnings("WeakerAccess") /* this is a library */
public class CQThread {

    public static void run(Runnable task) {
        if (task != null) {
            new Thread(task).start();
        }
    }

    public static void sleepForSeconds(float seconds) {
        if (seconds <= 0) {
            return;
        }

        try {
            Thread.sleep((long) (1000 * seconds));
        } catch (InterruptedException ignored) {
        }
    }
}
