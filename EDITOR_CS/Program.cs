using System.Diagnostics;
using System.IO;
using System;

class Program
{
    static void Initialize()
    {
        string rootDirectory = "fw-mobile";

        StackTrace trace = new StackTrace(new StackFrame(true));
        StackFrame frame = trace.GetFrame(0);
        string fileName = frame.GetFileName();

        int rootBegin = fileName.IndexOf(rootDirectory, StringComparison.Ordinal);
        if (rootBegin != -1)
        {
            string rootPath = fileName.Substring(0, rootBegin + rootDirectory.Length);
            Directory.SetCurrentDirectory(rootPath);
            L.ContinueLast.Write("work directory: {0}", rootPath);
        }
        else
        {
            L.ContinueLast.Write("FAILED TO CHANGE DIRECTORY");
        }
    }

    static void Main()
    {
        Initialize();
        Execute();
        L.SpaceLine(1);
    }

    static void Execute()
    {
        if (Demo.Enabled) { Demo.Entry(); }
    }
}
