using System.IO;
using UnityEditor;
using UnityEngine;

class AndroidBuilder
{
    // configuration begin
    const string AppPackageID = "domain.organization.appname.store.flavor";

    const string KeystoreFile = "MobileKeystore/Android/master.jks";
    const string KeystorePass = "master";
    const string KeyaliasName = "master";
    const string KeyaliasPass = "master";

    const string BuildAPKName = "unity.apk";

    static string[] Scenes
    {
        get
        {
            return new string[] { "Assets/Scenes/LaunchScene.unity" };
        }
    }
    // configuration end

    static void Build()
    {
        Debug.Log("android build");

        if (File.Exists(BuildAPKName))
        {
            File.Delete(BuildAPKName);
        }

        PlayerSettings.applicationIdentifier = AppPackageID;
        PlayerSettings.Android.keystoreName = KeystoreFile;
        PlayerSettings.Android.keystorePass = KeystorePass;
        PlayerSettings.Android.keyaliasName = KeyaliasName;
        PlayerSettings.Android.keyaliasPass = KeyaliasPass;

        BuildTarget buildTarget = BuildTarget.Android;
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, buildTarget);
        BuildPipeline.BuildPlayer(Scenes, BuildAPKName, buildTarget, BuildOptions.None);
    }
}
