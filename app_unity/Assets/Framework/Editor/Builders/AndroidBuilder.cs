using UnityEditor;
using UnityEngine;

class AndroidBuilder
{
    // configuration begin
    const string AppPackageID = ""; //e.g. domain.organization.appname.store.flavor

    const string KeystoreFile = ""; //file path
    const string KeystorePass = ""; //file password
    const string KeyaliasName = ""; //key name
    const string KeyaliasPass = ""; //key password

    const string BuildAPKFile = ""; //xx.apk

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

        PlayerSettings.applicationIdentifier = AppPackageID;
        PlayerSettings.Android.keystoreName = KeystoreFile;
        PlayerSettings.Android.keystorePass = KeystorePass;
        PlayerSettings.Android.keyaliasName = KeyaliasName;
        PlayerSettings.Android.keyaliasPass = KeyaliasPass;

        BuildTarget buildTarget = BuildTarget.Android;
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, buildTarget);
        BuildPipeline.BuildPlayer(Scenes, BuildAPKFile, buildTarget, BuildOptions.None);
    }
}
