package src.library.basis;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class CBlock {

    public static void in(String name, boolean value) {setParam(name, TYPE_BOOL_IN  , CFunc.in(value));}
    public static void in(String name, byte    value) {setParam(name, TYPE_INT8_IN  , CFunc.in(value));}
    public static void in(String name, short   value) {setParam(name, TYPE_INT16_IN , CFunc.in(value));}
    public static void in(String name, int     value) {setParam(name, TYPE_INT32_IN , CFunc.in(value));}
    public static void in(String name, long    value) {setParam(name, TYPE_INT64_IN , CFunc.in(value));}
    public static void in(String name, float   value) {setParam(name, TYPE_FLOAT_IN , CFunc.in(value));}
    public static void in(String name, double  value) {setParam(name, TYPE_DOUBLE_IN, CFunc.in(value));}
    public static void in(String name, String  value) {setParam(name, TYPE_STR_IN   , CFunc.in(value));}
    public static void in(String name, byte[]  value) {setParam(name, TYPE_BYTES_IN , CFunc.in(value));}

    public static void in(String name, long _u, ArrayList<Long> value) {setParam(name, TYPE_I64_LIST_IN, CFunc.in(0, value));}
    public static void in(String name, ArrayList<String>        value) {setParam(name, TYPE_STR_LIST_IN, CFunc.in(   value));}
    public static void in(String name, HashMap<String, String>  value) {setParam(name, TYPE_SS_MAP_IN  , CFunc.in(   value));}

    public static void out(String name, boolean[]     value) {setParam(name, TYPE_BOOL_OUT  , CFunc.out(value));}
    public static void out(String name, byte[]        value) {setParam(name, TYPE_INT8_OUT  , CFunc.out(value));}
    public static void out(String name, short[]       value) {setParam(name, TYPE_INT16_OUT , CFunc.out(value));}
    public static void out(String name, int[]         value) {setParam(name, TYPE_INT32_OUT , CFunc.out(value));}
    public static void out(String name, long[]        value) {setParam(name, TYPE_INT64_OUT , CFunc.out(value));}
    public static void out(String name, float[]       value) {setParam(name, TYPE_FLOAT_OUT , CFunc.out(value));}
    public static void out(String name, double[]      value) {setParam(name, TYPE_DOUBLE_OUT, CFunc.out(value));}
    public static void out(String name, StringBuilder value) {setParam(name, TYPE_STR_OUT   , CFunc.out(value));}
    public static void out(String name, ByteBuffer    value) {setParam(name, TYPE_BYTES_OUT , CFunc.out(value));}

    public static void out(String name, long u, ArrayList<Long> value) {setParam(name, TYPE_I64_LIST_OUT, CFunc.out(0, value));}
    public static void out(String name, ArrayList<String>       value) {setParam(name, TYPE_STR_LIST_OUT, CFunc.out(   value));}
    public static void out(String name, HashMap<String, String> value) {setParam(name, TYPE_SS_MAP_OUT  , CFunc.out(   value));}

    public static boolean getBool  (String name) {return CFunc.getBool  (param(name, TYPE_BOOL_IN  ));}
    public static byte    getInt8  (String name) {return CFunc.getInt8  (param(name, TYPE_INT8_IN  ));}
    public static short   getInt16 (String name) {return CFunc.getInt16 (param(name, TYPE_INT16_IN ));}
    public static int     getInt32 (String name) {return CFunc.getInt32 (param(name, TYPE_INT32_IN ));}
    public static long    getInt64 (String name) {return CFunc.getInt64 (param(name, TYPE_INT64_IN ));}
    public static float   getFloat (String name) {return CFunc.getFloat (param(name, TYPE_FLOAT_IN ));}
    public static double  getDouble(String name) {return CFunc.getDouble(param(name, TYPE_DOUBLE_IN));}
    public static String  getStr   (String name) {return CFunc.getStr   (param(name, TYPE_STR_IN   ));}
    public static byte[]  getBytes (String name) {return CFunc.getBytes (param(name, TYPE_BYTES_IN ));}

    public static ArrayList<Long>         getI64List(String name) {return CFunc.getI64List(param(name, TYPE_I64_LIST_IN));}
    public static ArrayList<String>       getStrList(String name) {return CFunc.getStrList(param(name, TYPE_STR_LIST_IN));}
    public static HashMap<String, String> getSSMap  (String name) {return CFunc.getSSMap  (param(name, TYPE_SS_MAP_IN  ));}

    public static void set(String name, boolean value) {CFunc.set(value, param(name, TYPE_BOOL_OUT  ));}
    public static void set(String name, byte    value) {CFunc.set(value, param(name, TYPE_INT8_OUT  ));}
    public static void set(String name, short   value) {CFunc.set(value, param(name, TYPE_INT16_OUT ));}
    public static void set(String name, int     value) {CFunc.set(value, param(name, TYPE_INT32_OUT ));}
    public static void set(String name, long    value) {CFunc.set(value, param(name, TYPE_INT64_OUT ));}
    public static void set(String name, float   value) {CFunc.set(value, param(name, TYPE_FLOAT_OUT ));}
    public static void set(String name, double  value) {CFunc.set(value, param(name, TYPE_DOUBLE_OUT));}
    public static void set(String name, String  value) {CFunc.set(value, param(name, TYPE_STR_OUT   ));}
    public static void set(String name, byte[]  value) {CFunc.set(value, param(name, TYPE_BYTES_OUT ));}

    public static void set(String name, long u, ArrayList<Long> value) {CFunc.set(0, value, param(name, TYPE_I64_LIST_OUT));}
    public static void set(String name, ArrayList<String>       value) {CFunc.set(   value, param(name, TYPE_STR_LIST_OUT));}
    public static void set(String name, HashMap<String, String> value) {CFunc.set(   value, param(name, TYPE_SS_MAP_OUT  ));}

    private static final int TYPE_BOOL_IN     = 0x21;
    private static final int TYPE_INT8_IN     = 0x22;
    private static final int TYPE_INT16_IN    = 0x23;
    private static final int TYPE_INT32_IN    = 0x24;
    private static final int TYPE_INT64_IN    = 0x25;
    private static final int TYPE_FLOAT_IN    = 0x26;
    private static final int TYPE_DOUBLE_IN   = 0x27;
    private static final int TYPE_STR_IN      = 0x28;
    private static final int TYPE_BYTES_IN    = 0x29;
    private static final int TYPE_I64_LIST_IN = 0x2A;
    private static final int TYPE_STR_LIST_IN = 0x2B;
    private static final int TYPE_SS_MAP_IN   = 0x2C;

    private static final int TYPE_BOOL_OUT     = 0x31;
    private static final int TYPE_INT8_OUT     = 0x32;
    private static final int TYPE_INT16_OUT    = 0x33;
    private static final int TYPE_INT32_OUT    = 0x34;
    private static final int TYPE_INT64_OUT    = 0x35;
    private static final int TYPE_FLOAT_OUT    = 0x36;
    private static final int TYPE_DOUBLE_OUT   = 0x37;
    private static final int TYPE_STR_OUT      = 0x38;
    private static final int TYPE_BYTES_OUT    = 0x39;
    private static final int TYPE_I64_LIST_OUT = 0x3A;
    private static final int TYPE_STR_LIST_OUT = 0x3B;
    private static final int TYPE_SS_MAP_OUT   = 0x3C;

    private static native void setParam(String name, int type, CPtr ptr);
    private static native CPtr param(String name, int type);

    public static native void run(CPtr block, CPtr data);
}
