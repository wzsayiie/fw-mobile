package src.library.foundation;

import src.library.bridge.CQValue;

public class Bridge {

    public static long info(long message, long file, long line, long arg3) {
        String aa = CQValue.getString(message);
        String bb = CQValue.getString(file);
        int cc = CQValue.getInt(line);
        Logger.info(aa, bb, cc);
        return CQValue.Null;
    }

    public static long error(long message, long file, long line, long arg3) {
        String aa = CQValue.getString(message);
        String bb = CQValue.getString(file);
        int cc = CQValue.getInt(line);
        Logger.error(aa, bb, cc);
        return CQValue.Null;
    }
}
