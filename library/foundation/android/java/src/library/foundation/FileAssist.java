package src.library.foundation;

import android.app.Application;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import src.library.basis.StringUtil;

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

    public static void copyAssetToDir(String assetName, String dir, String fileName) {
        if (StringUtil.isEmpty(assetName)) {
            return;
        }
        if (StringUtil.isEmpty(dir)) {
            return;
        }
        if (StringUtil.isEmpty(fileName)) {
            return;
        }

        File outFile = new File(dir, fileName);
        if (outFile.exists()) {
            removeRecursively(outFile);
        }

        try {
            Application app = AppContextAssist.getApp();
            if (app == null) {
                return;
            }
            InputStream inStream = app.getAssets().open(assetName);
            OutputStream outStream = new FileOutputStream(outFile);

            byte[] buffer = new byte[4 * 1024];
            int count;
            while ((count = inStream.read(buffer)) > 0) {
                outStream.write(buffer, 0, count);
            }

            inStream.close();
            outStream.close();

        } catch (IOException ignored) {
        }
    }
}
