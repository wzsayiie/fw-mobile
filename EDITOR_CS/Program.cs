using System.Diagnostics;
using System.Reflection;
using System.IO;
using System;

class Program
{
    static void Initialize()
    {
        StackTrace stackTrace = new StackTrace(new StackFrame(true));
        StackFrame stackFrame = stackTrace.GetFrame(0);
        string     allPath    = stackFrame.GetFileName();

        string workDirName = "fw-mobile";

        int begin = allPath.IndexOf(workDirName, StringComparison.Ordinal);
        if (begin == -1)
        {
            Terminal.WriteText("failed to find target directory");
            Terminal.Spac(1);
            return;
        }

        string workDirPath = allPath.Substring(0, begin + workDirName.Length);
        Directory.SetCurrentDirectory(workDirPath);

        Terminal.WriteText("work path: {0}", workDirPath);
        Terminal.Spac(1);
    }

    static void Run(string clazz, string method)
    {
        try
        {
            Type type = Type.GetType(clazz);

            BindingFlags flags = 0;
            flags |= BindingFlags.InvokeMethod;
            flags |= BindingFlags.Public;
            flags |= BindingFlags.Static;

            type.InvokeMember(method, flags, null, null, null);
        }
        catch (Exception)
        {
            Terminal.WriteLine("failed to invoke '{0}.{1}'", clazz, method);
        }
    }

    static void Main()
    {
        Initialize();

        Run("Demo", "Entry");
    }
}
