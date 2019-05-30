package src.app.host.cpp;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CPPActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    @SuppressLint("StaticFieldLeak") /* there is only activity instance in app */
    private static CPPActivity sSharedActivity = null;

    @SuppressWarnings("unused") /* called by native code */
    public static long create_window() {
        return sSharedActivity.createWindow();
    }
    @SuppressWarnings("unused") /* called by native code */
    public static void show_window(long wid) {
        sSharedActivity.showWindow(wid);
    }

    private boolean mStarted;
    private boolean mAttached;
    private float   mDensity;
    private float   mWidthPixels;
    private float   mHeightPixels;

    protected long getWid() {
        return hashCode();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sSharedActivity = this;

        //currently open-gl 2.0 is supported
        GLSurfaceView view = new GLSurfaceView(this);
        view.setEGLContextClientVersion(2);
        view.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
                onGLViewCreated();
            }
            @Override
            public void onSurfaceChanged(GL10 gl10, int width, int height) {
                onGLViewResized(width, height);
            }
            @Override
            public void onDrawFrame(GL10 gl10) {
                onGLViewDraw();
            }
        });
        setContentView(view);

        installInterfaces();
        notifyAppStartup();
    }

    @Override
    protected void onStart() {
        super.onStart();

        if (mAttached && !mStarted) {
            notifyWindowAppear(getWid());
            mStarted = true;
        }
    }

    @Override
    protected void onStop() {
        super.onStop();

        if (mAttached && mStarted) {
            mStarted = false;
            notifyWindowDisappear(getWid());
        }
    }

    private long createWindow() {

        //only one window can be created on android
        if (mAttached) {
            return 0;
        }

        mAttached = true;
        return sSharedActivity.getWid();
    }

    private void showWindow(long wid) {
        if (!mAttached || wid != getWid()) {
            return;
        }

        Display display = getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        mDensity      = metrics.density;
        mWidthPixels  = metrics.widthPixels;
        mHeightPixels = metrics.heightPixels;

        notifyWindowScale (wid, mDensity);
        notifyWindowOrigin(wid, 0, 0);
        notifyWindowSize  (wid, mWidthPixels / mDensity, mHeightPixels / mDensity);
        notifyWindowLoad  (wid);

        if (sSharedActivity.mStarted) {
            notifyWindowAppear(wid);
        }
    }

    protected void onGLViewCreated() {
    }

    protected void onGLViewResized(int width, int height) {
        GLES20.glViewport(0, 0, width, height);

        if (!mAttached) {
            return;
        }

        if (mWidthPixels != width || mHeightPixels != height) {
            mWidthPixels = width;
            mHeightPixels = height;
            notifyWindowSize(getWid(), width / mDensity, height / mDensity);
        }
    }

    public void onGLViewDraw() {
        if (!mAttached) {
            return;
        }

        notifyWindowGLDraw(getWid());
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (!mAttached || !mStarted) {
            return true;
        }

        float x = event.getX() / mDensity;
        float y = event.getY() / mDensity;

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN  : notifyWindowTouchBegan(getWid(), x, y); break;
            case MotionEvent.ACTION_MOVE  : notifyWindowTouchMoved(getWid(), x, y); break;
            case MotionEvent.ACTION_UP    : notifyWindowTouchEnded(getWid(), x, y); break;
            case MotionEvent.ACTION_CANCEL: notifyWindowTouchEnded(getWid(), x, y); break;
        }
        return true;
    }

    protected native void installInterfaces();

    protected native void notifyAppStartup();

    protected native void notifyWindowScale    (long wid, float scale);
    protected native void notifyWindowOrigin   (long wid, float x, float y);
    protected native void notifyWindowSize     (long wid, float width, float height);
    protected native void notifyWindowLoad     (long wid);
    protected native void notifyWindowGLDraw   (long wid);
    protected native void notifyWindowAppear   (long wid);
    protected native void notifyWindowDisappear(long wid);

    @SuppressWarnings("unused") /* on android 'unload' event is invalid */
    protected native void notifyWindowUnload(long wid);

    protected native void notifyWindowTouchBegan(long wid, float x, float y);
    protected native void notifyWindowTouchMoved(long wid, float x, float y);
    protected native void notifyWindowTouchEnded(long wid, float x, float y);
}
