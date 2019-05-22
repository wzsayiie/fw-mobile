using System.IO;
using UnityEditor;
using UnityEngine;

class AndroidBuilder
{
    // configuration begin
    const string AppPackageID = "domain.corp.store.flavor.name";

    const string KeystoreFile = "MobileKeystore/Android/master.jks";
    const string KeystorePass = "master";
    const string KeyaliasName = "master";
    const string KeyaliasPass = "master";

    const string BuiltAPKName = "unity.apk";

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
        if (File.Exists(BuiltAPKName))
        {
            File.Delete(BuiltAPKName);
        }
        PlayerSettings.applicationIdentifier = AppPackageID;
        PlayerSettings.Android.keystoreName = KeystoreFile;
        PlayerSettings.Android.keystorePass = KeystorePass;
        PlayerSettings.Android.keyaliasName = KeyaliasName;
        PlayerSettings.Android.keyaliasPass = KeyaliasPass;
        BuildPipeline.BuildPlayer(Scenes, BuiltAPKName, BuildTarget.Android, BuildOptions.None);

        string toDir = "../BUILD";
        string toAPK = "../BUILD/" + BuiltAPKName;
        if (!Directory.Exists(toDir))
        {
            Directory.CreateDirectory(toDir);
        }
        if (File.Exists(toAPK))
        {
            File.Delete(toAPK);
        }
        File.Move(BuiltAPKName, toAPK);
    }
}
