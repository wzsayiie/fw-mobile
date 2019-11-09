package src.library.foundation;

import android.app.Application;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class FileAssist {

    public static String filesDir() {
        Application app = AppContextAssist.getApp();
        if (app != null) {
            return app.getFilesDir().getAbsolutePath();
        } else {
            return null;
        }
    }

    public static String cacheDir() {
        Application app = AppContextAssist.getApp();
        if (app != null) {
            return app.getCacheDir().getAbsolutePath();
        } else {
            return null;
        }
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
        if (file == null) {
            return;
        }

        if (file.isDirectory()) {
            File[] subFiles = file.listFiles();
            if (subFiles != null) {
                for (File it : subFiles) {
                    removeRecursively(it);
                }
            }
        } else if (file.isFile()) {
            boolean ignored = file.delete();
        }
    }

    public static void removePath(String path) {
        if (StringUtil.isEmpty(path)) {
            File file = new File(path);
            removeRecursively(file);
        }
    }
}
