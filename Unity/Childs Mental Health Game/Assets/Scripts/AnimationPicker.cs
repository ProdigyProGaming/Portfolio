using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

public class AnimationPicker : MonoBehaviour
{
    public PlayableAsset rocketAnimation;
    public PlayableAsset hovercraftAnimation;
    
    // Start is called before the first frame update
    void Start()
    {
        if (PlayerPrefs.GetInt("rocketColour") > 3 && 
            PlayerPrefs.GetInt("rocketColour") < 12)
        {
            GetComponent<PlayableDirector>().playableAsset = rocketAnimation;
            Debug.Log("HERE");
        }
        else
        {
            GetComponent<PlayableDirector>().playableAsset = hovercraftAnimation;
            
        }
        /*
        if (GetComponent<SpriteRenderer>().sprite.name.Substring(0, 12) == "RocketModel2" || 
            GetComponent<SpriteRenderer>().sprite.name.Substring(0, 12) == "RocketModel3")
        {
            GetComponent<PlayableDirector>().playableAsset = rocketAnimation;
            Debug.Log("HERE");
            
        }
        else
        {
            GetComponent<PlayableDirector>().playableAsset = hovercraftAnimation;
            
        }
        */
        GetComponent<PlayableDirector>().Play();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
