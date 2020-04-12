package src.library.basis;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CObject {

    public static native CPtr retain(Object object, String className);

    @SuppressWarnings("unchecked")
    public static <T> T raw(CPtr ptr, Class<T> cls) {
        Object object = raw(ptr);
        if (object == null) {
            return null;
        }

        if (cls == null || !object.getClass().equals(cls)) {
            return null;
        }

        return (T)object;
    }
    private static native Object raw(CPtr ptr);

    public static native void emit(CPtr ptr, int event);
}
