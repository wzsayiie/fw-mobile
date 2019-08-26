package src.library.basis;

public class StringUtil {

    public static boolean isEmpty(String string) {
        return string == null || string.isEmpty();
    }

    public static boolean isEqual(String a, String b) {
        if (a != null) {
            return a.equals(b);
        } else {
            return b == null;
        }
    }

    public static String hexStringFromBytes(byte[] bytes) {
        if (bytes == null || bytes.length == 0) {
            return "";
        }

        char[] string = new char[bytes.length * 2];
        char[] hex = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
        for (int it = 0; it < bytes.length; ++it) {
            string[it * 2] = hex[(bytes[it] >> 4) & 0xf];
            string[it * 2 + 1] = hex[bytes[it] & 0xf];
        }

        return new String(string);
    }
}
