package src.library.foundation;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import src.library.basis.StringUtil;
import src.library.basis.W;

//WARNING:
//don't use HttpSession on main thread, which will result in a system exception.
//android prohibits any network access on the main thread.

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class HttpSession {

    public interface RequestBodyReader {
        //return length of read bytes, if no more bytes could be read, return -1.
        int read(HttpSession session, byte[] buffer);
    }

    public interface ResponseBodyWriter {
        //return false means stop transfer.
        boolean write(HttpSession session, byte[] data);
    }

    private float mTimeoutSeconds;

    private String mMethod;
    private String mURLString;
    private HashMap<String, String> mURLQuery;
    private HashMap<String, String> mRequestHeader;
    private RequestBodyReader mRequestBodyReader;
    private byte[] mRequestBodyData;

    private int mResponseCode;
    private HashMap<String, String> mResponseHeader;
    private ResponseBodyWriter mResponseBodyWriter;
    private byte[] mResponseBodyData;

    public void setMethod(String method) {
        mMethod = method;
    }

    public void setURLString(String urlString) {
        mURLString= urlString;
    }

    public void setURLQuery(String field, String value) {
        if (StringUtil.isEmpty(field) || StringUtil.isEmpty(value)) {
            return;
        }

        try {
            String escapedField = URLEncoder.encode(field, "UTF-8");
            String escapedValue = URLEncoder.encode(value, "UTF-8");

            if (mURLQuery == null) {
                mURLQuery = new HashMap<>();
            }
            mURLQuery.put(escapedField, escapedValue);

        } catch (UnsupportedEncodingException ignored) {
        }
    }

    public void setRequestHeader(String field, String value) {
        if (StringUtil.isEmpty(field) || StringUtil.isEmpty(value)) {
            return;
        }

        if (mRequestHeader == null) {
            mRequestHeader = new HashMap<>();
        }
        mRequestHeader.put(field, value);
    }

    //if set a RequestBodyReader, the session will use it to get request body,
    //else the request body from value set by setRequestBodyData().
    public void setRequestBodyReader(RequestBodyReader reader) {
        mRequestBodyReader = reader;
    }

    public void setRequestBodyData(byte[] data) {
        mRequestBodyData = data;
    }

    public void syncResume() throws IOException {

        //reset:
        mResponseCode = 0;
        mResponseHeader = null;
        mResponseBodyData = null;

        //send:
        boolean[] canWriteRequestBody = new boolean[1];
        HttpURLConnection connection = openConnection(canWriteRequestBody);

        if (canWriteRequestBody[0]) {
            OutputStream requestBodyStream = connection.getOutputStream();
            writeRequestBody(requestBodyStream);
        }

        //receive:
        mResponseCode = connection.getResponseCode();
        mResponseHeader = new HashMap<>();
        for (Map.Entry<String, List<String>> entry : connection.getHeaderFields().entrySet()) {
            String field = entry.getKey();
            if (field == null) {
                //this is response's first line("HTTP/0.0 000 xx").
                continue;
            }
            List<String> value = entry.getValue();
            if (value == null || value.size() == 0) {
                continue;
            }
            mResponseHeader.put(field, value.get(0));
        }

        InputStream responseBodyStream = connection.getInputStream();
        readResponseBody(responseBodyStream);

        connection.disconnect();
    }

    protected HttpURLConnection openConnection(boolean[] canWriteRequestBody) throws IOException {

        StringBuilder urlQuery = new StringBuilder();
        if (mURLQuery != null) {
            for (Map.Entry<String, String> entry : mURLQuery.entrySet()) {
                urlQuery.append(urlQuery.length() == 0 ? "?" : "&");
                urlQuery.append(entry.getKey());
                urlQuery.append("=");
                urlQuery.append(entry.getValue());
            }
        }

        URL url = new URL(mURLString + urlQuery);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setConnectTimeout((int)(mTimeoutSeconds * 1000));
        connection.setReadTimeout((int)(mTimeoutSeconds * 1000));

        //"GET" is default
        if (StringUtil.isNonEmpty(mMethod)) {
            connection.setRequestMethod(mMethod.toUpperCase());
        } else {
            connection.setRequestMethod("GET");
        }

        //"GET" method don't contain body, also android api don't allow this behaviour.
        boolean httpGET = connection.getRequestMethod().equals("GET");
        canWriteRequestBody[0] = !httpGET;

        connection.setDoOutput(canWriteRequestBody[0]);
        connection.setDoInput(true);

        if (mResponseHeader != null) {
            for (Map.Entry<String, String> entry : mRequestHeader.entrySet()) {
                connection.addRequestProperty(entry.getKey(), entry.getValue());
            }
        }

        return connection;
    }

    protected void writeRequestBody(OutputStream stream) throws IOException {

        //unresolved problem:
        //
        //how to judge that OutputStream is not writable ?
        //
        //if the network speed is slow but data need to be transmitted is very large,
        //the data can only be cached in memory.
        //continuously write will cause a OutOfMemoryException.

        if (mRequestBodyReader != null) {

            byte[] buffer = new byte[1024 * 8];
            while (true) {
                int length = mRequestBodyReader.read(this, buffer);
                if (length > 0) {
                    stream.write(buffer, 0, length);
                }
                //if no more data can be read, RequestBodyReader return -1.
                if (length <= -1) {
                    break;
                }
            }

        } else if (mRequestBodyData != null) {

            stream.write(mRequestBodyData);
        }
    }

    protected void readResponseBody(InputStream stream) throws IOException {

        byte[] buffer = new byte[1024 * 8];
        int length;

        if (mResponseBodyWriter != null) {
            while ((length = stream.read(buffer)) != -1) {
                byte[] copy = Arrays.copyOf(buffer, length);
                boolean goon = mResponseBodyWriter.write(this, copy);
                if (!goon) {
                    break;
                }
            }
        } else {
            ByteArrayOutputStream data = new ByteArrayOutputStream();
            while ((length = stream.read(buffer)) != -1) {
                data.write(buffer, 0, length);
            }
            mResponseBodyData = data.toByteArray();
        }
    }

    public int getResponseCode() {
        return mResponseCode;
    }

    public HashMap<String, String> getResponseHeader() {
        return mResponseHeader;
    }

    //if set a ResponseBodyWriter, the session will use it to write response body,
    //else the response body stored into internal data, which can be get by getResponseBodyData().
    public void setResponseBodyWriter(ResponseBodyWriter writer) {
        mResponseBodyWriter = writer;
    }

    public byte[] getResponseBodyData() {
        return mResponseBodyData;
    }

    public void setTimeoutSeconds(float timeoutSeconds) {
        mTimeoutSeconds = timeoutSeconds;
    }
}
