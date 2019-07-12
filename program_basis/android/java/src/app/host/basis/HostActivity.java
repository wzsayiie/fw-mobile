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
        //'cargo' will load implicitly 'library'.
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
            windowAppear(mWid);
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        mViewVisible = false;

        if (mWindowCreated) {
            windowDisappear(mWid);
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
            case MotionEvent.ACTION_DOWN  : windowPBegan(mWid, x, y); break;
            case MotionEvent.ACTION_MOVE  : windowPMoved(mWid, x, y); break;
            case MotionEvent.ACTION_UP    : windowPEnded(mWid, x, y); break;
            case MotionEvent.ACTION_CANCEL: windowPEnded(mWid, x, y); break;
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

        windowScale (wid, mScreenDensity);
        windowOrigin(wid, 0, 0);
        windowSize  (wid, width, height);
        windowLoad  (wid);

        if (mViewVisible) {
            windowAppear(wid);
        }
    }

    public void onGLViewLoad(int width, int height) {
        mWidthPixels  = width ;
        mHeightPixels = height;

        initInterfaces();
        
        //NOTE: call entry function here.
    }

    public void onGLViewResize(int width, int height) {
        mWidthPixels  = width ;
        mHeightPixels = height;

        if (mWindowCreated) {
            windowSize(mWid, width, height);
        }
    }

    public void onGLViewDraw() {
        if (mWindowCreated) {
            windowGLPaint(mWid);
        }
    }

    public void update() {
        if (!mViewVisible) {
            return;
        }

        if (mWindowCreated) {
            windowUpdate(mWid);
        }
        mView.update();
    }

    protected native void initInterfaces();

    protected native void windowLoad     (long wid);
    protected native void windowAppear   (long wid);
    protected native void windowDisappear(long wid);

    @SuppressWarnings("unused") /* on android 'unload' event is invalid */
    protected native void windowUnload(long wid);

    protected native void windowScale  (long wid, float scale);
    protected native void windowOrigin (long wid, float x, float y);
    protected native void windowSize   (long wid, float width, float height);
    protected native void windowGLPaint(long wid);
    protected native void windowUpdate (long wid);

    protected native void windowPBegan(long wid, float x, float y);
    protected native void windowPMoved(long wid, float x, float y);
    protected native void windowPEnded(long wid, float x, float y);
}
