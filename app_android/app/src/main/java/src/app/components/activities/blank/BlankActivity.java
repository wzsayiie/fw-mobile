package src.app.components.activities.blank;

import android.app.Activity;
import android.os.Bundle;

import src.app.R;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class BlankActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blank);
    }
}
