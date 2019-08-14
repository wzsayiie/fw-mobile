package src.app.model.user;

public class UserIdentity {

    private static class Singleton {
        static UserIdentity instance = new UserIdentity();
    }
    public static UserIdentity get() {
        return Singleton.instance;
    }
}
