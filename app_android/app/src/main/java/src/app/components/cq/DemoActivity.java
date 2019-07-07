package src.app.components.cq;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

import src.library.basis.CQString;
import src.library.foundation.L;

public abstract class DemoActivity extends Activity {

    protected static class DataItem {

        private String mText;
        private Runnable mAction;

        String getText() {
            return mText;
        }

        void setText(String text) {
            mText = text;
        }

        Runnable getAction() {
            return mAction;
        }

        void setAction(Runnable action) {
            mAction = action;
        }
    }

    private ArrayList<DataItem> mDataSource;
    private BaseAdapter mListAdapter;
    private ListView.OnItemClickListener mClickListener;

    @Override
    protected void onResume() {
        super.onResume();
        loadListViewIfNeeded();
    }

    protected ListView getListView() {
        L.e("the getListView should be overridden");
        return null;
    }

    protected void loadListViewIfNeeded() {
        ListView listView = getListView();

        if (listView == null) {
            return;
        }
        if (listView.getAdapter() != null) {
            return;
        }

        listView.setAdapter(getListAdapter());
        listView.setOnItemClickListener(getClickListener());
    }

    protected ArrayList<DataItem> getDataSource() {
        if (mDataSource == null) {
            mDataSource = new ArrayList<>();
        }
        return mDataSource;
    }

    protected void addAction(String actionText, Runnable action) {
        if (CQString.isEmpty(actionText)) {
            return;
        }

        DataItem item = new DataItem();
        item.setText(actionText);
        item.setAction(action);
        getDataSource().add(item);

        loadListViewIfNeeded();
        getListAdapter().notifyDataSetChanged();
    }

    protected BaseAdapter getListAdapter() {
        if (mListAdapter != null) {
            return mListAdapter;
        }

        mListAdapter = new BaseAdapter() {
            @Override
            public int getCount() {
                return getDataSource().size();
            }

            @Override
            public Object getItem(int position) {
                return getDataSource().get(position);
            }

            @Override
            public long getItemId(int position) {
                return position;
            }

            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                String text = getDataSource().get(position).getText();

                if (convertView == null) {
                    LayoutInflater inflater = LayoutInflater.from(DemoActivity.this);
                    convertView = inflater.inflate(android.R.layout.simple_list_item_1, null);
                }
                TextView textView = convertView.findViewById(android.R.id.text1);
                textView.setText(text);

                return convertView;
            }
        };
        return mListAdapter;
    }

    protected ListView.OnItemClickListener getClickListener() {
        if (mClickListener != null) {
            return mClickListener;
        }

        mClickListener = (AdapterView<?> parent, View view, int position, long id) -> {
            Runnable action = getDataSource().get(position).getAction();
            if (action != null) {
                action.run();
            }
        };
        return mClickListener;
    }
}
