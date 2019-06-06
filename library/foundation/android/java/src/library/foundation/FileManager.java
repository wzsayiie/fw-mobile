package src.library.foundation;

import android.content.Context;

import java.io.File;

@SuppressWarnings("WeakerAccess") /* this is a library */
public class FileManager {

    public static String documentDirectory() {
        Context context = ContextFinder.get().findCurrentActivity();
        return context.getFilesDir().getAbsolutePath();
    }

    public static String cachesDirectory() {
        Context context = ContextFinder.get().findCurrentActivity();
        return context.getCacheDir().getAbsolutePath();
    }

    public static String temporaryDirectory() {
        Context context = ContextFinder.get().findCurrentActivity();
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

    private static FileManager sInstance;

    public static FileManager get() {
        if (sInstance == null) {
            sInstance = new FileManager();
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
        if (path == null || path.length() == 0) {
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
        if (path == null || path.length() == 0) {
            File file = new File(path);
            removeRecursively(file);
        }
    }
}
