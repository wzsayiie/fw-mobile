package src.library.bridge;

public class BridgeValue {

    public static final long Null = 0;

    public static native int getInt(long handle);
    public static native String getString(long handle);
}
