package src.app.components.activities.daily;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import src.app.R;
import src.app.com.CommandHelper;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class CommandFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater,
            @Nullable ViewGroup container,
            @Nullable Bundle savedInstanceState)
    {
        View view = inflater.inflate(R.layout.daily_command_fragment, container, false);
        initializeRootView(view);
        return view;
    }

    protected void initializeRootView(View view) {

        ListView listView = view.findViewById(R.id.list_view);
        CommandHelper helper = new CommandHelper();

        helper.setListViewIfNeeded(listView);
        helper.addAction("alpha", this::onActionAlpha);
        helper.addAction("beta", this::onActionBeta);
    }

    protected void onActionAlpha() {
    }

    protected void onActionBeta() {
    }
}
