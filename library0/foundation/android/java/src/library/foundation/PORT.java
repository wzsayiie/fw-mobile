package src.library.foundation;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;

import src.library.basis.CBlock;
import src.library.basis.CFunc;
import src.library.basis.CObject;
import src.library.basis.CPtr;
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

    public static void cq_android_asset(String name, CPtr out) {
        byte[] asset = AssetAssist.getAsset(name);
        CFunc.set(asset, out);
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

    public static void cq_sub_files(String path, CPtr out) {
        ArrayList<String> items = FileAssist.listSubItems(path, null);
        CFunc.set(items, out);
    }

    //thread:

    public static void cq_thread_run(CPtr runnable, CPtr data) {
        ThreadAssist.run(() -> CBlock.run(runnable, data));
    }

    public static void cq_thread_sleep(float seconds) {
        ThreadAssist.sleepForSeconds(seconds);
    }

    //main run loop:

    public static void cq_main_loop_post(CPtr runnable, CPtr data) {
        LooperAssist.runOnMainLoop(() -> CBlock.run(runnable, data));
    }

    //http:
    
    private static class HttpSessionBridge extends HttpSession {

        private CPtr mPort;
        private String mError;

        public HttpSessionBridge() {
            setRequestBodyReader (this::onReadRequestBody  );
            setResponseBodyWriter(this::onWriteResponseBody);
        }

        public void setPort(CPtr port) {
            mPort = port;
        }

        public void setError(String error) {
            mError = error;
        }

        public String getError() {
            return mError;
        }

        private int onReadRequestBody(HttpSession session, byte[] buffer) {

            ByteBuffer byteBuffer = ByteBuffer.allocate(0);
            boolean[] stop = new boolean[1];

            CBlock.out("buffer", byteBuffer);
            CBlock.in("capacity", buffer.length);
            CBlock.out("stop", stop);
            CObject.emit(mPort, 1 /* cq_http_e_send_body */);

            byte[] byteData = byteBuffer.array();
            int    byteSize = byteBuffer.array().length;

            if (byteSize > 0) {
                System.arraycopy(byteData, 0, buffer, 0, byteSize);
            }

            if (!stop[0]) {
                return byteSize;
            } else {
                return -1;
            }
        }

        private boolean onWriteResponseBody(HttpSession session, byte[] data) {
            boolean[] stop = new boolean[1];

            CBlock.in("body", data);
            CBlock.out("stop", stop);
            CObject.emit(mPort, 2 /* cq_http_e_recv_body */);

            return !stop[0];
        }
    }

    public static CPtr cq_http_create() {
        HttpSessionBridge object = new HttpSessionBridge();
        CPtr port = CObject.retain(object, "HTTPSession");

        object.setPort(port);

        return port;
    }

    public static void cq_http_timeout(CPtr http, float seconds) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.setTimeoutSeconds(seconds);
        }
    }

    public static void cq_http_send_method(CPtr http, String method) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.setMethod(method);
        }
    }

    public static void cq_http_send_url(CPtr http, String url) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.setURLString(url);
        }
    }

    public static void cq_http_send_query(CPtr http, String field, String value) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.setURLQuery(field, value);
        }
    }

    public static void cq_http_send_header(CPtr http, String field, String value) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.setRequestHeader(field, value);
        }
    }

    public static void cq_http_sync(CPtr http) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            try {
                object.setError(null);
                object.syncResume();
            } catch (IOException e) {
                object.setError(e.toString());
            }
        }
    }

    public static String cq_http_error(CPtr http) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            return object.getError();
        } else {
            return null;
        }
    }

    public static int cq_http_recv_code(CPtr http) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            return object.getResponseCode();
        } else {
            return 0;
        }
    }

    public static void cq_http_recv_header(CPtr http, CPtr out) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            HashMap<String, String> header = object.getResponseHeader();
            CFunc.set(header, out);
        }
    }
}
