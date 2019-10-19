package src.app.components.activities.daily;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import androidx.drawerlayout.widget.DrawerLayout;
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

    private ArrayList<Fragment> mMasterFragments;
    private ArrayList<Button> mTabButtons;
    private int mSelectedIndex;

    //life cycle:

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.daily_activity);

        addMasterFragment(mSelectedIndex, "command", new CommandFragment());
        addMasterFragment(mSelectedIndex, "blank", new BlankFragment());

        setDrawerFragment();
    }

    //event:

    protected void onTopButtonClick(View view) {
        DrawerLayout contentDrawer = findViewById(R.id.content_drawer);
        FrameLayout drawerFrame = findViewById(R.id.drawer_frame);

        contentDrawer.openDrawer(drawerFrame);
    }

    protected void onTabBarButtonClick(View view) {
        Integer index = (Integer) view.getTag();
        selectPage(index);
    }

    //functions:

    protected void setDrawerFragment() {
        //left drawer view:
        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
        transaction.add(R.id.drawer_frame, new DrawerFragment());
        transaction.commit();

        //top button:
        Button topButton = findViewById(R.id.top_button);
        topButton.setOnClickListener(this::onTopButtonClick);
    }

    protected void addMasterFragment(int currentIndex, String name, Fragment fragment) {

        int thisIndex = (mMasterFragments != null ? mMasterFragments.size() : 0);

        //add fragment:
        if (mMasterFragments == null) {
            mMasterFragments = new ArrayList<>();
        }
        mMasterFragments.add(fragment);

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
        transaction.add(R.id.master_frame, fragment);
        if (thisIndex != currentIndex) {
            transaction.hide(fragment);
        }
        transaction.commit();

        //add button:
        Button button = new Button(this);

        if (mTabButtons == null) {
            mTabButtons = new ArrayList<>();
        }
        mTabButtons.add(button);

        button.setTag(thisIndex);
        button.setOnClickListener(this::onTabBarButtonClick);
        button.setText(name);
        if (thisIndex == currentIndex) {
            button.setTextColor(SELECTED_COLOR);
        } else {
            button.setTextColor(NORMAL_COLOR);
        }

        button.setLayoutParams(new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        LinearLayout tabLinear = findViewById(R.id.tab_linear);
        tabLinear.addView(button);
    }

    protected void selectPage(int index) {
        if (mMasterFragments == null) {
            return;
        }
        if (index < 0 || index >= mMasterFragments.size()) {
            return;
        }
        if (index == mSelectedIndex) {
            return;
        }

        //switch fragment:
        Fragment oldFragment = mMasterFragments.get(mSelectedIndex);
        Fragment newFragment = mMasterFragments.get(index);

        FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
        transaction.hide(oldFragment);
        transaction.show(newFragment);
        transaction.commit();

        //switch button:
        Button oldButton = mTabButtons.get(mSelectedIndex);
        Button newButton = mTabButtons.get(index);

        oldButton.setTextColor(NORMAL_COLOR);
        newButton.setTextColor(SELECTED_COLOR);

        mSelectedIndex = index;
    }
}
