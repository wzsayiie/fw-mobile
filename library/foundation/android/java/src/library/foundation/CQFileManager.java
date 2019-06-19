package src.library.foundation;

import android.content.Context;

import java.io.File;

import src.library.basis.CQString;

@SuppressWarnings("WeakerAccess") /* this is a library */
public class CQFileManager {

    public static String documentDirectory() {
        Context context = CQAppContextFinder.get().findApp();
        return context.getFilesDir().getAbsolutePath();
    }

    public static String cachesDirectory() {
        Context context = CQAppContextFinder.get().findApp();
        return context.getCacheDir().getAbsolutePath();
    }

    public static String temporaryDirectory() {
        Context context = CQAppContextFinder.get().findApp();
        return context.getCacheDir().getAbsolutePath();
    }

    public static String appendPath(String parent, String child) {
        if (parent != null && child != null) {
            if (!parent.endsWith("/")) {
                return String.format("%s/%s", parent, child);
            } else {
                return String.format("%s%s", parent, child);
            }
        } else {
            return parent;
        }
    }

    private static CQFileManager sInstance;

    public static synchronized CQFileManager get() {
        if (sInstance == null) {
            sInstance = new CQFileManager();
        }
        return sInstance;
    }

    public boolean directoryExists(String path) {
        if (path != null && path.length() > 0) {
            File file = new File(path);
            return file.exists() && file.isDirectory();
        } else {
            return false;
        }
    }

    public boolean fileExists(String path) {
        if (path != null && path.length() > 0) {
            File file = new File(path);
            return file.exists() && !file.isDirectory();
        } else {
            return false;
        }
    }

    public boolean createDirectory(String path, boolean intermediate) {
        if (CQString.isEmpty(path)) {
            return false;
        }

        File dir = new File(path);
        if (intermediate) {
            return dir.mkdirs();
        } else {
            return dir.mkdir();
        }
    }

    private void removeRecursively(File file) {
        if (file.isDirectory()) {
            for (File item : file.listFiles()) {
                removeRecursively(item);
            }
        }
        if (file.isFile()) {
            @SuppressWarnings("unused")
            boolean d = file.delete();
        }
    }

    public void removePath(String path) {
        if (CQString.isEmpty(path)) {
            File file = new File(path);
            removeRecursively(file);
        }
    }
}
