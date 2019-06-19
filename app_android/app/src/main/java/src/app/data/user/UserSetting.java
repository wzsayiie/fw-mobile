package src.app.data.user;

public class UserSetting {

    private static UserSetting sInstance;

    public static synchronized UserSetting get() {
        if (sInstance == null) {
            sInstance = new UserSetting();
        }
        return sInstance;
    }
}
