using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.PlayerLoop;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Customisation : MonoBehaviour
{
    public Button colourButton1;
    public Button colourButton2;
    public Button colourButton3;

    public Button modelButton1;
    public Button modelButton2;
    public Button modelButton3;

    public Color[] colours;
    public Sprite[] buttonSprites;

    private int colourStart;
    private int colourMiddle;
    private int colourEnd;
    private int modelStart;
    private int modelMiddle;
    private int modelEnd;
    private int offset;

    public Sprite[] sprites;
    public GameObject customisee;
    private int colourSelected;

    public GameObject canvasToActivate;
    public GameObject canvasToDeactivate;
    
    // Start is called before the first frame update
    void Start()
    {
        colourStart = 0;
        colourMiddle = 1;
        colourEnd = 2;
        modelStart = 0;
        modelMiddle = 1;
        modelEnd = 2;
        offset = 0;
        colourSelected = 0;
        RefreshButtons();
    }

    public void SetColour(int buttonPressed)
    {
        switch (buttonPressed)
        {
            case 1:
                colourSelected = colourStart;
                break;
            case 2:
                colourSelected = colourMiddle;
                break;
            case 3:
                colourSelected = colourEnd;
                break;
        }
        customisee.GetComponent<SpriteRenderer>().sprite = sprites[colourSelected + offset];
    }

    public void SetModel(int buttonPressed)
    {
        switch (buttonPressed)
        {
            case 1:
                offset = modelStart * 4;
                break;
            case 2:
                offset = modelMiddle * 4;
                break;
            case 3:
                offset = modelEnd * 4;
                break;
        }
        customisee.GetComponent<SpriteRenderer>().sprite = sprites[colourSelected + offset];
    }
    
    public void ColourCycleUp()
    {
        if (colourStart != 0)
        {
            colourStart--;
            colourMiddle--;
            colourEnd--;
            RefreshButtons();
        }
    }

    public void ColourCycleDown()
    {
        if (colourEnd != colours.Length - 1)
        {
            colourStart++;
            colourMiddle++;
            colourEnd++;
            RefreshButtons();
        }
    }

    public void ModelCycleUp()
    {
        if (modelStart != 0)
        {
            modelStart--;
            modelMiddle--;
            modelEnd--;
            RefreshButtons();
        }
    }

    public void ModelCycleDown()
    {
        if (modelEnd != buttonSprites.Length - 1)
        {
            modelStart++;
            modelMiddle++;
            modelEnd++;
            RefreshButtons();
        }
    }

    void RefreshButtons()
    {
        colourButton1.GetComponent<Image>().color = colours[colourStart];
        colourButton2.GetComponent<Image>().color = colours[colourMiddle];
        colourButton3.GetComponent<Image>().color = colours[colourEnd];

        modelButton1.GetComponent<Image>().sprite = buttonSprites[modelStart];
        modelButton2.GetComponent<Image>().sprite = buttonSprites[modelMiddle];
        modelButton3.GetComponent<Image>().sprite = buttonSprites[modelEnd];
    }

    public void NextCustom(int customisationNumber)
    {
        if (customisationNumber == 1)
        {
            PlayerPrefs.SetInt("playerColour", colourSelected + offset);
        }
        else if (customisationNumber == 2)
        {
            PlayerPrefs.SetInt("companionColour", colourSelected + offset);
        }
        
        //offset = 0?
        canvasToDeactivate.SetActive(false);
        canvasToActivate.SetActive(true);
    }

    public void NextScene()
    {
        PlayerPrefs.SetInt("rocketColour", colourSelected + offset);
        LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
        levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 1);
        //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }
}
