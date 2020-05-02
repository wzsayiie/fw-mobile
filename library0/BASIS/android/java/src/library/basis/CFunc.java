package src.library.basis;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CFunc {

    public static CPtr out          (ByteBuffer               dst) {return outBytes  (dst);}
    public static CPtr outLongList  (ArrayList<Long>          dst) {return outI64List(dst);}
    public static CPtr outStringList(ArrayList<String>        dst) {return outStrList(dst);}
    public static CPtr out          (HashMap<String, String>  dst) {return outSSMap  (dst);}

    private static native CPtr outBytes  (ByteBuffer              dst);
    private static native CPtr outI64List(ArrayList<Long>         dst);
    private static native CPtr outStrList(ArrayList<String>       dst);
    private static native CPtr outSSMap  (HashMap<String, String> dst);

    private static void onOutBytes(ByteBuffer dst, byte[] value) {
        if (dst != null && value != null) {
            dst.put(value);
        }
    }
    private static void onOutI64List(ArrayList<Long> dst, long value) {
        if (dst != null) {
            dst.add(value);
        }
    }
    private static void onOutStrList(ArrayList<String> dst, String value) {
        if (dst != null) {
            dst.add(value);
        }
    }
    private static void onOutSSMap(HashMap<String, String> dst, String key, String value) {
        if (dst != null && key != null) {
            dst.put(key, value);
        }
    }

    public static CPtr in          (byte[]                  src) {return inBytes  (src);}
    public static CPtr inLongList  (ArrayList<Long>         src) {return inI64List(src);}
    public static CPtr inStringList(ArrayList<String>       src) {return inStrList(src);}
    public static CPtr in          (HashMap<String, String> src) {return inSSMap  (src);}

    private static native CPtr inBytes  (byte[]                  src);
    private static native CPtr inI64List(ArrayList<Long>         src);
    private static native CPtr inStrList(ArrayList<String>       src);
    private static native CPtr inSSMap  (HashMap<String, String> src);

    private static void onInI64List(ArrayList<Long> src, CPtr out) {
        if (src == null) {
            return;
        }
        for (long it : src) {
            appendI64List(it, out);
        }
    }
    private static void onInStrList(ArrayList<String> src, CPtr out) {
        if (src == null) {
            return;
        }
        for (String it : src) {
            appendStrList(it, out);
        }
    }
    private static void onInSSMap(HashMap<String, String> src, CPtr out) {
        if (src == null) {
            return;
        }
        for (HashMap.Entry<String, String> cp : src.entrySet()) {
            appendSSMap(cp.getKey(), cp.getValue(), out);
        }
    }

    private static native void appendI64List(long   val, CPtr   out);
    private static native void appendStrList(String val, CPtr   out);
    private static native void appendSSMap  (String key, String val, CPtr out);

    public static byte[] getBytes(CPtr in) {
        ByteBuffer dst = ByteBuffer.allocate(0);
        assignBytes(in, out(dst));
        return dst.array();
    }
    public static ArrayList<Long> getI64List(CPtr in) {
        ArrayList<Long> dst = new ArrayList<>();
        assignI64List(in, outLongList(dst));
        return dst;
    }
    public static ArrayList<String> getStrList(CPtr in) {
        ArrayList<String> dst = new ArrayList<>();
        assignStrList(in, outStringList(dst));
        return dst;
    }
    public static HashMap<String, String> getSSMap(CPtr in) {
        HashMap<String, String> dst = new HashMap<>();
        assignSSMap(in, out(dst));
        return dst;
    }

    public static void set          (byte[]                   src, CPtr out) {setBytes  (src, out);}
    public static void setLongList  (ArrayList<Long>          src, CPtr out) {setI64List(src, out);}
    public static void setStringList(ArrayList<String>        src, CPtr out) {setStrList(src, out);}
    public static void set          (HashMap<String, String>  src, CPtr out) {setSSMap  (src, out);}

    private static void setBytes  (byte[]                  src, CPtr out) {assignBytes  (in          (src), out);}
    private static void setI64List(ArrayList<Long>         src, CPtr out) {assignI64List(inLongList  (src), out);}
    private static void setStrList(ArrayList<String>       src, CPtr out) {assignStrList(inStringList(src), out);}
    private static void setSSMap  (HashMap<String, String> src, CPtr out) {assignSSMap  (in          (src), out);}

    private static native void assignBytes  (CPtr in, CPtr out);
    private static native void assignI64List(CPtr in, CPtr out);
    private static native void assignStrList(CPtr in, CPtr out);
    private static native void assignSSMap  (CPtr in, CPtr out);
}
