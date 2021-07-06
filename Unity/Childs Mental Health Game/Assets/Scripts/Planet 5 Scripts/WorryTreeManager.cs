using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WorryTreeManager : MonoBehaviour
{
    public ScoreLoader scores;
    public CamersSwitcher switcher;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void NextGame()
    {
        PlayerPrefs.SetInt("bags", PlayerPrefs.GetInt("bags") + 1);
        scores.updateScores();
        switcher.NextActivity();
    }
    
}
