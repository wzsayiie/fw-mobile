package src.library.foundation;

import java.io.IOException;
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
        CFunc.setStringList(items, out);
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

        private static final int SEND_BODY = 1;
        private static final int RECV_BODY = 2;

        public CPtr   Port;
        public String Error;

        public boolean SendBodyFinish;
        public byte[]  SendBodyBuffer;
        public int     SendBodyLength;

        public byte[]  ReceiveBodyData;
        public boolean ReceiveBodyStop;

        public HttpSessionBridge() {
            setRequestBodyReader (this::onReadRequestBody  );
            setResponseBodyWriter(this::onWriteResponseBody);
        }

        public void syncResume() {
            try {
                SendBodyFinish = false;
                Error = null;
                super.syncResume();
            } catch (IOException e) {
                Error = e.toString();
            }
        }

        private int onReadRequestBody(HttpSession session, byte[] buffer) {
            //NOTE: if transfer finished, return -1.
            if (SendBodyFinish) {
                return -1;
            }

            SendBodyBuffer = buffer;
            SendBodyLength = 0;
            CObject.emit(Port, SEND_BODY);

            //REMEMBER: assign the reference to null.
            SendBodyBuffer = null;

            if (SendBodyLength > 0) {
                return SendBodyLength;
            }

            if (SendBodyFinish) {
                return -1;
            } else {
                //no data this time.
                return 0;
            }
        }

        private boolean onWriteResponseBody(HttpSession session, byte[] data) {
            ReceiveBodyData = data;
            ReceiveBodyStop = false;
            CObject.emit(Port, RECV_BODY);

            //REMEMBER: assign reference to null.
            ReceiveBodyData = null;

            //NOTE:
            //  boolean continue = !ReceiveBodyStop;
            //  return continue;
            return !ReceiveBodyStop;
        }
    }

    public static CPtr cq_http_create() {
        HttpSessionBridge object = new HttpSessionBridge();
        CPtr port = CObject.retain(object, "HTTPSession");

        object.Port = port;

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
            object.syncResume();
        }
    }

    public static int cq_http_send_body_cap(CPtr http) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            return object.SendBodyBuffer.length;
        } else {
            return 0;
        }
    }

    public static void cq_http_send_body(CPtr http, CPtr bytesIn, boolean finish) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            byte[] data = CFunc.getBytes(bytesIn);
            System.arraycopy(data, 0, object.SendBodyBuffer, 0, data.length);
            object.SendBodyFinish = finish;
        }
    }

    public static void cq_http_recv_body(CPtr http, CPtr bytesOut) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            CFunc.set(object.ReceiveBodyData, bytesOut);
        }
    }

    public static void cq_http_recv_stop(CPtr http, boolean stop) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            object.ReceiveBodyStop = stop;
        }
    }

    public static String cq_http_error(CPtr http) {
        HttpSessionBridge object = CObject.raw(http, HttpSessionBridge.class);
        if (object != null) {
            return object.Error;
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
