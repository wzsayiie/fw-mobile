package src.library.basis;

import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class JNI {

    //runnable:

    public static native void run(CPtr runnable, CPtr data);

    //data structure:

    public static byte[] bytesFrom(CPtr in) {
        makeBytesSuck(in);

        byte[] ret = sBytes;
        sBytes = null;
        return ret;
    }

    public static ArrayList<Long> intListFrom(CPtr in) {
        sIntList = new ArrayList<>();

        makeIntListSuck(in);

        ArrayList<Long> ret = sIntList;
        sIntList = null;
        return ret;
    }

    public static ArrayList<String> strListFrom(CPtr in) {
        sStrList = new ArrayList<>();

        makeStrListSuck(in);

        ArrayList<String> ret = sStrList;
        sStrList = null;
        return ret;
    }

    public static HashMap<String, String> ssMapFrom(CPtr in) {
        sSSMap = new HashMap<>();

        makeSSMapSuck(in);

        HashMap<String, String> ret = sSSMap;
        sSSMap = null;
        return ret;
    }

    private static byte[]                  sBytes  ;
    private static ArrayList<Long>         sIntList;
    private static ArrayList<String>       sStrList;
    private static HashMap<String, String> sSSMap  ;

    private static native void makeBytesSuck  (CPtr in);
    private static native void makeIntListSuck(CPtr in);
    private static native void makeStrListSuck(CPtr in);
    private static native void makeSSMapSuck  (CPtr in);

    private static void onBytesSuck  (byte[]       value) { sBytes  =    value ; }
    private static void onIntListSuck(long         value) { sIntList.add(value); }
    private static void onStrListSuck(String       value) { sStrList.add(value); }
    private static void onSSMap      (String k, String v) { sSSMap  .put(k , v); }

    public static void bytesAssign(byte[] object, CPtr out) {
        makeBytesAssign(object, out);
    }

    public static void intListAssign(ArrayList<Long> object, CPtr out) {
        if (object == null) {
            return;
        }
        for (Long it : object) {
            makeIntListAssign(it, out);
        }
    }

    public static void strListAssign(ArrayList<String> object, CPtr out) {
        if (object == null) {
            return;
        }
        for (String it : object) {
            makeStrListAssign(it, out);
        }
    }

    public static void ssMapAssign(HashMap<String, String> object, CPtr out) {
        if (object == null) {
            return;
        }
        for (HashMap.Entry<String, String> cp : object.entrySet()) {
            makeSSMapAssign(cp.getKey(), cp.getValue(), out);
        }
    }

    private static native void makeBytesAssign  (byte[] value, CPtr out);
    private static native void makeIntListAssign(long   value, CPtr out);
    private static native void makeStrListAssign(String value, CPtr out);
    private static native void makeSSMapAssign  (String key, String value, CPtr out);

    //object reference:

    //create a pointer that references $object. the pointer need to release by cq_release_obj().
    public static native CPtr retainJavaObject(Object object, String cls);

    //get the object that pointed by $ptr.
    //if $ptr does not point a java object or that object is not a $cls, return null.
    //it's equivalent to $cls is null and $cls is Object.class .
    @SuppressWarnings("unchecked")
    public static <T> T rawJavaObject(CPtr ptr, Class<T> cls) {
        Object object = makeObjectReturnRaw(ptr);
        if (object == null) {
            return null;
        }

        if (cls != null && !object.getClass().equals(cls)) {
            return null;
        }

        return (T)object;
    }

    private static native Object makeObjectReturnRaw(CPtr ptr);
}
