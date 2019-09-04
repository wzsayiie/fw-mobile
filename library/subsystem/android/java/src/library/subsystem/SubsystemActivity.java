package src.library.subsystem;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import src.library.R;
import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class SubsystemActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_subsystem);
        SubsystemManager.get().setSubsystemActivityInstance(this);

        Button closeButton = findViewById(R.id.close_button);
        closeButton.setOnClickListener((View view) -> onCloseButtonClick());
    }

    protected void onCloseButtonClick() {
        finishSubsystem();
    }

    protected void finishSubsystem() {
        SubsystemManager.get().stopSubsystem();
    }
}
