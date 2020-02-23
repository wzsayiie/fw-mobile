package src.library.basis;

import java.util.ArrayList;
import java.util.HashMap;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class JNI {

    public static byte[] bytesFrom(CPtr send, CPtr src) {
        makeBytesSuck(send, src);

        byte[] ret = sBytes;
        sBytes = null;
        return ret;
    }

    public static ArrayList<Long> longsFrom(CPtr send, CPtr src) {
        sLongs = new ArrayList<>();

        makeLongsSuck(send, src);

        ArrayList<Long> ret = sLongs;
        sLongs = null;
        return ret;
    }

    public static ArrayList<String> stringsFrom(CPtr send, CPtr src) {
        sStrings = new ArrayList<>();

        makeStringsSuck(send, src);

        ArrayList<String> ret = sStrings;
        sStrings = null;
        return ret;
    }

    public static HashMap<String, String> ssMapFrom(CPtr send, CPtr src) {
        sSSMap = new HashMap<>();

        makeStringsSuck(send, src);

        HashMap<String, String> ret = sSSMap;
        sSSMap = null;
        return ret;
    }

    private static byte[]                  sBytes  ;
    private static ArrayList<Long>         sLongs  ;
    private static ArrayList<String>       sStrings;
    private static HashMap<String, String> sSSMap  ;

    private static native void makeBytesSuck  (CPtr send, CPtr src);
    private static native void makeLongsSuck  (CPtr send, CPtr src);
    private static native void makeStringsSuck(CPtr send, CPtr src);
    private static native void makeSSMapSuck  (CPtr send, CPtr src);

    private static void onBytesSuck  (byte[]       value) { sBytes  =    value ; }
    private static void onLongsSuck  (long         value) { sLongs  .add(value); }
    private static void onStringsSuck(String       value) { sStrings.add(value); }
    private static void onSSMap      (String k, String v) { sSSMap  .put(k , v); }

    public static void sendBytes(byte[] src, CPtr receive, CPtr dst) {
        makeBytesSend(src, receive, dst);
    }

    public static void sendLongs(ArrayList<Long> src, CPtr receive, CPtr dst) {
        if (src != null) {
            for (Long it : src) {
                makeLongsAdd(it);
            }
        }
        makeLongsSend(receive, dst);
    }

    public static void sendStrings(ArrayList<String> src, CPtr receive, CPtr dst) {
        if (src != null) {
            for (String it : src) {
                makeStringsAdd(it);
            }
        }
        makeStringsSend(receive, dst);
    }

    public static void sendSSMap(HashMap<String, String> src, CPtr receive, CPtr dst) {
        if (src != null) {
            for (HashMap.Entry<String, String> cp : src.entrySet()) {
                makeSSMapAdd(cp.getKey(), cp.getValue());
            }
        }
        makeSSMapSend(receive, dst);
    }

    public static CPtr storeBytes(byte[] object) {
        return makeBytesStore(object);
    }

    public static CPtr storeLongs(ArrayList<Long> object) {
        if (object != null) {
            for (Long it : object) {
                makeLongsAdd(it);
            }
        }
        return makeLongsStore();
    }

    public static CPtr storeStrings(ArrayList<String> object) {
        if (object != null) {
            for (String it : object) {
                makeStringsAdd(it);
            }
        }
        return makeStringsStore();
    }

    public static CPtr storeSSMap(HashMap<String, String> object) {
        if (object != null) {
            for (HashMap.Entry<String, String> cp : object.entrySet()) {
                makeSSMapAdd(cp.getKey(), cp.getValue());
            }
        }
        return makeSSMapStore();
    }

    private static native void makeLongsAdd  (long   value);
    private static native void makeStringsAdd(String value);
    private static native void makeSSMapAdd  (String key, String value);

    private static native void makeBytesSend  (byte[] value, CPtr receive, CPtr dst);
    private static native void makeLongsSend  (CPtr receive, CPtr dst);
    private static native void makeStringsSend(CPtr receive, CPtr dst);
    private static native void makeSSMapSend  (CPtr receive, CPtr dst);

    private static native CPtr makeBytesStore  (byte[] value);
    private static native CPtr makeLongsStore  ();
    private static native CPtr makeStringsStore();
    private static native CPtr makeSSMapStore  ();

    public static native void run(CPtr runnable, CPtr data);
}
