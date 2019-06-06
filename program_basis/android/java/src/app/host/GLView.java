package src.app.host;

import android.content.Context;
import android.opengl.EGL14;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;

public class GLView extends SurfaceView implements SurfaceHolder.Callback {

    public interface Renderer {
        void onGLViewLoad(int width, int height);
        void onGLViewResize(int width, int height);
        void onGLViewDraw();
    }

    //currently open-gl 2.0 is supported
    private static final int GL_ES_VERSION = EGL14.EGL_OPENGL_ES2_BIT;
    private static final int EGL_VERSION = 2;

    private Renderer mRenderer;
    private boolean  mAttached;

    private EGL10      mEGL;
    private EGLDisplay mEGLDisplay;
    private EGLConfig  mEGLConfig;
    private EGLContext mEGLContext;
    private EGLSurface mEGLSurface;

    public GLView(Context context) {
        super(context);

        SurfaceHolder holder = getHolder();
        holder.addCallback(this);
    }

    public void setRenderer(Renderer renderer) {
        mRenderer = renderer;
    }

    protected EGLConfig createEGLConfig(EGL10 egl, EGLDisplay display) {

        int depthSize   = 16;
        int stencilSize =  0;
        int redSize     =  8;
        int greenSize   =  8;
        int blueSize    =  8;
        int alphaSize   =  8;

        int[] wantedConfigs = new int[] {
            EGL10.EGL_RENDERABLE_TYPE, GL_ES_VERSION,
            EGL10.EGL_DEPTH_SIZE     , depthSize,
            EGL10.EGL_STENCIL_SIZE   , stencilSize,
            EGL10.EGL_RED_SIZE       , redSize,
            EGL10.EGL_GREEN_SIZE     , greenSize,
            EGL10.EGL_BLUE_SIZE      , blueSize,
            EGL10.EGL_ALPHA_SIZE     , alphaSize,
            EGL10.EGL_NONE
        };

        int[] configsLength = new int[1];
        egl.eglChooseConfig(display, wantedConfigs, null, 0, configsLength);

        EGLConfig[] configs = new EGLConfig[configsLength[0]];
        egl.eglChooseConfig(display, wantedConfigs, configs, configsLength[0], configsLength);

        for (EGLConfig item : configs) {

            int d = findEGLConfigValue(egl, display, item, EGL10.EGL_DEPTH_SIZE  );
            int s = findEGLConfigValue(egl, display, item, EGL10.EGL_STENCIL_SIZE);
            int r = findEGLConfigValue(egl, display, item, EGL10.EGL_RED_SIZE    );
            int g = findEGLConfigValue(egl, display, item, EGL10.EGL_GREEN_SIZE  );
            int b = findEGLConfigValue(egl, display, item, EGL10.EGL_BLUE_SIZE   );
            int a = findEGLConfigValue(egl, display, item, EGL10.EGL_ALPHA_SIZE  );

            if (d >= depthSize
             && s >= stencilSize
             && r == redSize
             && g == greenSize
             && b == greenSize
             && a == alphaSize)
            {
                return item;
            }
        }
        return null;
    }

    protected int findEGLConfigValue(EGL10 egl, EGLDisplay display, EGLConfig item, int key) {
        int[] value = new int[1];
        if (egl.eglGetConfigAttrib(display, item, key, value)) {
            return value[0];
        }
        return 0;
    }

    protected EGLContext createEGLContext(EGL10 egl, EGLDisplay display, EGLConfig config) {
        int[] attributes = {
            0x3098 /* EGL_CONTEXT_CLIENT_VERSION */, EGL_VERSION,
            EGL10.EGL_NONE
        };
        return egl.eglCreateContext(display, config, EGL10.EGL_NO_CONTEXT, attributes);
    }

    protected EGLSurface createEGLSurface
        (EGL10 egl, EGLDisplay display, EGLConfig config, SurfaceHolder window, EGLContext context)
    {
        EGLSurface surface = egl.eglCreateWindowSurface(display, config, window, null);
        egl.eglMakeCurrent(display, surface, surface, context);
        return surface;
    }

    protected void destroyEGLSurface(EGL10 egl, EGLDisplay display, EGLSurface surface) {
        egl.eglMakeCurrent(display, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        egl.eglDestroySurface(display, surface);
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {

        mEGL = (EGL10) EGLContext.getEGL();
        mEGLDisplay = mEGL.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
        mEGL.eglInitialize(mEGLDisplay, new int[2]);

        mEGLConfig = createEGLConfig(mEGL, mEGLDisplay);
        mEGLContext = createEGLContext(mEGL, mEGLDisplay, mEGLConfig);
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {

        //when view resize, egl surface need to rebuild
        if (mEGLSurface != null) {
            destroyEGLSurface(mEGL, mEGLDisplay, mEGLSurface);
        }
        mEGLSurface = createEGLSurface(mEGL, mEGLDisplay, mEGLConfig, getHolder(), mEGLContext);

        if (!mAttached) {
            if (mRenderer != null) {
                mRenderer.onGLViewLoad(width, height);
            }
            mAttached = true;
        } else {
            if (mRenderer != null) {
                mRenderer.onGLViewResize(width, height);
            }
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
    }

    public void update() {
        if (mRenderer != null && mEGL != null) {
            mRenderer.onGLViewDraw();
            mEGL.eglSwapBuffers(mEGLDisplay, mEGLSurface);
        }
    }
}
