using System.IO;
using UnityEditor;

public static class SDKExporter
{
    //configuration begin
    static readonly string[] ExportFiles = {
        Path.Combine("Assets", "SDK")
    };
    static readonly string ExportDirectory = Path.Combine("..", "BUILD");
    static readonly string PackageFileName = "sdk.unitypackage";
    //configuration end

    public static void Export()
    {
        if (!Directory.Exists(ExportDirectory))
        {
            Directory.CreateDirectory(ExportDirectory);
        }

        string packagePath = Path.Combine(ExportDirectory, PackageFileName);
        if (File.Exists(packagePath))
        {
            File.Delete(packagePath);
        }

        ExportPackageOptions options = ExportPackageOptions.Recurse;
        AssetDatabase.ExportPackage(ExportFiles, packagePath, options);
    }
}
