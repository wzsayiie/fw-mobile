package src.app.components.activities.doc;

import android.content.res.Configuration;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentTransaction;

import java.util.Timer;

import src.app.R;
import src.app.mod.TimerAssist;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class DocActivity extends FragmentActivity {

    private int              mLoadedOrientation;
    private ContentFragment  mContentFragment;
    private TitleBarFragment mTitleBarFragment;
    private ToolBarFragment  mToolBarFragment;
    private AttachFragment   mAttachFragment;

    private boolean mBarsHidden;
    private Timer mHideBarsTimer;

    //life cycle:

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        int orientation = getResources().getConfiguration().orientation;
        reloadContentViewIfNeeded(orientation);

        resetHideBarsTimer(true);
    }

    @Override
    public void onConfigurationChanged(@NonNull Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        int orientation = newConfig.orientation;
        reloadContentViewIfNeeded(orientation);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        resetHideBarsTimer(false);
    }

    //events:

    protected void onContentFrameTouch(View view, MotionEvent event) {
        if (event.getAction() != MotionEvent.ACTION_UP) {
            return;
        }

        if (mBarsHidden) {
            //to show bars and start the timer.
            resetBarsHidden(false);
            resetHideBarsTimer(true);
        } else {
            //to hide bars.
            resetBarsHidden(true);
            resetHideBarsTimer(false);
        }
    }

    protected void onBarsHideTimerTimeout() {
        resetBarsHidden(true);
        resetHideBarsTimer(false);
    }

    //functions:

    protected void resetBarsHidden(boolean hidden) {
        if (mBarsHidden == hidden) {
            return;
        }
        mBarsHidden = hidden;

        if (hidden) {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.setCustomAnimations(android.R.anim.fade_in, android.R.anim.fade_out);
            transaction.hide(mTitleBarFragment);
            transaction.hide(mToolBarFragment);
            transaction.commitNow();
        } else {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.setCustomAnimations(android.R.anim.fade_in, android.R.anim.fade_out);
            transaction.show(mTitleBarFragment);
            transaction.show(mToolBarFragment);
            transaction.commitNow();
        }
    }

    protected void resetHideBarsTimer(boolean enabled) {
        if (mHideBarsTimer != null) {
            mHideBarsTimer.cancel();
            mHideBarsTimer = null;
        }

        if (enabled) {
            mHideBarsTimer = TimerAssist.schedule(true, 5000, (Timer timer) ->
                onBarsHideTimerTimeout()
            );
        }
    }

    protected void reloadContentViewIfNeeded(int orientation) {
        if (mLoadedOrientation == orientation) {
            return;
        }
        mLoadedOrientation = orientation;

        //load ui:
        if (orientation == Configuration.ORIENTATION_PORTRAIT) {

            removeFragmentNow(mContentFragment );
            removeFragmentNow(mTitleBarFragment);
            removeFragmentNow(mToolBarFragment );
            removeFragmentNow(mAttachFragment  );

            if (mContentFragment  == null) { mContentFragment  = new ContentFragment (); }
            if (mTitleBarFragment == null) { mTitleBarFragment = new TitleBarFragment(); }
            if (mToolBarFragment  == null) { mToolBarFragment  = new ToolBarFragment (); }
            if (mAttachFragment   == null) { mAttachFragment   = new AttachFragment  (); }

            setContentView(R.layout.doc_activity_port);

            addFragmentNow(R.id.content_frame  , mContentFragment , false);
            addFragmentNow(R.id.title_bar_frame, mTitleBarFragment, mBarsHidden);
            addFragmentNow(R.id.tool_bar_frame , mToolBarFragment , mBarsHidden);
            addFragmentNow(R.id.attach_frame   , mAttachFragment  , false);

        } else if (orientation == Configuration.ORIENTATION_LANDSCAPE) {

            removeFragmentNow(mContentFragment );
            removeFragmentNow(mTitleBarFragment);
            removeFragmentNow(mToolBarFragment );

            if (mContentFragment  == null) { mContentFragment  = new ContentFragment (); }
            if (mTitleBarFragment == null) { mTitleBarFragment = new TitleBarFragment(); }
            if (mToolBarFragment  == null) { mToolBarFragment  = new ToolBarFragment (); }

            setContentView(R.layout.doc_activity_land);

            addFragmentNow(R.id.content_frame  , mContentFragment , false);
            addFragmentNow(R.id.title_bar_frame, mTitleBarFragment, mBarsHidden);
            addFragmentNow(R.id.tool_bar_frame , mToolBarFragment , mBarsHidden);
        }

        //ui events:
        View contentFrame = findViewById(R.id.content_frame);
        contentFrame.setOnTouchListener((View view, MotionEvent event) -> {
            onContentFrameTouch(view, event);
            view.performClick();
            return true;
        });
    }

    protected void addFragmentNow(int containerViewId, Fragment fragment, boolean hidden) {
        if (fragment != null) {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.add(containerViewId, fragment);
            if (hidden) {
                transaction.hide(fragment);
            }
            transaction.commitNow();
        }
    }

    protected void removeFragmentNow(Fragment fragment) {
        if (fragment != null) {
            FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
            transaction.remove(fragment);
            transaction.commitNow();
        }
    }
}
