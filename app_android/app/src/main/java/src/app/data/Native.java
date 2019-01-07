package src.app.data;

public class Native {

    static {
        System.loadLibrary("native");
    }

    public static native void action(String text);
}
