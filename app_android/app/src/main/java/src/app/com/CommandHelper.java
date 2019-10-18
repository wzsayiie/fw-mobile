package src.app.com;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

import src.library.basis.StringUtil;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class CommandHelper {

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

    private ListView mListView;
    private ArrayList<DataItem> mDataSource;
    private BaseAdapter mListAdapter;
    private ListView.OnItemClickListener mClickListener;

    public void setListViewIfNeeded(ListView listView) {
        if (mListView != null) {
            //only can set once.
            return;
        }
        if (listView == null) {
            return;
        }

        mListView = listView;
        mListView.setAdapter(getListAdapter());
        mListView.setOnItemClickListener(getClickListener());
    }

    public void addAction(String actionText, Runnable action) {
        if (StringUtil.isEmpty(actionText)) {
            return;
        }
        if (mListView == null) {
            return;
        }

        DataItem item = new DataItem();
        item.setText(actionText);
        item.setAction(action);
        getDataSource().add(item);

        getListAdapter().notifyDataSetChanged();
    }

    protected ArrayList<DataItem> getDataSource() {
        if (mDataSource == null) {
            mDataSource = new ArrayList<>();
        }
        return mDataSource;
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
                    //NOTE: if mListView is null, should not enter this branch.
                    Context context = mListView.getContext();
                    LayoutInflater inflater = LayoutInflater.from(context);
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
