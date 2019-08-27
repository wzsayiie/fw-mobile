using System.Collections;
using UnityEngine;

public static class CoroutineManager
{
    public static Coroutine StartCoroutine(IEnumerator routine)
    {
        if (routine == null)
        {
            D.Error("coroutine object is null");
            return null;
        }

        return SDKRoot.Instance.StartCoroutine(routine);
    }
}
