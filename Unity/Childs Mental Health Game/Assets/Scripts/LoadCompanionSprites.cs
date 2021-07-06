using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LoadCompanionSprites : MonoBehaviour
{
    public GameObject[] companions;
    public Sprite[] companionSprites;
    // Start is called before the first frame update
    void Start()
    {
        if (companions != null)
        {
            foreach (GameObject companion in companions)
            {
                companion.GetComponent<Image>().sprite = companionSprites[PlayerPrefs.GetInt("companionColour")];
            }
            
            //companion.GetComponent<SpriteRenderer>().sprite = companionSprites[PlayerPrefs.GetInt("companionColour")];
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
