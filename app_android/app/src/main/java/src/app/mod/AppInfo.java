package src.app.mod;

import android.annotation.SuppressLint;
import android.app.ActivityManager;
import android.app.Application;
import android.content.ContentResolver;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Build;
import android.os.Process;
import android.provider.Settings;
import android.text.TextUtils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import src.app.boot.AppWrapper;
import src.library.basis.StringUtil;
import src.library.foundation.L;

public class AppInfo {

    public static String getProcessName() {
        Application app = AppWrapper.getApp();
        ActivityManager manager = (ActivityManager) app.getSystemService(Context.ACTIVITY_SERVICE);
        if (manager == null) {
            L.e("activity service did not found");
            return "";
        }

        int pid = Process.myPid();
        for (ActivityManager.RunningAppProcessInfo info : manager.getRunningAppProcesses()) {
            if (info.pid == pid) {
                return info.processName;
            }
        }
        L.e("current pid didn't match any process name");
        return "";
    }

    public static String getPackageName() {
        return AppWrapper.getApp().getPackageName();
    }

    public static String getAppVersion() {
        try {

            PackageManager manager = AppWrapper.getApp().getPackageManager();
            String packageName = getPackageName();
            PackageInfo info = manager.getPackageInfo(packageName, 0);

            String versionName = info.versionName;

            long versionCode;
            if (Build.VERSION.SDK_INT >= AndroidVersion.P_9_API_28) {
                versionCode = info.getLongVersionCode();
            } else {
                versionCode = info.versionCode;
            }

            return versionName + "-" + versionCode;

        } catch (PackageManager.NameNotFoundException e) {
            L.e("exception on get app version: %s", e.toString());
            return "";
        }
    }

    public static String getAndroidID() {
        ContentResolver resolver = AppWrapper.getApp().getContentResolver();
        return Settings.System.getString(resolver, Settings.Secure.ANDROID_ID);
    }

    public static String getSupportedABIs() {
        if (Build.VERSION.SDK_INT >= AndroidVersion.LOLLIPOP_5_API_21) {
            String[] values = Build.SUPPORTED_ABIS;
            return TextUtils.join("|", values);
        } else {
            String abi1 = Build.CPU_ABI;
            String abi2 = Build.CPU_ABI2;
            return abi2 != null ? abi1 + "|" + abi2 : abi1;
        }
    }

    public static Signature getApkSignature() {
        PackageManager packageManager = AppWrapper.getApp().getPackageManager();
        String packageName = getPackageName();

        Signature[] signatures;
        try {
            if (Build.VERSION.SDK_INT >= AndroidVersion.P_9_API_28) {
                int flag = PackageManager.GET_SIGNING_CERTIFICATES;
                PackageInfo info = packageManager.getPackageInfo(packageName, flag);
                signatures = info.signingInfo.getApkContentsSigners();
            } else {
                int flag = PackageManager.GET_SIGNATURES;
                @SuppressLint("PackageManagerGetSignatures")
                PackageInfo info = packageManager.getPackageInfo(packageName, flag);
                signatures = info.signatures;
            }
        } catch (PackageManager.NameNotFoundException e) {
            L.e("exception on get apk signature: %s", e.toString());
            return null;
        }
        if (signatures == null || signatures.length == 0) {
            L.e("the apk signature is empty");
            return null;
        }

        return signatures[0];
    }

    public static String getApkSignatureDigest(String algorithm) {
        if (StringUtil.isEmpty(algorithm)) {
            L.e("didn't specify algorithm for apk signature digest");
            return "";
        }

        byte[] data = null; {
            Signature signature = getApkSignature();
            if (signature != null) {
                data = signature.toByteArray();
            }
        }
        if (data == null) {
            L.e("apk signature data is empty");
            return "";
        }

        MessageDigest digestGenerator;
        try {
            digestGenerator = MessageDigest.getInstance(algorithm);
            digestGenerator.update(data);
        } catch (NoSuchAlgorithmException e) {
            L.e("exception on calculate signature digest: %s", e.toString());
            return "";
        }

        byte[] digest = digestGenerator.digest();
        return StringUtil.hexStringFromBytes(digest);
    }
}
