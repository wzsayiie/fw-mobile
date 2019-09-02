package src.library.glkit;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.view.MotionEvent;

import java.util.Timer;
import java.util.TimerTask;

public class GLActivity extends Activity implements GLView.Renderer {

    static {
        //'cargo' will load implicitly 'library'.
        System.loadLibrary("cargo");
    }

    private static GLActivity sActivity;

    private GLView mView;
    private Timer mTimer;

    @SuppressWarnings("unused") /* the activity can be found dynamically */
    public static Activity sharedInstance() {
        //NOTE: this method will be called on non-ui thread.
        return sActivity;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sActivity = this;

        mView = new GLView(this);
        mView.setRenderer(this);
        setContentView(mView);

        TimerTask timerTask = new TimerTask() {
            @Override
            public void run() {
                Handler handler = new Handler(Looper.getMainLooper());
                handler.post(GLActivity.this::timeout);
            }
        };
        mTimer = new Timer();
        mTimer.schedule(timerTask, 30, 30);
    }

    @Override
    protected void onStart() {
        super.onStart();
        setWindowAppearIfNeeded();
    }

    @Override
    protected void onStop() {
        super.onStop();
        setWindowDisappearIfNeeded();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        mTimer.cancel();
        sActivity = null;
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        setWindowTouchEventIfNeeded(e.getAction(), (int)e.getX(), (int)e.getY());
        return true;
    }

    public void onGLViewLoad(int width, int height) {
        if (initializeIfNeeded(this, width, height)) {
            invokeEntry();
        }
    }

    protected void invokeEntry() {
        //NOTE: call entry function here.
    }

    public void onGLViewResize(int width, int height) {
        setWindowSizeIfNeeded(width, height);
    }

    protected void timeout() {
        //NOTE: update data above all, after paint ui.
        setWindowUpdateIfNeeded();
        mView.update();
    }

    public void onGLViewPaint() {
        setWindowGLPaintIfNeeded();
    }

    //store values as static date.
    //if app entries to background, the activity will be release possibly.
    private static boolean sInitialized;
    private static float   sScreenDensity;
    private static int     sWidthPixels;
    private static int     sHeightPixels;
    private static boolean sWantVisible;
    private static boolean sVisible;
    private static long    sWid;

    protected static boolean initializeIfNeeded(Activity activity, int widthPixels, int heightPixels) {
        if (sInitialized) {
            return false;
        }
        sInitialized = true;

        DisplayMetrics metrics = new DisplayMetrics();
        activity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
        sWidthPixels = widthPixels;
        sHeightPixels = heightPixels;
        sScreenDensity = metrics.density;

        installInterfaces();

        return true;
    }

    @SuppressWarnings("unused") /* called by native code */
    protected static long create_window() {

        //only one window can be created on android
        if (sWid != 0) {
            return 0;
        }

        sWid = 1;
        return sWid;
    }

    @SuppressWarnings("unused") /* called by native code */
    protected static void show_window(long wid) {
        if (wid != sWid) {
            return;
        }

        float width  = sWidthPixels  / sScreenDensity;
        float height = sHeightPixels / sScreenDensity;

        windowScale (wid, sScreenDensity);
        windowOrigin(wid, 0, 0);
        windowSize  (wid, width, height);
        windowLoad  (wid);

        if (sWantVisible) {
            sVisible = true;
            windowAppear(wid);
        }
    }

    private static void setWindowSizeIfNeeded(int width, int height) {
        sWidthPixels  = width ;
        sHeightPixels = height;

        if (sWid != 0) {
            float w = sWidthPixels  / sScreenDensity;
            float h = sHeightPixels / sScreenDensity;
            windowSize(sWid, w, h);
        }
    }

    protected static void setWindowAppearIfNeeded() {
        sWantVisible = true;

        if (sWid != 0 && !sVisible) {
            sVisible = true;
            windowAppear(sWid);
        }
    }

    private static void setWindowDisappearIfNeeded() {
        sWantVisible = false;

        if (sWid != 0 && sVisible) {
            sVisible = false;
            windowDisappear(sWid);
        }
    }

    private static void setWindowTouchEventIfNeeded(int action, int xPixels, int yPixels) {
        if (sWid == 0 || !sVisible) {
            return;
        }

        float x = xPixels / sScreenDensity;
        float y = yPixels / sScreenDensity;
        switch (action) {
            case MotionEvent.ACTION_DOWN  : windowPBegan(sWid, x, y); break;
            case MotionEvent.ACTION_MOVE  : windowPMoved(sWid, x, y); break;
            case MotionEvent.ACTION_UP    : windowPEnded(sWid, x, y); break;
            case MotionEvent.ACTION_CANCEL: windowPEnded(sWid, x, y); break;
        }
    }

    private static void setWindowUpdateIfNeeded() {
        if (sWid == 0) {
            return;
        }

        windowUpdate(sWid);
    }

    private static void setWindowGLPaintIfNeeded() {
        if (sWid == 0) {
            return;
        }

        //only paint window when it's visible, that's different with windowUpdate().
        if (sVisible) {
            windowGLPaint(sWid);
        }
    }

    protected static native void installInterfaces();

    protected static native void windowLoad     (long wid);
    protected static native void windowAppear   (long wid);
    protected static native void windowDisappear(long wid);

    @SuppressWarnings("unused") /* on android 'unload' event is invalid */
    protected static native void windowUnload(long wid);

    protected static native void windowScale  (long wid, float scale);
    protected static native void windowOrigin (long wid, float x, float y);
    protected static native void windowSize   (long wid, float width, float height);
    protected static native void windowUpdate (long wid);
    protected static native void windowGLPaint(long wid);

    protected static native void windowPBegan(long wid, float x, float y);
    protected static native void windowPMoved(long wid, float x, float y);
    protected static native void windowPEnded(long wid, float x, float y);
}
