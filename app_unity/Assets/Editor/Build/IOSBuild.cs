using System.Diagnostics;
using System.IO;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEditor.iOS.Xcode;

public static class IOSBuild
{
    //configuration begin
    static readonly string AppPackageID = ""; // bundle id
    static readonly string TeamIdentity = ""; // team id
    static readonly string SignIdentity = ""; // command "security find-identity" to find
    static readonly string Provisioning = ""; // name of provision profile exported in xcode
    static readonly string ExportMethod = ""; // "ad-hoc", "app-store", "development" or "enterprise"
    static readonly string AllowBitcode = ""; // "true" or "false"

    static readonly string ProductDPath = Path.Combine("..", "BUILD");
    static readonly string ProductsName = "unity";

    static readonly string[] Scenes = {
        Path.Combine("Assets", "Scene", "LaunchScene.unity"),
        Path.Combine("Assets", "Scene", "WorldScene.unity")
    };
    //configuration end

    public static void Build()
    {
        if (AppPackageID.Length == 0)
        {
            return;
        }

        //1st step
        GenerateXcodeProject();
    }

    [PostProcessBuild]
    private static void ExportIPA(BuildTarget buildTarget, string projectDirectory)
    {
        if (buildTarget != BuildTarget.iOS) return;

        //2nd step
        EditProjectSettings(projectDirectory);

        //3rd step
        WriteExportOptions(projectDirectory);

        //4st step
        ExportIPA(projectDirectory);

        //5st step
        MoveProducts(projectDirectory);
    }

    private static void GenerateXcodeProject()
    {
        string directory = "XCODEBUILD";
        if (Directory.Exists(directory))
        {
            Directory.Delete(directory, true);
        }

        PlayerSettings.applicationIdentifier = AppPackageID;
        BuildPipeline.BuildPlayer(Scenes, directory, BuildTarget.iOS, BuildOptions.None);
    }

    private static void EditProjectSettings(string directory)
    {
        var file = Path.Combine(directory, "Unity-iPhone.xcodeproj", "project.pbxproj");
        var settings = new PBXProject();
        settings.ReadFromFile(file);

        string target = settings.TargetGuidByName(PBXProject.GetUnityTargetName());

        settings.SetBuildProperty(target, "CODE_SIGN_STYLE"               , "Manual"    );
        settings.SetBuildProperty(target, "DEVELOPMENT_TEAM"              , TeamIdentity);
        settings.SetBuildProperty(target, "CODE_SIGN_IDENTITY"            , SignIdentity);
        settings.SetBuildProperty(target, "PROVISIONING_PROFILE_SPECIFIER", Provisioning);

        settings.WriteToFile(file);
    }

    private static void WriteExportOptions(string directory)
    {
        string options = "";
        options +=/**/"<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
        options += "\n <!DOCTYPE plist PUBLIC";
        options += "\n     \"-//Apple//DTD PLIST 1.0//EN\"";
        options += "\n     \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">";
        options += "\n <plist version=\"1.0\">";
        options += "\n <dict>";
        options += "\n     <key>teamID</key> <string>$(teamID)</string>";
        options += "\n     <key>method</key> <string>$(method)</string>";
        options += "\n     <key>provisioningProfiles</key>";
        options += "\n     <dict>";
        options += "\n         <key>$(bundleID)</key> <string>$(provision)</string>";
        options += "\n     </dict>";
        options += "\n     <key>compileBitcode</key> <$(bitcode) />";
        options += "\n     <key>uploadSymbols</key> <true />";
        options += "\n </dict>";
        options += "\n </plist>";

        options = options.Replace("$(teamID)"   , TeamIdentity);
        options = options.Replace("$(method)"   , ExportMethod);
        options = options.Replace("$(bundleID)" , AppPackageID);
        options = options.Replace("$(provision)", Provisioning);
        options = options.Replace("$(bitcode)"  , AllowBitcode);

        string plistFilePath = Path.Combine(directory, "ExportOptions.plist");
        File.WriteAllText(plistFilePath, options);
    }

    private static void ExportIPA(string directory)
    {
        string scriptPath = Path.Combine(directory, "Export.sh");

        string script = "";
        script +=/**/"#!/bin/bash";
        script += "\n ";
        script += "\n set -e -u";
        script += "\n ";
        script += "\n cd `dirname $0`";
        script += "\n ";
        script += "\n cmd_line=\"xcodebuild\"";
        script += "\n cmd_line=\"$cmd_line clean\"";
        script += "\n cmd_line=\"$cmd_line archive\"";
        script += "\n cmd_line=\"$cmd_line -project Unity-iPhone.xcodeproj\"";
        script += "\n cmd_line=\"$cmd_line -scheme Unity-iPhone\"";
        script += "\n cmd_line=\"$cmd_line -configuration Release\"";
        script += "\n cmd_line=\"$cmd_line BITCODE_GENERATION_MODE=bitcode\"";
        script += "\n cmd_line=\"$cmd_line -archivePath Unity-iPhone.xcarchive\"";
        script += "\n $cmd_line";
        script += "\n ";
        script += "\n cmd_line=\"xcodebuild\"";
        script += "\n cmd_line=\"$cmd_line -exportArchive\"";
        script += "\n cmd_line=\"$cmd_line -archivePath Unity-iPhone.xcarchive\"";
        script += "\n cmd_line=\"$cmd_line -exportOptionsPlist ExportOptions.plist\"";
        script += "\n cmd_line=\"$cmd_line -exportPath Export\"";
        script += "\n $cmd_line";

        File.WriteAllText(scriptPath, script);

        Process process = new Process();
        process.StartInfo.UseShellExecute = true;
        process.StartInfo.FileName = "sh";
        process.StartInfo.Arguments = scriptPath;
        process.Start();
        process.WaitForExit();
        process.Close();
    }

    private static void MoveProducts(string fromDir)
    {
        string toXCArch = Path.Combine(ProductDPath, ProductsName) + ".xcarchive";
        string toAppIPA = Path.Combine(ProductDPath, ProductsName) + ".ipa";

        if (!Directory.Exists(ProductDPath))
        {
            Directory.CreateDirectory(ProductDPath);
        }
        if (Directory.Exists(toXCArch))
        {
            Directory.Delete(toXCArch, true);
        }
        if (File.Exists(toAppIPA))
        {
            File.Delete(toAppIPA);
        }

        string fromXCArch = Path.Combine(fromDir, "Unity-iPhone.xcarchive");
        string fromAppIPA = Path.Combine(fromDir, "Export", "Unity-iPhone.ipa");

        Directory.Move(fromXCArch, toXCArch);
        File.Move(fromAppIPA, toAppIPA);
    }
}
