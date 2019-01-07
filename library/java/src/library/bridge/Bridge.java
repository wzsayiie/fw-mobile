package src.library.bridge;

import android.util.SparseArray;

public class Bridge {

    private static class BridgeCoreItem {
        int referenceCount;
        Object object;
    }

    private static SparseArray<BridgeCoreItem> sBridgeCores;

    private static SparseArray<BridgeCoreItem> getBridgeCores() {
        if (sBridgeCores == null) {
            sBridgeCores = new SparseArray<>();
        }
        return sBridgeCores;
    }

    public static void addCore(int index, Object object) {
        if (object == null) {
            return;
        }

        BridgeCoreItem item = new BridgeCoreItem();
        item.referenceCount = 1;
        item.object = object;

        SparseArray<BridgeCoreItem> bridgeCores = getBridgeCores();
        bridgeCores.put(index, item);
    }

    public static boolean tryRetainCore(int index) {
        SparseArray<BridgeCoreItem> bridgeCores = getBridgeCores();
        BridgeCoreItem item = bridgeCores.get(index);
        if (item != null) {
            item.referenceCount += 1;
            return true;
        } else {
            return false;
        }
    }

    public static boolean tryReleaseCore(int index) {
        SparseArray<BridgeCoreItem> bridgeCores = getBridgeCores();
        BridgeCoreItem item = bridgeCores.get(index);
        if (item != null) {
            item.referenceCount -= 1;
            if (item.referenceCount <= 0) {
                bridgeCores.put(index, null);
            }
            return true;
        } else {
            return false;
        }
    }
}
