package src.app.components.launch;

import android.app.Activity;
import android.os.Bundle;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.widget.TextView;

import src.app.R;
import src.app.data.CQActivityDispatcher;
import src.app.data.CQBus;

public class LaunchActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_launch);

        TextView textView = findViewById(R.id.text_view);
        Animation animation = new AlphaAnimation(0.f, 1.f);
        animation.setDuration(1000);
        textView.startAnimation(animation);

        CQBus.runOnMainThread(1000, () ->
            CQActivityDispatcher.get().startActivityWithFade("apps.example", null)
        );
    }
}
