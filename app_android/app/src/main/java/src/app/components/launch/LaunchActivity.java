package src.app.components.launch;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;

import src.app.R;
import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;
import src.app.utility.data.ActivityDispatcher;
import src.app.utility.data.Bus;

public class LaunchActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_launch);

        Bus.runOnMainThread(1000, () ->
            ActivityDispatcher.get().startActivity("apps.example", null)
        );
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }
}
