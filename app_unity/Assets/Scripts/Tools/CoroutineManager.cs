using System.Collections;
using UnityEngine;

public static class CoroutineManager
{
    public static MonoBehaviour Behaviour { get; set; }

    public static Coroutine StartCoroutine(IEnumerator routine)
    {
        if (Behaviour != null)
        {
            D.Error("behaviour is null, initialize it when app startup");
            return null;
        }

        return Behaviour.StartCoroutine(routine);
    }
}
