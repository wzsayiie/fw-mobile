package src.library.foundation;

public class ThreadAssist {

    public static void run(Runnable task) {
        if (task != null) {
            new Thread(task).start();
        }
    }

    public static void sleepForSeconds(float seconds) {
        if (seconds > 0) {
            try {
                Thread.sleep((long) (1000 * seconds));
            } catch (InterruptedException ignored) {
            }
        }
    }

    public static void sleep(long millis) {
        if (millis > 0) {
            try {
                Thread.sleep(millis);
            } catch (InterruptedException ignored) {
            }
        }
    }
}
