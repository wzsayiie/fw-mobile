package src.app.host;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.MotionEvent;

import java.util.ArrayList;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class HostActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    //constant variables, initializing before gl thread created:

    @SuppressLint("StaticFieldLeak")
    private static HostActivity sActivity;

    private static float sDensity;
    private static long sWid;

    @SuppressWarnings("unused") /* the activity can be found dynamically */
    public static Activity sharedInstance() {
        //NOTE: this method will be called on non-ui thread.
        return sActivity;
    }

    //shared variables between main thread and gl thread:

    protected static class TouchItem {

        int action;
        int pixelX;
        int pixelY;

        TouchItem(int action, int pixelX, int pixelY) {
            this.action = action;
            this.pixelX = pixelX;
            this.pixelY = pixelY;
        }
    }

    private final Object mSharedTouchListLock = new Object();
    private final Object mSharedVisibleLock = new Object();

    private ArrayList<TouchItem> mSharedTouchList;
    private boolean mSharedVisible;

    //on main thread:

    private GLSurfaceView mContentView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);

        sActivity = this;
        sDensity = metrics.density;
        sWid = hashCode();

        //currently open-gl 2.0 is supported
        mContentView = new GLSurfaceView(this);
        mContentView.setEGLContextClientVersion(2);
        mContentView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig eglConfig) {
            }
            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                onGLThreadViewResized(width, height);
            }
            @Override
            public void onDrawFrame(GL10 gl10) {
                onGLThreadViewDraw();
            }
        });
        setContentView(mContentView);
    }

    @Override
    protected void onStart() {
        super.onStart();

        synchronized (mSharedVisibleLock) {
            mSharedVisible = true;
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        mContentView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mContentView.onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();

        synchronized (mSharedVisibleLock) {
            mSharedVisible = false;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        int a = event.getAction();
        int x = (int)event.getX();
        int y = (int)event.getY();
        TouchItem item = new TouchItem(a, x, y);

        synchronized (mSharedTouchListLock) {
            if (mSharedTouchList == null) {
                mSharedTouchList = new ArrayList<>();
            }
            mSharedTouchList.add(item);
        }

        return true;
    }

    //on open-gl thread:

    @SuppressWarnings("unused") /* called by native code */
    protected static long create_window() {
        return sActivity.createWindow();
    }
    @SuppressWarnings("unused") /* called by native code */
    protected static void show_window(long wid) {
        sActivity.showWindow(wid);
    }

    private boolean mGLAppLaunched;
    private boolean mGLWindowAttached;
    private boolean mGLVisible;
    private int mGLWidthPixels;
    private int mGLHeightPixels;

    protected void onGLThreadViewResized(int width, int height) {
        GLES20.glViewport(0, 0, width, height);

        mGLWidthPixels  = width ;
        mGLHeightPixels = height;

        if (!mGLAppLaunched) {
            mGLAppLaunched = true;
            installInterfaces();
            notifyAppLaunch();
        } else if (mGLWindowAttached) {
            notifyWindowSize(sWid, width, height);
        }
    }

    protected long createWindow() {

        //only one window can be created on android
        if (mGLWindowAttached) {
            return 0;
        }

        mGLWindowAttached = true;
        return sWid;
    }

    protected void showWindow(long wid) {
        if (!mGLWindowAttached || wid != sWid) {
            return;
        }

        notifyWindowScale (wid, sDensity);
        notifyWindowOrigin(wid, 0, 0);
        notifyWindowSize  (wid, mGLWidthPixels / sDensity, mGLHeightPixels / sDensity);
        notifyWindowLoad  (wid);

        synchronized (mSharedVisibleLock) {
            mGLVisible = mSharedVisible;
        }
        if (mGLVisible) {
            notifyWindowAppear(wid);
        }
    }

    protected void onGLThreadViewDraw() {
        if (!mGLWindowAttached) {
            return;
        }

        //visible event
        boolean currentVisible;
        synchronized (mSharedVisibleLock) {
            currentVisible = mSharedVisible;
        }

        if (!mGLVisible && currentVisible) {
            notifyWindowAppear(sWid);
        } else if (mGLVisible && !currentVisible) {
            notifyWindowDisappear(sWid);
        }
        mGLVisible = currentVisible;

        //touch event
        ArrayList<TouchItem> list;
        synchronized (mSharedTouchListLock) {
            list = mSharedTouchList;
            mSharedTouchList = null;
        }

        if (list != null) {
            for (TouchItem item : list) {
                float x = item.pixelX / sDensity;
                float y = item.pixelY / sDensity;
                switch (item.action) {
                    case MotionEvent.ACTION_DOWN  : notifyWindowTouchBegan(sWid, x, y); break;
                    case MotionEvent.ACTION_MOVE  : notifyWindowTouchMoved(sWid, x, y); break;
                    case MotionEvent.ACTION_UP    : notifyWindowTouchEnded(sWid, x, y); break;
                    case MotionEvent.ACTION_CANCEL: notifyWindowTouchEnded(sWid, x, y); break;
                }
            }
        }

        //draw
        notifyWindowGLDraw(sWid);

        //update
        notifyWindowUpdate(sWid);
    }

    protected native void installInterfaces();

    protected native void notifyAppLaunch();

    protected native void notifyWindowLoad     (long wid);
    protected native void notifyWindowAppear   (long wid);
    protected native void notifyWindowDisappear(long wid);

    @SuppressWarnings("unused") /* on android 'unload' event is invalid */
    protected native void notifyWindowUnload(long wid);

    protected native void notifyWindowScale (long wid, float scale);
    protected native void notifyWindowOrigin(long wid, float x, float y);
    protected native void notifyWindowSize  (long wid, float width, float height);
    protected native void notifyWindowGLDraw(long wid);
    protected native void notifyWindowUpdate(long wid);

    protected native void notifyWindowTouchBegan(long wid, float x, float y);
    protected native void notifyWindowTouchMoved(long wid, float x, float y);
    protected native void notifyWindowTouchEnded(long wid, float x, float y);
}
