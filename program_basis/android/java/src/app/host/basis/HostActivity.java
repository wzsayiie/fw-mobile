package src.app.host.basis;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;
import android.view.MotionEvent;

import java.util.Timer;
import java.util.TimerTask;

public class HostActivity extends Activity implements GLView.Renderer {

    static {
        System.loadLibrary("cargo");
    }

    private static HostActivity sActivity;

    @SuppressWarnings("unused") /* the activity can be found dynamically */
    public static Activity sharedInstance() {
        //NOTE: this method will be called on non-ui thread.
        return sActivity;
    }

    private float   mScreenDensity;
    private int     mWidthPixels;
    private int     mHeightPixels;
    private GLView  mView;
    private boolean mViewVisible;
    private long    mWid;
    private boolean mWindowCreated;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        sActivity = this;

        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);

        mScreenDensity = metrics.density;
        mWid = hashCode();
        mView = new GLView(this);
        mView.setRenderer(this);
        setContentView(mView);

        TimerTask timerTask = new TimerTask() {
            @Override
            public void run() {
                new Handler(Looper.getMainLooper()).post(() -> update());
            }
        };
        Timer timer = new Timer();
        timer.schedule(timerTask, 30, 30);
    }

    @Override
    protected void onStart() {
        super.onStart();
        mViewVisible = true;

        if (mWindowCreated) {
            notifyWindowAppear(mWid);
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        mViewVisible = false;

        if (mWindowCreated) {
            notifyWindowDisappear(mWid);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        sActivity = null;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (!mWindowCreated) {
            return true;
        }

        float x = event.getX() / mScreenDensity;
        float y = event.getY() / mScreenDensity;
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN  : notifyWindowTouchBegan(mWid, x, y); break;
            case MotionEvent.ACTION_MOVE  : notifyWindowTouchMoved(mWid, x, y); break;
            case MotionEvent.ACTION_UP    : notifyWindowTouchEnded(mWid, x, y); break;
            case MotionEvent.ACTION_CANCEL: notifyWindowTouchEnded(mWid, x, y); break;
        }
        return true;
    }

    @SuppressWarnings("unused") /* called by native code */
    protected static long create_window() {
        return sActivity.createWindow();
    }
    @SuppressWarnings("unused") /* called by native code */
    protected static void show_window(long wid) {
        sActivity.showWindow(wid);
    }

    protected long createWindow() {

        //only one window can be created on android
        if (mWindowCreated) {
            return 0;
        }

        mWindowCreated = true;
        return mWid;
    }

    protected void showWindow(long wid) {
        if (!mWindowCreated || wid != mWid) {
            return;
        }

        float width  = mWidthPixels  / mScreenDensity;
        float height = mHeightPixels / mScreenDensity;

        notifyWindowScale (wid, mScreenDensity);
        notifyWindowOrigin(wid, 0, 0);
        notifyWindowSize  (wid, width, height);
        notifyWindowLoad  (wid);

        if (mViewVisible) {
            notifyWindowAppear(wid);
        }
    }

    public void onGLViewLoad(int width, int height) {
        mWidthPixels  = width ;
        mHeightPixels = height;

        installInterfaces();
        
        //NOTE: call entry function here.
    }

    public void onGLViewResize(int width, int height) {
        mWidthPixels  = width ;
        mHeightPixels = height;

        if (mWindowCreated) {
            notifyWindowSize(mWid, width, height);
        }
    }

    public void onGLViewDraw() {
        if (mWindowCreated) {
            notifyWindowGLDraw(mWid);
        }
    }

    public void update() {
        if (mWindowCreated) {
            notifyWindowUpdate(mWid);
        }
        mView.update();
    }

    protected native void installInterfaces();

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
