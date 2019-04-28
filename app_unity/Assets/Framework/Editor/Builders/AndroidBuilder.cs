using UnityEditor;
using UnityEngine;

class AndroidBuilder
{
    static void Build()
    {
        Debug.Log("to configurate !");
        return;

        /// configuration begin
        ///
        string applicationPkgId = ""; //e.g. domain.organization.appname.store.flavor

        string keystoreFilePath = ""; //keystore file path
        string keystorePassword = ""; //keystore file password
        string keyaliasName     = ""; //key name
        string keyaliasPassword = ""; //key password

        string buildAPKFilePath = ""; //output apk file path

        string[] scenes = { "Assets/Scenes/LaunchScene.unity" };
        ///
        /// configuration end

        Debug.Log("android build begin");

        PlayerSettings.applicationIdentifier = applicationPkgId;
        PlayerSettings.Android.keystoreName = keystoreFilePath;
        PlayerSettings.Android.keystorePass = keystorePassword;
        PlayerSettings.Android.keyaliasName = keyaliasName;
        PlayerSettings.Android.keyaliasPass = keyaliasPassword;

        BuildTarget buildTarget = BuildTarget.Android;
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, buildTarget);
        BuildPipeline.BuildPlayer(scenes, buildAPKFilePath, buildTarget, BuildOptions.None);
    }
}
