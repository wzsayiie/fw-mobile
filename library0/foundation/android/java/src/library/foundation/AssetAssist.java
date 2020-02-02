package src.library.foundation;

import android.app.Application;
import android.content.res.AssetManager;

import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class AssetAssist {

    public static byte[] getAsset(String name) {
        if (StringUtil.isEmpty(name)) {
            return null;
        }

        Application app = AppContextAssist.getApp();
        if (app == null) {
            return null;
        }

        try {
            InputStream input = app.getAssets().open(name);
            ByteArrayOutputStream output = new ByteArrayOutputStream();

            byte[] buffer = new byte[1024];
            int length;
            while ((length = input.read(buffer)) > 0) {
                output.write(buffer, 0, length);
            }
            byte[] data = output.toByteArray();

            output.close();
            input.close();

            return data;

        } catch (IOException ignored) {
            return null;
        }
    }

    private static void copyAssetItem(AssetManager manager, String from, String to) {
        try {
            String[] subFiles = manager.list(from);

            if (subFiles != null && subFiles.length > 0) {
                //this is a directory.

                FileAssist.createDirectory(to, false);

                for (String it : subFiles) {
                    String src = from + "/" + it;
                    String dst = to + "/" + it;
                    copyAssetItem(manager, src, dst);
                }

            } else {
                //try copy a file.

                InputStream input = manager.open(from);
                OutputStream output = new FileOutputStream(to);

                byte[] buffer = new byte[1024];
                int length;
                while ((length = input.read(buffer)) > 0) {
                    output.write(buffer, 0, length);
                }

                output.close();
                input.close();
            }

        } catch (IOException ignored) {
        }
    }

    public static boolean copyAsset(String fromPath, String toPath) {
        if (StringUtil.isEmpty(fromPath) || StringUtil.isEmpty(toPath)) {
            return false;
        }

        Application app = AppContextAssist.getApp();
        if (app == null) {
            return false;
        }

        //remove deprecated destination.
        FileAssist.removePath(toPath);

        copyAssetItem(app.getAssets(), fromPath, toPath);
        return true;
    }
}
