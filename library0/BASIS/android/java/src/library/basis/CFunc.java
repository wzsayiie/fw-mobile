package src.library.basis;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CFunc {

    public static CPtr out(boolean[] dst) {return outBool  (dst);}
    public static CPtr out(byte[]    dst) {return outInt8  (dst);}
    public static CPtr out(short[]   dst) {return outInt16 (dst);}
    public static CPtr out(int[]     dst) {return outInt32 (dst);}
    public static CPtr out(long[]    dst) {return outInt64 (dst);}
    public static CPtr out(float[]   dst) {return outFloat (dst);}
    public static CPtr out(double[]  dst) {return outDouble(dst);}

    public static CPtr out(StringBuffer             dst) {return outStr    (dst);}
    public static CPtr out(ByteBuffer               dst) {return outBytes  (dst);}
    public static CPtr out(long _u, ArrayList<Long> dst) {return outI64List(dst);}
    public static CPtr out(ArrayList<String>        dst) {return outStrList(dst);}
    public static CPtr out(HashMap<String, String>  dst) {return outSSMap  (dst);}

    private static native CPtr outBool  (boolean[]    dst);
    private static native CPtr outInt8  (byte[]       dst);
    private static native CPtr outInt16 (short[]      dst);
    private static native CPtr outInt32 (int[]        dst);
    private static native CPtr outInt64 (long[]       dst);
    private static native CPtr outFloat (float[]      dst);
    private static native CPtr outDouble(double[]     dst);

    private static native CPtr outStr    (StringBuffer            dst);
    private static native CPtr outBytes  (ByteBuffer              dst);
    private static native CPtr outI64List(ArrayList<Long>         dst);
    private static native CPtr outStrList(ArrayList<String>       dst);
    private static native CPtr outSSMap  (HashMap<String, String> dst);

    private static void onOutBool  (boolean[] d, boolean v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutInt8  (byte[]    d, byte    v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutInt16 (short[]   d, short   v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutInt32 (int[]     d, int     v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutInt64 (long[]    d, long    v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutFloat (float[]   d, float   v) {if (d != null && d.length > 0) d[0] = v;}
    private static void onOutDouble(double[]  d, double  v) {if (d != null && d.length > 0) d[0] = v;}

    private static void onOutStr(StringBuffer dst, String value) {
        if (dst != null && value != null) {
            dst.append(value);
        }
    }
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

    public static CPtr in(boolean src) {return inBool  (src);}
    public static CPtr in(byte    src) {return inInt8  (src);}
    public static CPtr in(short   src) {return inInt16 (src);}
    public static CPtr in(int     src) {return inInt32 (src);}
    public static CPtr in(long    src) {return inInt64 (src);}
    public static CPtr in(float   src) {return inFloat (src);}
    public static CPtr in(double  src) {return inDouble(src);}
    public static CPtr in(String  src) {return inStr   (src);}
    public static CPtr in(byte[]  src) {return inBytes (src);}

    public static CPtr in(long _u, ArrayList<Long> src) {return inI64List(src);}
    public static CPtr in(ArrayList<String>        src) {return inStrList(src);}
    public static CPtr in(HashMap<String, String>  src) {return inSSMap  (src);}

    private static native CPtr inBool  (boolean src);
    private static native CPtr inInt8  (byte    src);
    private static native CPtr inInt16 (short   src);
    private static native CPtr inInt32 (int     src);
    private static native CPtr inInt64 (long    src);
    private static native CPtr inFloat (float   src);
    private static native CPtr inDouble(double  src);
    private static native CPtr inStr   (String  src);
    private static native CPtr inBytes (byte[]  src);

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

    public static boolean getBool  (CPtr in) { boolean[] r = new boolean[1]; assignBool  (in, out(r)); return r[0]; }
    public static byte    getInt8  (CPtr in) { byte   [] r = new byte   [1]; assignInt8  (in, out(r)); return r[0]; }
    public static short   getInt16 (CPtr in) { short  [] r = new short  [1]; assignInt16 (in, out(r)); return r[0]; }
    public static int     getInt32 (CPtr in) { int    [] r = new int    [1]; assignInt32 (in, out(r)); return r[0]; }
    public static long    getInt64 (CPtr in) { long   [] r = new long   [1]; assignInt64 (in, out(r)); return r[0]; }
    public static float   getFloat (CPtr in) { float  [] r = new float  [1]; assignFloat (in, out(r)); return r[0]; }
    public static double  getDouble(CPtr in) { double [] r = new double [1]; assignDouble(in, out(r)); return r[0]; }

    public static String getStr(CPtr in) {
        StringBuffer dst = new StringBuffer();
        assignStr(in, out(dst));
        return dst.toString();
    }
    public static byte[] getBytes(CPtr in) {
        ByteBuffer dst = ByteBuffer.allocate(0);
        assignBytes(in, out(dst));
        return dst.array();
    }
    public static ArrayList<Long> getI64List(CPtr in) {
        ArrayList<Long> dst = new ArrayList<>();
        assignI64List(in, out(0, dst));
        return dst;
    }
    public static ArrayList<String> getStrList(CPtr in) {
        ArrayList<String> dst = new ArrayList<>();
        assignStrList(in, out(dst));
        return dst;
    }

    public static void set(boolean src, CPtr out) {setBool  (src, out);}
    public static void set(byte    src, CPtr out) {setInt8  (src, out);}
    public static void set(short   src, CPtr out) {setInt16 (src, out);}
    public static void set(int     src, CPtr out) {setInt32 (src, out);}
    public static void set(long    src, CPtr out) {setInt64 (src, out);}
    public static void set(float   src, CPtr out) {setFloat (src, out);}
    public static void set(double  src, CPtr out) {setDouble(src, out);}
    public static void set(String  src, CPtr out) {setStr   (src, out);}
    public static void set(byte[]  src, CPtr out) {setBytes (src, out);}

    public static void set(long _u, ArrayList<Long> src, CPtr out) {setI64List(src, out);}
    public static void set(ArrayList<String>        src, CPtr out) {setStrList(src, out);}
    public static void set(HashMap<String, String>  src, CPtr out) {setSSMap  (src, out);}

    private static void setBool  (boolean src, CPtr out) {assignBool  (in(src), out);}
    private static void setInt8  (byte    src, CPtr out) {assignInt8  (in(src), out);}
    private static void setInt16 (short   src, CPtr out) {assignInt16 (in(src), out);}
    private static void setInt32 (int     src, CPtr out) {assignInt32 (in(src), out);}
    private static void setInt64 (long    src, CPtr out) {assignInt64 (in(src), out);}
    private static void setFloat (float   src, CPtr out) {assignFloat (in(src), out);}
    private static void setDouble(double  src, CPtr out) {assignDouble(in(src), out);}
    private static void setStr   (String  src, CPtr out) {assignStr   (in(src), out);}
    private static void setBytes (byte[]  src, CPtr out) {assignBytes (in(src), out);}

    private static void setI64List(ArrayList<Long>         src, CPtr out) {assignI64List(in(0, src), out);}
    private static void setStrList(ArrayList<String>       src, CPtr out) {assignStrList(in(   src), out);}
    private static void setSSMap  (HashMap<String, String> src, CPtr out) {assignSSMap  (in(   src), out);}

    private static native void assignBool   (CPtr in, CPtr out);
    private static native void assignInt8   (CPtr in, CPtr out);
    private static native void assignInt16  (CPtr in, CPtr out);
    private static native void assignInt32  (CPtr in, CPtr out);
    private static native void assignInt64  (CPtr in, CPtr out);
    private static native void assignFloat  (CPtr in, CPtr out);
    private static native void assignDouble (CPtr in, CPtr out);
    private static native void assignStr    (CPtr in, CPtr out);
    private static native void assignBytes  (CPtr in, CPtr out);
    private static native void assignI64List(CPtr in, CPtr out);
    private static native void assignStrList(CPtr in, CPtr out);
    private static native void assignSSMap  (CPtr in, CPtr out);
}
