package src.library.foundation;

import android.os.NetworkOnMainThreadException;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import src.library.basis.CQString;

@SuppressWarnings("WeakerAccess") /* this is a library */
public class CQURLSession {

    private static CQURLSession sInstance;

    public static synchronized CQURLSession get() {
        if (sInstance == null) {
            sInstance = new CQURLSession();
        }
        return sInstance;
    }

    //NOTE:
    //android sdk don't allow network operation on main thread,
    //if the method called on main thread, always failed.
    public byte[] sendSyncGet(String urlString, float timeoutSeconds, int[] outError) {

        //firstly set error = 1, if successful reset error = 0
        if (outError != null) {
            outError[0] = 1;
        }

        if (CQString.isEmpty(urlString) || timeoutSeconds <= 0) {
            return null;
        }

        URL url;
        try {
            url = new URL(urlString);
        } catch (MalformedURLException ignored) {
            return null;
        }

        HttpURLConnection connection = null;
        ByteArrayOutputStream data = new ByteArrayOutputStream();
        try {
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setReadTimeout((int) (timeoutSeconds * 1000));

            InputStream stream = connection.getInputStream();
            byte[] once = new byte[1024];
            int count;
            while ((count = stream.read(once, 0, once.length)) != -1) {
                data.write(once, 0, count);
            }

            //successful
            if (outError != null) {
                outError[0] = 0;
            }
        } catch (IOException ignored) {

        } catch (NetworkOnMainThreadException ignored) {

        } finally {
            if (connection != null) {
                connection.disconnect();
            }
        }
        return data.toByteArray();
    }
}
