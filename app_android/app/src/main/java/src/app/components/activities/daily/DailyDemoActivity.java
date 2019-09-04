package src.app.components.activities.daily;

import android.os.Bundle;
import android.widget.ListView;

import src.app.R;
import src.app.com.DemoActivity;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class DailyDemoActivity extends DemoActivity {

    private ListView mListView;

    @Override
    protected ListView getListView() {
        return mListView;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);
        mListView = findViewById(R.id.list_view);

        addAction("Alpha", this::onActionAlpha);
        addAction("Beta" , this::onActionBeta );
    }

    protected void onActionAlpha() {
    }

    protected void onActionBeta() {
    }
}
