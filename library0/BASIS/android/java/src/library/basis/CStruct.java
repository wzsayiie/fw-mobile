package src.library.basis;

import java.lang.ref.WeakReference;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CStruct {

    private static final int BYTES      = 1;
    private static final int INT64_LIST = 2;
    private static final int STR_LIST   = 3;
    private static final int SS_MAP     = 4;

    //make a c ref to a java object:

    public static CPtr bytes    (ByteBuffer              a) { return cast(a, BYTES     ); }
    public static CPtr bytes    (byte[]                  a) { return cast(a, BYTES     ); }
    public static CPtr int64List(ArrayList<Long>         a) { return cast(a, INT64_LIST); }
    public static CPtr strList  (ArrayList<String>       a) { return cast(a, STR_LIST  ); }
    public static CPtr ssMap    (HashMap<String, String> a) { return cast(a, SS_MAP    ); }

    private static CPtr cast(Object object, int type) {
        if (object != null) {
            int index = storeWeakRef(object);
            return generateStruct(index, type);
        }
        return null;
    }
    private static native CPtr generateStruct(int index, int type);

    //clear methods:

    private static void bytes_clear(int index) {
        ByteBuffer buffer = getStoredRef(index, ByteBuffer.class);
        if (buffer != null) {
            buffer.clear();
            return;
        }

        byte[] bytes = getStoredRef(index, byte[].class);
        if (bytes != null) {
            Arrays.fill(bytes, (byte)0);
        }
    }

    private static void int64_list_clear(int index) {
        @SuppressWarnings("unchecked")
        ArrayList<Long> dst = getStoredRef(index, ArrayList.class);
        if (dst != null) {
            dst.clear();
        }
    }

    private static void str_list_clear(int index) {
        @SuppressWarnings("unchecked")
        ArrayList<String> dst = getStoredRef(index, ArrayList.class);
        if (dst != null) {
            dst.clear();
        }
    }

    private static void ss_map_clear(int index) {
        @SuppressWarnings("unchecked")
        HashMap<String, String> dst = getStoredRef(index, HashMap.class);
        if (dst != null) {
            dst.clear();
        }
    }

    //receive methods:

    private static void bytes_recv(int index, byte[] data) {
        if (data == null || data.length == 0) {
            return;
        }

        ByteBuffer buffer = getStoredRef(index, ByteBuffer.class);
        if (buffer != null) {
            buffer.put(data);
            return;
        }

        byte[] bytes = getStoredRef(index, byte[].class);
        if (bytes != null) {
            int length = Math.min(bytes.length, data.length);
            System.arraycopy(data, 0, bytes, 0, length);
        }
    }

    private static void int64_list_recv(int index, long item) {
        @SuppressWarnings("unchecked")
        ArrayList<Long> dst = getStoredRef(index, ArrayList.class);
        if (dst != null) {
            dst.add(item);
        }
    }

    private static void str_list_recv(int index, String item) {
        @SuppressWarnings("unchecked")
        ArrayList<String> dst = getStoredRef(index, ArrayList.class);
        if (dst != null) {
            dst.add(item);
        }
    }

    private static void ss_map_recv(int index, String key, String value) {
        @SuppressWarnings("unchecked")
        HashMap<String, String> dst = getStoredRef(index, HashMap.class);
        if (dst == null) {
            return;
        }

        if (StringUtil.isNonEmpty(key)) {
            dst.put(key, value);
        }
    }

    //send methods:

    private static void bytes_send(int index, CPtr dst) {
        ByteBuffer buffer = getStoredRef(index, ByteBuffer.class);
        if (buffer != null) {
            sendBytes(buffer.array(), dst);
            return;
        }

        byte[] bytes = getStoredRef(index, byte[].class);
        if (bytes != null) {
            sendBytes(bytes, dst);
        }
    }

    private static void int64_list_send(int index, CPtr dst) {
        @SuppressWarnings("unchecked")
        ArrayList<Long> src = getStoredRef(index, ArrayList.class);
        if (src == null) {
            return;
        }

        for (long item : src) {
            sendInt64List(item, dst);
        }
    }

    private static void str_list_send(int index, CPtr dst) {
        @SuppressWarnings("unchecked")
        ArrayList<String> src = getStoredRef(index, ArrayList.class);
        if (src == null) {
            return;
        }

        for (String item : src) {
            sendStrList(item, dst);
        }
    }

    private static void ss_map_send(int index, CPtr dst) {
        @SuppressWarnings("unchecked")
        HashMap<String, String> src = getStoredRef(index, HashMap.class);
        if (src == null) {
            return;
        }

        for (HashMap.Entry<String, String> entry : src.entrySet()) {
            sendSSMap(entry.getKey(), entry.getValue(), dst);
        }
    }

    private static native void sendBytes    (byte[] data, CPtr dst);
    private static native void sendInt64List(long   item, CPtr dst);
    private static native void sendStrList  (String item, CPtr dst);
    private static native void sendSSMap    (String key , String value, CPtr dst);

    //weak reference pool:

    @SuppressWarnings("unchecked")
    private static final WeakReference<Object>[] sReferences = new WeakReference[64];
    private static int sReferenceCursor = 1;

    private static int storeWeakRef(Object object) {
        WeakReference<Object> ref = new WeakReference<>(object);
        int index;

        synchronized (sReferences) {
            index = sReferenceCursor;

            sReferenceCursor = (sReferenceCursor + 1) % sReferences.length;
            //NOTE: position '0' is reserved.
            if (sReferenceCursor == 0) {
                sReferenceCursor = 1;
            }

            sReferences[index] = ref;
        }

        return index;
    }

    @SuppressWarnings("unchecked")
    private static <T> T getStoredRef(int index, Class<T> cls) {
        Object ref = null;

        synchronized (sReferences) {
            if (0 <= index && index < sReferences.length) {
                if (sReferences[index] != null) {
                    ref = sReferences[index].get();
                }
            }
        }

        if (ref != null && ref.getClass().equals(cls)) {
            return (T)ref;
        }
        return null;
    }

    //methods for c types:

    public static void bytesClear    (CPtr dst) { clear(dst, BYTES     ); }
    public static void int64ListClear(CPtr dst) { clear(dst, INT64_LIST); }
    public static void strListClear  (CPtr dst) { clear(dst, STR_LIST  ); }
    public static void ssMapClear    (CPtr dst) { clear(dst, SS_MAP    ); }

    public static void bytesAppend    (ByteBuffer              dst, CPtr src) { append(bytes    (dst), src, BYTES     ); }
    public static void bytesAppend    (byte[]                  dst, CPtr src) { append(bytes    (dst), src, BYTES     ); }
    public static void int64ListAppend(ArrayList<Long>         dst, CPtr src) { append(int64List(dst), src, INT64_LIST); }
    public static void strListAppend  (ArrayList<String>       dst, CPtr src) { append(strList  (dst), src, STR_LIST  ); }
    public static void ssMapAppend    (HashMap<String, String> dst, CPtr src) { append(ssMap    (dst), src, SS_MAP    ); }

    public static void bytesAppend    (CPtr dst, ByteBuffer              src) { append(dst, bytes    (src), BYTES     ); }
    public static void bytesAppend    (CPtr dst, byte[]                  src) { append(dst, bytes    (src), BYTES     ); }
    public static void int64ListAppend(CPtr dst, ArrayList<Long>         src) { append(dst, int64List(src), INT64_LIST); }
    public static void strListAppend  (CPtr dst, ArrayList<String>       src) { append(dst, strList  (src), STR_LIST  ); }
    public static void ssMapAppend    (CPtr dst, HashMap<String, String> src) { append(dst, ssMap    (src), SS_MAP    ); }

    public static void bytesAssign    (ByteBuffer              dst, CPtr src) { assign(bytes    (dst), src, BYTES     ); }
    public static void bytesAssign    (byte[]                  dst, CPtr src) { assign(bytes    (dst), src, BYTES     ); }
    public static void int64ListAssign(ArrayList<Long>         dst, CPtr src) { assign(int64List(dst), src, INT64_LIST); }
    public static void strListAssign  (ArrayList<String>       dst, CPtr src) { assign(strList  (dst), src, STR_LIST  ); }
    public static void ssMapAssign    (HashMap<String, String> dst, CPtr src) { assign(ssMap    (dst), src, SS_MAP    ); }

    public static void bytesAssign    (CPtr dst, ByteBuffer              src) { assign(dst, bytes    (src), BYTES     ); }
    public static void bytesAssign    (CPtr dst, byte[]                  src) { assign(dst, bytes    (src), BYTES     ); }
    public static void int64ListAssign(CPtr dst, ArrayList<Long>         src) { assign(dst, int64List(src), INT64_LIST); }
    public static void strListAssign  (CPtr dst, ArrayList<String>       src) { assign(dst, strList  (src), STR_LIST  ); }
    public static void ssMapAssign    (CPtr dst, HashMap<String, String> src) { assign(dst, ssMap    (src), SS_MAP    ); }

    public static void bytesStore    (ByteBuffer              val) { store(bytes    (val), BYTES     ); }
    public static void bytesStore    (byte[]                  val) { store(bytes    (val), BYTES     ); }
    public static void int64ListStore(ArrayList<Long>         val) { store(int64List(val), INT64_LIST); }
    public static void strListStore  (ArrayList<String>       val) { store(strList  (val), STR_LIST  ); }
    public static void ssMapStore    (HashMap<String, String> val) { store(ssMap    (val), SS_MAP    ); }

    private static native void clear (CPtr dst, int type);
    private static native void append(CPtr dst, CPtr src, int type);
    private static native void assign(CPtr dst, CPtr src, int type);
    private static native CPtr store (CPtr val, int type);
}
