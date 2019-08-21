using UnityEngine;

public static class D
{
    public static void Info(string format, params object[] args)
    {
        Debug.LogFormat(format, args);
    }

    public static void Error(string format, params object[] args)
    {
        Debug.LogErrorFormat(format, args);
    }
}
