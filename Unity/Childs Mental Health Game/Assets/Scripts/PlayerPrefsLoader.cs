using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPrefsLoader : MonoBehaviour
{
    public GameObject player;
    public Sprite[] playerSprites;
    public GameObject companion;
    public Sprite[] companionSprites;
    public GameObject rocket;
    public Sprite[] rocketSprites;
    
    // Start is called before the first frame update
    void Start()
    {
        if (player != null)
        {
            player.GetComponent<SpriteRenderer>().sprite = playerSprites[PlayerPrefs.GetInt("playerColour")];
        }
        if (companion != null)
        {
            companion.GetComponent<SpriteRenderer>().sprite = companionSprites[PlayerPrefs.GetInt("companionColour")];
        }

        if (rocket != null)
        {
            rocket.GetComponent<SpriteRenderer>().sprite = rocketSprites[PlayerPrefs.GetInt("rocketColour")];
        }
    }
}
