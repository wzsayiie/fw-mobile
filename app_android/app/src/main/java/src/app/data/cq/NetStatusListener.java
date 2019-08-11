package src.app.data.cq;

public class NetStatusListener {

    private static class Singleton {
        static NetStatusListener instance = new NetStatusListener();
    }
    public static NetStatusListener get() {
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
