package src.app.com;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;

import src.app.mod.AndroidVersion;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class PermissionRequestActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String[] permissions = { getIntent().getStringExtra("permission") };
        if (Build.VERSION.SDK_INT >= AndroidVersion.M_6_API_23) {
            requestPermissions(permissions, 0);
        } else {
            L.e("should not enter this branch");
        }
    }

    @Override
    public void onRequestPermissionsResult(
        int requestCode, @NonNull String[] list, @NonNull int[] results)
    {
        super.onRequestPermissionsResult(requestCode, list, results);

        String permission = list[0];
        boolean granted = (results[0] == PackageManager.PERMISSION_GRANTED);
        PermissionHelper.get().onResponse(permission, granted);

        finish();
    }
}
