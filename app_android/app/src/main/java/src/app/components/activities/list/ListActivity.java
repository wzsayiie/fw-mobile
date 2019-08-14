package src.app.components.activities.list;

import android.os.Bundle;
import android.widget.ListView;

import src.app.R;

public class ListActivity extends ListBaseActivity {

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
