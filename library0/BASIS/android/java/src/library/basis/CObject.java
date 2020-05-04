package src.library.basis;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CObject {

    public static native CPtr retainRaw(Object object, String className);
    public static native CPtr retain(CPtr object);
    public static native void release(CPtr object);

    @SuppressWarnings("unchecked")
    public static <T> T raw(CPtr ptr, Class<T> cls) {
        Object object = raw(ptr);
        if (object == null) {
            return null;
        }

        if (cls != null && object.getClass().equals(cls)) {
            return (T)object;
        }
        return null;
    }
    private static native Object raw(CPtr raw);

    public static void listen(CPtr object, int event, Runnable runnable) {
        CPtr block = CBlock.retainRaw(runnable);
        listen(object, event, block);
        CBlock.release(block);
    }
    private static native void listen(CPtr object, int event, CPtr block);

    public static native void emit(CPtr object, int event);
}
