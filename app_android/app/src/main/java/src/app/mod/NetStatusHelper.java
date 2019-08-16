package src.app.mod;

public class NetStatusHelper {

    private static class Singleton {
        static NetStatusHelper instance = new NetStatusHelper();
    }
    public static NetStatusHelper get() {
        return Singleton.instance;
    }

    public static final int NET_STATUS_NONE = 0;
    public static final int NET_STATUS_WWAN = 1;
    public static final int NET_STATUS_WiFi = 2;

    private int mStatus;

    public int getStatus() {
        return mStatus;
    }
}
