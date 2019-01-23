package src.app.components.example;

import android.os.Bundle;
import android.widget.ListView;

import src.app.R;
import src.app.utility.components.DemoActivity;
import src.app.utility.data.ActivityDispatcher;

public class ExampleActivity extends DemoActivity {

    private ListView mListView;

    @Override
    protected ListView getListView() {
        return mListView;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_case);
        mListView = findViewById(R.id.list_view);

        addAction("Alpha", this::onActionAlpha);
        addAction("Beta" , this::onActionBeta );
    }

    protected void onActionAlpha() {
    }

    protected void onActionBeta() {
    }

    @Override
    public void onBackPressed() {
        ActivityDispatcher.get().moveTaskToBackground();
    }
}
