package src.app.com;

import android.app.Application;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;

import src.app.boot.AppWrapper;
import src.app.mod.AndroidVersion;
import src.app.mod.TaskHelper;
import src.library.basis.StringUtil;
import src.library.foundation.L;

public class PermissionHelper {

    private static class Singleton {
        static PermissionHelper instance = new PermissionHelper();
    }
    public static PermissionHelper get() {
        return Singleton.instance;
    }

    //if a permission declared in AndroidManifest.
    private boolean isDeclared(String permission) {
        try {
            Application app = AppWrapper.getApp();
            PackageManager manager = app.getPackageManager();
            String packageName = app.getPackageName();

            PackageInfo info = manager.getPackageInfo(packageName, PackageManager.GET_PERMISSIONS);
            for (String it : info.requestedPermissions) {
                if (it.equals(permission)) {
                    return true;
                }
            }
            return false;

        } catch (PackageManager.NameNotFoundException e) {
            L.e("%s", e.toString());
            return false;
        }
    }

    //does the app have a permission.
    public boolean isGranted(String permission) {
        if (StringUtil.isEmpty(permission)) {
            L.e("try check a empty permission");
            return false;
        }

        boolean declared = isDeclared(permission);

        if (Build.VERSION.SDK_INT <= AndroidVersion.LOLLIPOP_5_1_API_22) {
            //on Android 5.1 or earlier, user who install the app
            //must agree to all the permissions declared in AndroidManifest.xml,
            //otherwise the installation will fail.
            L.i("'%s' declared in AndroidManifest and app granted it automatically", permission);
            return declared;
        }

        if (declared) {
            int status = AppWrapper.getApp().checkSelfPermission(permission);
            if (status == PackageManager.PERMISSION_GRANTED) {
                L.i("'%s' is granted", permission);
                return true;
            } else {
                L.i("'%s' is denied", permission);
                return false;
            }
        } else {
            L.i("'%s' did not be declared in AndroidManifest", permission);
            return false;
        }
    }

    public interface Response {
        void onResponse(String permission, boolean granted);
    }

    private Response mWaitingResponse;

    public void request(String permission, Response response) {
        if (StringUtil.isEmpty(permission)) {
            L.e("try request a empty permission");
            return;
        }
        if (response == null) {
            L.e("request permission callback is null");
            return;
        }

        if (!isDeclared(permission)) {

            //NOTE: callback on asynchronous,
            //consistent with the case that start PermissionRequestActivity.

            L.i("'%s' was not declare in AndroidManifest", permission);
            TaskHelper.get().runOnCurrentTread(0, () ->
                response.onResponse(permission, false)
            );

        } else if (isGranted(permission)) {

            L.i("'%s' was already granted", permission);
            TaskHelper.get().runOnCurrentTread(0, () ->
                response.onResponse(permission, true)
            );

        } else if (Build.VERSION.SDK_INT >= AndroidVersion.M_6_API_23) {

            //only can request permission dynamically since Android 6.

            L.i("request '%s'", permission);

            mWaitingResponse = response;

            Application app = AppWrapper.getApp();
            Intent intent = new Intent(app, PermissionRequestActivity.class);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            intent.putExtra("permission", permission);
            app.startActivity(intent);

        } else {

            L.i("'%s' is denied and can't be requested", permission);
            TaskHelper.get().runOnCurrentTread(0, () ->
                response.onResponse(permission, false)
            );
        }
    }

    //do not call this method. it's prepared for PermissionRequestActivity.
    void onResponse(String permission, boolean granted) {
        if (mWaitingResponse == null) {
            L.e("the response callback should not be null");
            return;
        }

        L.i("request '%s' response, %s", permission, (granted ? "granted" : "denied"));
        mWaitingResponse.onResponse(permission, granted);
        mWaitingResponse = null;
    }
}
