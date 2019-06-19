package src.app.data;

import src.library.foundation.L;

public class CQHotfixManager {

    private static CQHotfixManager sInstance;

    public static synchronized CQHotfixManager get() {
        if (sInstance == null) {
            L.i("init hotfix management");
            sInstance = new CQHotfixManager();
        }
        return sInstance;
    }
}
