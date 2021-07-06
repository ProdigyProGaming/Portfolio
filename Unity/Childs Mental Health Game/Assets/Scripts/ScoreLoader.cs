using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreLoader : MonoBehaviour
{
    public GameObject starText;
    public GameObject bagText;
    
    // Start is called before the first frame update
    void Start()
    {
        updateScores();
    }

    public void updateScores()
    {
        starText.GetComponent<Text>().text = "x " + PlayerPrefs.GetInt("stars");
        bagText.GetComponent<Text>().text = "x " + PlayerPrefs.GetInt("bags");
    }
}
