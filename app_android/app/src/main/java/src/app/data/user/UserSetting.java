package src.app.data.user;

public class UserSetting {

    private static class Singleton {
        static UserSetting instance = new UserSetting();
    }
    public static UserSetting get() {
        return Singleton.instance;
    }
}
