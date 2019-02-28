package src.app.utility.application;

import java.util.HashMap;

import src.library.foundation.L;

public class SingletonManager {

    private static SingletonManager sInstance;

    public static SingletonManager get() {
        if (sInstance == null) {
            sInstance = new SingletonManager();
        }
        return sInstance;
    }

    private HashMap<Class, Object> sInstances;

    @SuppressWarnings("unchecked")
    public <T> T getInstanceOf(Class<T> clazz) {
        if (clazz == null) {
            L.e("try get a instance but class specified is null");
            return null;
        }

        if (sInstances == null) {
            L.i("init storage map of instances");
            sInstances = new HashMap<>();
        }

        if (!sInstances.containsKey(clazz)) {

            try {
                T object = clazz.newInstance();
                sInstances.put(clazz, object);
                L.i("new singleton object '%s' succeeded", clazz.getSimpleName());
                return object;
            } catch (Exception e) {
                L.e("new singleton object exception: %s", e);
                return null;
            }

        } else {

            return (T) sInstances.get(clazz);
        }
    }
}
