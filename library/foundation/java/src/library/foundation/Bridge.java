package src.library.foundation;

import src.library.bridge.BridgeValue;

public class Bridge {

    public static long info(long message, long file, long line, long arg3) {
        String aa = BridgeValue.getString(message);
        String bb = BridgeValue.getString(file);
        int cc = BridgeValue.getInt(line);
        Logger.info(aa, bb, cc);
        return BridgeValue.Null;
    }

    public static long error(long message, long file, long line, long arg3) {
        String aa = BridgeValue.getString(message);
        String bb = BridgeValue.getString(file);
        int cc = BridgeValue.getInt(line);
        Logger.error(aa, bb, cc);
        return BridgeValue.Null;
    }
}
