using System;
using System.IO;
using UnityEditor;

public static class AndroidBuild
{
    //configuration begin
    static readonly string AppPackageID = "domain.corp.store.flavor.name";

    static readonly string KeystoreFile = Path.Combine("MobileKeystore", "Android", "master.jks");
    static readonly string KeystorePass = "master";
    static readonly string KeyaliasName = "master";
    static readonly string KeyaliasPass = "master";

    static readonly string ExportAKPDir = Path.Combine("..", "BUILD");
    static readonly string BuiltAPKName = "unity.apk";

    static readonly string[] Scenes = {
        Path.Combine("Assets", "Scene", "LaunchScene.unity"),
        Path.Combine("Assets", "Scene", "WorldScene.unity")
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
        string toAPK = Path.Combine(ExportAKPDir, BuiltAPKName);
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
                File.Move(it, Path.Combine(ExportAKPDir, Path.GetFileName(it)));
            }
        }
    }
}
