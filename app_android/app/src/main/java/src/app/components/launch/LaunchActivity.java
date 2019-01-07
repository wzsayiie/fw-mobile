package src.app.components.launch;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import src.app.R;
import src.app.utility.application.EventCenter;
import src.app.utility.application.L;
import src.app.utility.data.ActivityDispatcher;

public class LaunchActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_launch);

        L.i("'%s' onCreate", L.string(this));

        EventCenter.runOnMainThread(1000, () ->
            ActivityDispatcher.get().startActivity("apps.example", null)
        );
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }
}
