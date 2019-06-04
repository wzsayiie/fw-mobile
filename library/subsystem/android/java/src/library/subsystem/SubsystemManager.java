package src.library.subsystem;

import android.app.Activity;
import android.content.Intent;

import java.util.ArrayList;
import java.util.HashMap;

import src.library.foundation.ContextFinder;
import src.library.foundation.L;

public class SubsystemManager {

    private static SubsystemManager sInstance;

    public static SubsystemManager get() {
        if (sInstance == null) {
            sInstance = new SubsystemManager();
        }
        return sInstance;
    }

    private static class SubsystemInfoItem {
        boolean startedByProxy;
    }

    private SubsystemManagerProxy mProxy = null;
    private ArrayList<String> mLastStartedSubsystemNames = new ArrayList<>();
    private HashMap<String, SubsystemInfoItem> mRunningSubsystemInfoMap = new HashMap<>();

    public void setProxy(SubsystemManagerProxy proxy) {
        mProxy = proxy;
    }

    public String popLastStartedSubsystemName() {
        if (mLastStartedSubsystemNames.size() > 0) {
            return mLastStartedSubsystemNames.remove(0);
        } else {
            return null;
        }
    }

    private Intent createSubsystemIntent(Activity rootActivity, String subsystemName) {
        if (subsystemName.equals("default")) {
            return new Intent(rootActivity, DefaultSubsystemActivity.class);
        }
        return null;
    }

    public boolean startSubsystem(String subsystemName) {
        if (subsystemName == null || subsystemName.length() == 0) {
            L.e("try start subsystem but specified name is empty");
            return false;
        }
        if (mRunningSubsystemInfoMap.containsKey(subsystemName)) {
            L.e("try start subsystem '%s' but it's already running", subsystemName);
            return false;
        }

        //record name of starting subsystem, for the activity could get this name.
        mLastStartedSubsystemNames.add(subsystemName);

        SubsystemInfoItem subsystemInfoItem = null;
        if (mProxy == null) do {
            L.i("try start subsystem '%s' with default method", subsystemName);

            Activity rootActivity = ContextFinder.get().findCurrentActivity();
            if (rootActivity == null) {
                L.e("not found available activity context");
                break;
            }
            Intent subsystemIntent = createSubsystemIntent(rootActivity, subsystemName);
            if (subsystemIntent == null) {
                L.e("create subsystem activity intent failed");
                break;
            }

            try {
                rootActivity.startActivity(subsystemIntent);
                subsystemInfoItem = new SubsystemInfoItem();
                subsystemInfoItem.startedByProxy = false;
            } catch (Exception e) {
                L.e("start subsystem activity exception: %s", e.toString());
            }

        } while (false); else {
            L.i("try start subsystem '%s' with proxy", subsystemName);

            boolean succeeded = mProxy.onSubsystemManagerStartSubsystem(subsystemName);
            if (succeeded) {
                subsystemInfoItem = new SubsystemInfoItem();
                subsystemInfoItem.startedByProxy = true;
            }
        }

        if (subsystemInfoItem != null) {
            L.i("start subsystem '%s' succeeded", subsystemName);
            mRunningSubsystemInfoMap.put(subsystemName, subsystemInfoItem);
            return true;
        } else {
            L.e("start subsystem '%s' failed", subsystemName);
            return false;
        }
    }

    public void stopSubsystem(String subsystemName) {
        stopSubsystem(null, subsystemName);
    }

    public void stopSubsystem(Activity activity, String subsystemName) {
        if (subsystemName == null || subsystemName.length() == 0) {
            L.e("try stop subsystem but specified name is empty");
            return;
        }

        SubsystemInfoItem infoItem = mRunningSubsystemInfoMap.get(subsystemName);
        if (infoItem == null) {
            L.e("try stop subsystem '%s' but it was not running", subsystemName);
            return;
        }

        if (infoItem.startedByProxy) {
            L.i("try stop subsystem '%s' with proxy", subsystemName);
            if (mProxy == null) {
                L.e("can't stop subsystem '%s' because the proxy is released", subsystemName);
            } else {
                mProxy.onSubsystemManagerStopSubsystem(subsystemName);
            }
        } else {
            L.i("try stop subsystem '%s' with default method", subsystemName);
            if (activity == null) {
                L.e("can't stop subsystem '%s' because the activity is null", subsystemName);
            } else {
                activity.finish();
            }
        }
        mRunningSubsystemInfoMap.remove(subsystemName);
    }
}
