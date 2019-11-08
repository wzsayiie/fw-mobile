package src.library.foundation;

import android.app.Application;
import android.content.res.AssetManager;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class AssetAssist {

    public static byte[] getAsset(String type, String name) {
        if (StringUtil.isEmpty(type) || StringUtil.isEmpty(name)) {
            return null;
        }

        //1 open the resource.
        Application app = AppContextAssist.getApp();
        AssetManager manager = app.getResources().getAssets();

        InputStream input = null;
        try {
            input = manager.open(name + "." + type);
        } catch (IOException ignored) {
        }

        //NOTE: enable open the file from userappres/ without parent directory name.
        try {
            if (input == null) {
                input = manager.open("userappres/" + name + "." + type);
            }
        } catch (IOException ignored) {
        }

        if (input == null) {
            return null;
        }

        //2. read the resource.
        try {

            ByteArrayOutputStream output = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int length;
            while ((length = input.read(buffer)) > 0) {
                output.write(buffer, 0, length);
            }

            input.close();

            return output.toByteArray();

        } catch (IOException ignored) {
            return null;
        }
    }
}
