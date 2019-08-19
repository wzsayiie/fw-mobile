package src.library.foundation;

import android.app.Application;

import java.io.File;

import src.library.basis.StringUtil;

public class FileAssist {

    public static String documentDirectory() {
        Application app = AppContextAssist.getApp();
        if (app != null) {
            return app.getFilesDir().getAbsolutePath();
        } else {
            return null;
        }
    }

    public static String cachesDirectory() {
        Application app = AppContextAssist.getApp();
        if (app != null) {
            return app.getCacheDir().getAbsolutePath();
        } else {
            return null;
        }
    }

    public static String temporaryDirectory() {
        return cachesDirectory();
    }

    public static boolean directoryExists(String path) {
        if (!StringUtil.isEmpty(path)) {
            File file = new File(path);
            return file.exists() && file.isDirectory();
        } else {
            return false;
        }
    }

    public static boolean fileExists(String path) {
        if (!StringUtil.isEmpty(path)) {
            File file = new File(path);
            return file.exists() && !file.isDirectory();
        } else {
            return false;
        }
    }

    public static boolean createDirectory(String path, boolean intermediate) {
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

    private static void removeRecursively(File file) {
        if (file.isDirectory()) {
            for (File item : file.listFiles()) {
                removeRecursively(item);
            }
        } else if (file.isFile()) {
            @SuppressWarnings("unused")
            boolean d = file.delete();
        }
    }

    public static void removePath(String path) {
        if (StringUtil.isEmpty(path)) {
            File file = new File(path);
            removeRecursively(file);
        }
    }
}
