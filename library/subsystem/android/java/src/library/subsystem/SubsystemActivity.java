package src.library.subsystem;

import android.app.Activity;
import android.os.Bundle;

public abstract class SubsystemActivity extends Activity {

    private String mSubsystemName;

    protected String getSubsystemName() {
        return mSubsystemName;
    }

    protected void finishSubsystem() {
        SubsystemManager.get().stopSubsystem(this, mSubsystemName);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mSubsystemName = SubsystemManager.get().popLastStartedSubsystemName();
    }
}
