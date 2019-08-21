using UnityEngine;

public class GameRoot : MonoBehaviour
{
    public static GameObject    GameObject { get; private set; }
    public static MonoBehaviour Behaviour  { get; private set; }

    void Awake()
    {
        DontDestroyOnLoad(gameObject);
        GameObject = gameObject;
        Behaviour = this;
    }

    void Start()
    {
    }
}
