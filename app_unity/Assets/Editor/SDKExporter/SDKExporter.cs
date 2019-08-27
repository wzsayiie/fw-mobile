using System.IO;
using UnityEditor;

public static class SDKExporter
{
    //configuration begin
    private static readonly string[] ExportFiles = {
        "Assets/SDK"
    };
    private const string ExportDirectory = "../BUILD";
    private const string PackageFileName = "sdk.unitypackage";
    //configuration end

    public static void Export()
    {
        if (!Directory.Exists(ExportDirectory))
        {
            Directory.CreateDirectory(ExportDirectory);
        }

        string packagePath = ExportDirectory + "/" + PackageFileName;
        if (File.Exists(packagePath))
        {
            File.Delete(packagePath);
        }

        ExportPackageOptions options = ExportPackageOptions.Recurse;
        AssetDatabase.ExportPackage(ExportFiles, packagePath, options);
    }
}
