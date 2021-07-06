using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MonsterEmotions : MonoBehaviour
{
    public ScoreLoader scores;
    public CamersSwitcher switcher;
    
    private int score = 0;
    private int lastScore = 0;
    public GameObject Alien;
    public Sprite[] AlienSprites;
    public string[] alienLabels;
    public GameObject alienLabelText;
    private int currentAlien;
    private int[] currentCorrectButtons = new int[3];
    public Text scoreText;
    private int localScore = 0;

    public GameObject button;
    
    // Start is called before the first frame update
    void Start()
    {
        currentAlien = -1;
        NextAlien();
    }
    
    public void AddPoints(int buttonPressed)
    {
        if (currentCorrectButtons.Contains(buttonPressed))
        {
            score++;
            localScore++;
            int buttonIndex = Array.IndexOf(currentCorrectButtons, buttonPressed);
            currentCorrectButtons[buttonIndex] = 0;
        }
        scoreText.GetComponent<Text>().text = localScore.ToString();
        if (score == (AlienSprites.Length * 3))
        {
            PlayerPrefs.SetInt("bags", PlayerPrefs.GetInt("bags") + 1);
            scores.updateScores();
            switcher.NextActivity();
            //Next Activity
            /*
            cameraToDeactivate.SetActive(false);
            cameraToActivate.SetActive(true);
            */
        }
        else if (score == lastScore + 3)
        {
            PlayerPrefs.SetInt("bags", PlayerPrefs.GetInt("bags") + 1);
            scores.updateScores();
            NextAlien();
        }
    }

    void NextAlien()
    {
        currentAlien++;
        Alien.GetComponent<SpriteRenderer>().sprite = AlienSprites[currentAlien];
        alienLabelText.GetComponent<Text>().text = alienLabels[currentAlien];
        
        lastScore = score;
        localScore = 0;
        scoreText.GetComponent<Text>().text = localScore.ToString();
        
        currentCorrectButtons[0] = lastScore + 1;
        currentCorrectButtons[1] = lastScore + 2;
        currentCorrectButtons[2] = lastScore + 3;
        
        updateHelpText();
    }

    void updateHelpText()
    {
        int tempNum = 520 + (currentAlien + 1);
        button.GetComponent<Button>().onClick.AddListener( () => GiveHelp.giveHelp(tempNum));
    }

}
