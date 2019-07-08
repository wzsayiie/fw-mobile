package src.library.foundation;

import android.content.Context;

import java.io.File;

import src.library.basis.StringUtil;

public class FileManager {

    public static String documentDirectory() {
        Context context = AppContextFinder.get().findApp();
        return context.getFilesDir().getAbsolutePath();
    }

    public static String cachesDirectory() {
        Context context = AppContextFinder.get().findApp();
        return context.getCacheDir().getAbsolutePath();
    }

    public static String temporaryDirectory() {
        Context context = AppContextFinder.get().findApp();
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

    private static class Singleton {
        static FileManager instance = new FileManager();
    }
    public static FileManager get() {
        return Singleton.instance;
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
        if (StringUtil.isEmpty(path)) {
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
        if (StringUtil.isEmpty(path)) {
            File file = new File(path);
            removeRecursively(file);
        }
    }
}
