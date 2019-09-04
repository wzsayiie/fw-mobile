package src.app.model.user;

import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class UserIdentity {

    private static class Singleton {
        static UserIdentity instance = new UserIdentity();
    }
    public static UserIdentity get() {
        return Singleton.instance;
    }
}
