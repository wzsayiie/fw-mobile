package src.app.components.activities.floating;

import android.app.Activity;
import android.os.Bundle;

import java.util.Timer;

import src.app.R;
import src.app.mod.ActivityHelper;
import src.app.mod.TimerAssist;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class FloatingActivity extends Activity {

    private Timer mStopTimer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.floating_activity);

        //NOTE: use startActivityWithFade() to start this activity.

        mStopTimer = TimerAssist.schedule(false, 2000, (Timer timer) ->
            ActivityHelper.get().finishActivityWithFade(this, null)
        );
    }

    @Override
    protected void onStop() {
        super.onStop();

        mStopTimer.cancel();
    }
}
