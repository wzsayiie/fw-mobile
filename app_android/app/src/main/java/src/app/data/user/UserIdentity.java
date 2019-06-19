package src.app.data.user;

public class UserIdentity {

    private static UserIdentity sInstance;

    public static synchronized UserIdentity get() {
        if (sInstance == null) {
            sInstance = new UserIdentity();
        }
        return sInstance;
    }
}
