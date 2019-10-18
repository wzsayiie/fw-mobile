package src.app.components.activities.daily;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentTransaction;

import java.util.ArrayList;

import src.app.R;
import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class DailyActivity extends FragmentActivity {

    private static final int SELECTED_COLOR = Color.rgb(0, 102, 204);
    private static final int NORMAL_COLOR = Color.rgb(0, 0, 0);

    private ArrayList<Fragment> mFragments;
    private ArrayList<Button> mBarButtons;
    private int mSelectedIndex;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.daily_activity);

        addPage(mSelectedIndex, "command", new CommandFragment());
        addPage(mSelectedIndex, "blank", new BlankFragment());
    }

    protected void onBarButtonClick(int index) {
        selectPage(index);
    }

    protected void addPage(int currentIndex, String name, Fragment fragment) {

        int thisIndex = (mFragments != null ? mFragments.size() : 0);

        //add fragment:
        if (mFragments == null) {
            mFragments = new ArrayList<>();
        }
        mFragments.add(fragment);

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
        transaction.add(R.id.fragment_container, fragment);
        if (thisIndex != currentIndex) {
            transaction.hide(fragment);
        }
        transaction.commit();

        //add button:
        Button button = new Button(this);

        if (mBarButtons == null) {
            mBarButtons = new ArrayList<>();
        }
        mBarButtons.add(button);

        button.setText(name);
        if (thisIndex == currentIndex) {
            button.setTextColor(SELECTED_COLOR);
        } else {
            button.setTextColor(NORMAL_COLOR);
        }

        button.setOnClickListener((View view) ->
            onBarButtonClick(thisIndex)
        );

        button.setLayoutParams(new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        LinearLayout layout = findViewById(R.id.button_container);
        layout.addView(button);
    }

    protected void selectPage(int index) {
        if (mFragments == null) {
            return;
        }
        if (index < 0 || index >= mFragments.size()) {
            return;
        }
        if (index == mSelectedIndex) {
            return;
        }

        //switch fragment:
        Fragment oldFragment = mFragments.get(mSelectedIndex);
        Fragment newFragment = mFragments.get(index);

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
        transaction.hide(oldFragment);
        transaction.show(newFragment);
        transaction.commit();

        //switch button:
        Button oldButton = mBarButtons.get(mSelectedIndex);
        Button newButton = mBarButtons.get(index);

        oldButton.setTextColor(NORMAL_COLOR);
        newButton.setTextColor(SELECTED_COLOR);

        mSelectedIndex = index;
    }
}
