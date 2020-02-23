package src.library.basis;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CPtr {

    static CPtr objectFromValue(long value) {
        CPtr ptr = new CPtr();
        ptr.mValue = value;
        return ptr;
    }

    static long valueFromObject(CPtr ptr) {
        if (ptr != null) {
            return ptr.mValue;
        } else {
            return 0;
        }
    }

    private long mValue;
}
