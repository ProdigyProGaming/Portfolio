using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;
using Random = UnityEngine.Random;

public class GiveHelp : MonoBehaviour
{
    public GameObject textBubble;

    public static GiveHelp instance;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void Awake()
    {
        instance = this;
    }

    public static void giveHelp(int number)
    {
        instance.StartCoroutine(giveHelpCoRoutine(number));
    }

    static IEnumerator giveHelpCoRoutine(int number)
    {
        string temp = number.ToString();
        int planetNumber = int.Parse(temp.Substring(0, 1));
        int activityNumber = int.Parse(temp.Substring(1, 1));
        int extraNumber = int.Parse(temp.Substring(2, 1));

        string[] helpTexts = new string[3];
        
        switch (planetNumber)
        {
            case 5:
                switch (activityNumber)
                {
                    case 1:
                        helpTexts[0] = "Click next when you are finished";
                        helpTexts[1] = "Place the things you worry about on the tree";
                        helpTexts[2] = "Drag the leaves to stick them to the tree";
                        break;
                    case 2:
                        switch (extraNumber)
                        {
                            case 1:
                                helpTexts[0] = "Scared Help Tip 1";
                                helpTexts[1] = "Scared Help Tip 2";
                                helpTexts[2] = "Scared Help Tip 3";
                                break;
                            case 2:
                                helpTexts[0] = "Angry Help Tip 1";
                                helpTexts[1] = "Angry Help Tip 2";
                                helpTexts[2] = "Angry Help Tip 3";
                                break;
                            case 3:
                                helpTexts[0] = "Sad Help Tip 1";
                                helpTexts[1] = "Sad Help Tip 2";
                                helpTexts[2] = "Sad Help Tip 3";
                                break;
                            case 4:
                                helpTexts[0] = "Excited Help Tip 1";
                                helpTexts[1] = "Excited Help Tip 2";
                                helpTexts[2] = "Excited Help Tip 3";
                                break;
                            case 5:
                                helpTexts[0] = "Surprise Help Tip 1";
                                helpTexts[1] = "Surprise Help Tip 2";
                                helpTexts[2] = "Surprise Help Tip 3";
                                break;
                        }
                        break;
                    case 3:
                        helpTexts[0] = "Thermometer Help Tip 1";
                        helpTexts[1] = "Thermometer Help Tip 2";
                        helpTexts[2] = "Thermometer Help Tip 3";
                        break;
                }
                break;
        }
        int selection = Random.Range(0, 3);
        instance.textBubble.GetComponentInChildren<TextMeshPro>().text= helpTexts[selection];
        instance.textBubble.SetActive(true);
        yield return new WaitForSeconds(5);
        instance.textBubble.SetActive(false);
    }
}
