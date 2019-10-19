package src.app.components.activities.daily;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import src.app.R;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class BlankFragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle state) {
        View contentView = inflater.inflate(R.layout.daily_blank_fragment, container, false);
        initializeRootView(contentView);
        return contentView;
    }

    protected void initializeRootView(View contentView) {
    }
}
