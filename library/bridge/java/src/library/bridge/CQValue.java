package src.library.bridge;

public class CQValue {

    public static final long Null = 0;

    public static native int getInt(long handle);
    public static native String getString(long handle);
}
