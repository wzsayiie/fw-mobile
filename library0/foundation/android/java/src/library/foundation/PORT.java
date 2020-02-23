package src.library.foundation;

import android.util.LongSparseArray;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;

import src.library.basis.CPtr;
import src.library.basis.JNI;
import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class PORT {

    //log:

    public static void cq_log_info(String file, int line, String message) {
        L.info(file, line, message);
    }

    public static void cq_log_error(String file, int line, String message) {
        L.error(file, line, message);
    }

    //app bundle resource:

    public static CPtr cq_android_asset(String name) {
        byte[] asset = AssetAssist.getAsset(name);
        return JNI.storeBytes(asset);
    }

    public static boolean cq_android_copy_asset(String fromPath, String toPath) {
        return AssetAssist.copyAsset(fromPath, toPath);
    }

    //file access:

    public static String cq_document_directory() {
        return FileAssist.filesDir();
    }

    public static String cq_caches_directory() {
        return FileAssist.cacheDir();
    }

    public static String cq_temporary_directory() {
        return FileAssist.cacheDir();
    }

    public static boolean cq_directory_exists(String path) {
        return FileAssist.directoryExists(path);
    }

    public static boolean cq_file_exists(String path) {
        return FileAssist.fileExists(path);
    }

    public static boolean cq_create_directory(String path, boolean intermediate) {
        return FileAssist.createDirectory(path, intermediate);
    }

    public static void cq_remove_path(String path) {
        FileAssist.removePath(path);
    }

    public static CPtr cq_sub_files(String path) {
        ArrayList<String> items = FileAssist.listSubItems(path, null);
        return JNI.storeStrings(items);
    }

    //thread:

    public static void cq_thread_run(long task, long data) {
        ThreadAssist.run(() -> threadBody(task, data));
    }

    private static native void threadBody(long task, long data);

    public static void cq_thread_sleep(float seconds) {
        ThreadAssist.sleepForSeconds(seconds);
    }

    //main run loop:

    public static void cq_main_loop_post(long task, long data) {
        LooperAssist.runOnMainLoop(() -> looperTaskBody(task, data));
    }

    private static native void looperTaskBody(long task, long data);
    
    //http:
    
    private static class HttpSessionPort extends HttpSession {
        
        private long mRequestBodyReader;
        private long mResponseCodeWriter;
        private long mResponseHeaderWriter;
        private long mResponseBodyWriter;

        private boolean mWaitResponse;
        private long mUserData;
        private String mError;

        void setRequestBodyReader(long reader) {
            mRequestBodyReader = reader;
        }

        void setResponseCodeWriter(long writer) {
            mResponseCodeWriter = writer;
        }

        void setResponseHeaderWriter(long writer) {
            mResponseHeaderWriter = writer;
        }

        void setResponseBodyWriter(long writer) {
            mResponseBodyWriter = writer;
        }
        
        void syncResume(long userData) {

            mWaitResponse = true;
            mUserData = userData;
            mError = null;

            setRequestBodyReader(this::onReadRequestBody);
            setResponseBodyWriter(this::onWriteResponseBody);

            try {
                syncResume();
            } catch (IOException e) {
                mError = e.toString();
            }
        }

        int onReadRequestBody(HttpSession session, byte[] buffer) {
            if (mRequestBodyReader != 0) {
                return httpReadRequestBody(mRequestBodyReader, mUserData, buffer);
            } else {
                return -1;
            }
        }

        void onWriteResponseHeader(HttpSession session) {
            if (mResponseCodeWriter != 0) {
                int responseCode = session.getResponseCode();
                httpWriteResponseCode(mResponseCodeWriter, mUserData, responseCode);
            }

            if (mResponseHeaderWriter != 0) {
                for (Map.Entry<String, String> cp : session.getResponseHeader().entrySet()) {
                    String field = cp.getKey();
                    String value = cp.getValue();
                    httpWriteResponseHeader(mResponseHeaderWriter, mUserData, field, value);
                }
            }
        }

        boolean onWriteResponseBody(HttpSession session, byte[] data) {
            if (mWaitResponse) {
                onWriteResponseHeader(session);
                mWaitResponse = false;
            }

            if (mResponseBodyWriter != 0) {
                return httpWriteResponseBody(mResponseBodyWriter, mUserData, data);
            } else {
                return true;
            }
        }

        String getError() {
            return mError;
        }
    }

    private static native int     httpReadRequestBody    (long reader, long userData, byte[] buffer);
    private static native void    httpWriteResponseCode  (long writer, long userData, int responseCode);
    private static native void    httpWriteResponseHeader(long writer, long userData, String field, String value);
    private static native boolean httpWriteResponseBody  (long writer, long userData, byte[] data);

    private static LongSparseArray<HttpSessionPort> sHttpSessionPortArray = null;
    
    private static LongSparseArray<HttpSessionPort> getHttpSessionPortArray() {
        if (sHttpSessionPortArray == null) {
            sHttpSessionPortArray = new LongSparseArray<>();
        }
        return sHttpSessionPortArray;
    }

    public static long cq_http_create() {
        HttpSessionPort port = new HttpSessionPort();
        getHttpSessionPortArray().put(port.hashCode(), port);
        return port.hashCode();
    }

    public static void cq_http_destroy(long http) {
        getHttpSessionPortArray().remove(http);
    }

    public static void cq_http_timeout(long http, float seconds) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setTimeoutSeconds(seconds);
        }
    }

    public static void cq_http_send_method(long http, String method) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setMethod(method);
        }
    }

    public static void cq_http_send_url(long http, String url) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setURLString(url);
        }
    }

    public static void cq_http_send_query(long http, String field, String value) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setURLQuery(field, value);
        }
    }

    public static void cq_http_send_header(long http, String field, String value) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setRequestHeader(field, value);
        }
    }

    public static void cq_http_send_body_from(long http, long reader) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setRequestBodyReader(reader);
        }
    }

    public static void cq_http_recv_code_to(long http, long writer) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setResponseCodeWriter(writer);
        }
    }

    public static void cq_http_recv_header_to(long http, long writer) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setResponseHeaderWriter(writer);
        }
    }

    public static void cq_http_recv_body_to(long http, long writer) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.setResponseBodyWriter(writer);
        }
    }

    public static void cq_http_sync(long http, long user) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        if (port != null) {
            port.syncResume(user);
        }
    }

    public static String cq_http_error(long http) {
        HttpSessionPort port = getHttpSessionPortArray().get(http);
        return port != null ? port.getError() : null;
    }
}
