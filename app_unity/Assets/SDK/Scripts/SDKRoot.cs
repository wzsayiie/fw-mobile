using UnityEngine;

public class SDKRoot : MonoBehaviour
{
    private static SDKRoot instance;

    public static SDKRoot Get()
    {
        if (instance == null)
        {
            GameObject gameObject = new GameObject("SDKRoot");
            instance = gameObject.AddComponent<SDKRoot>();

            DontDestroyOnLoad(gameObject);
        }
        return instance;
    }

    public static SDKRoot Instance
    {
        get
        {
            return Get();
        }
    }
}
