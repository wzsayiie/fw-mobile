package src.library.subsystem;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import src.library.R;

public class DefaultSubsystemActivity extends SubsystemActivity {

    private Button mCloseButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_default_subsystem);

        mCloseButton = findViewById(R.id.close_button);
        mCloseButton.setOnClickListener((View view) -> onCloseButtonClick());
    }

    protected void onCloseButtonClick() {
        finishSubsystem();
    }
}
