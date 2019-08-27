using System;
using System.IO;
using UnityEditor;

public static class AndroidBuilder
{
    //configuration begin
    private const string AppPackageID = "domain.corp.store.flavor.name";

    private const string KeystoreFile = "MobileKeystore/Android/master.jks";
    private const string KeystorePass = "master";
    private const string KeyaliasName = "master";
    private const string KeyaliasPass = "master";

    private const string ExportAKPDir = "../BUILD";
    private const string BuiltAPKName = "unity.apk";

    private static readonly string[] Scenes = {
        "Assets/Scene/LaunchScene.unity",
        "Assets/Scene/WorldScene.unity"
    };
    //configuration end

    public static void Build()
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

        if (!Directory.Exists(ExportAKPDir))
        {
            Directory.CreateDirectory(ExportAKPDir);
        }

        //move apk.
        string toAPK = ExportAKPDir + "/" + BuiltAPKName;
        if (File.Exists(toAPK))
        {
            File.Delete(toAPK);
        }
        File.Move(BuiltAPKName, toAPK);

        //move symbols.zip of il2cpp.
        string symbolsSuffix = ".symbols.zip";
        foreach (string it in Directory.GetFiles(ExportAKPDir))
        {
            if (it.EndsWith(symbolsSuffix, StringComparison.OrdinalIgnoreCase))
            {
                File.Delete(it);
            }
        }
        foreach (string it in Directory.GetFiles("."))
        {
            if (it.EndsWith(symbolsSuffix, StringComparison.OrdinalIgnoreCase))
            {
                File.Move(it, ExportAKPDir + "/" + Path.GetFileName(it));
            }
        }
    }
}
