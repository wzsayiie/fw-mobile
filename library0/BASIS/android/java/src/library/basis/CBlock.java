package src.library.basis;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CBlock {

    public static native CPtr retain(Runnable runnable);
    public static native void run(CPtr block);

    private static void run_block(Runnable runnable) {
        if (runnable != null) {
            runnable.run();
        }
    }
}
