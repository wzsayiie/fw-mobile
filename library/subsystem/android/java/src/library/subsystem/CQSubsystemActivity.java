package src.library.subsystem;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import src.library.R;

public class CQSubsystemActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_subsystem);
        CQSubsystemManager.get().setSubsystemActivityInstance(this);

        Button closeButton = findViewById(R.id.close_button);
        closeButton.setOnClickListener((View view) -> onCloseButtonClick());
    }

    protected void onCloseButtonClick() {
        finishSubsystem();
    }

    protected void finishSubsystem() {
        CQSubsystemManager.get().stopSubsystem();
    }
}
