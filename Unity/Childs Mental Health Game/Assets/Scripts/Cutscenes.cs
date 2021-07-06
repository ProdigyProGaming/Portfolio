using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Cutscenes : MonoBehaviour
{
    public GameObject text;
    public GameObject cutsceneCanvas;
    public GameObject activityCanvas;
    private IEnumerator cutscene = null;
    
    public void Planet5Cutscene1()
    {
        string[] messages = new string[4];
        messages[0] = "The first problem is all about worries";
        messages[1] = "The worry tree has dropped all its leaves";
        messages[2] = "We need you to pick up the leaves that have your feelings on";
        messages[3] = "Once you have put all the leaves on, just click next!";
        cutscene = PlayScene(messages);
        StartCoroutine(cutscene);
    }
    
    public void Planet5Cutscene2()
    {
        string[] messages = new string[5];
        messages[0] = "Great Job!";
        messages[1] = "The next problem we need help with is identifying emotions";
        messages[2] = "Each of these monsters are feeling something";
        messages[3] = "We need to figure out how they are feeling by matching the words";
        messages[4] = "There should be 3 words to match for each monster";
        cutscene = PlayScene(messages);
        StartCoroutine(cutscene);
    }
    
    public void Planet5Cutscene3()
    {
        string[] messages = new string[4];
        messages[0] = "Nice Work!";
        messages[1] = "Finally, there are a bunch of emotions that we aren't sure about";
        messages[2] = "We need to figure out where on the thermometer each one goes";
        messages[3] = "Drag the word into the correct box and click next to check your answer";
        cutscene = PlayScene(messages);
        StartCoroutine(cutscene);
    }
    
    IEnumerator PlayScene(string[] messages)
    {
        string currentText;
        string fullText;
        float delay = 0.05f;
        
        foreach (var s in messages)
        {
            //tw.GetComponent<TypeWriter>().BeginTyping(s);
            
            currentText = "";
            fullText = s;
            for (int i = 0; i <= fullText.Length; i++)
            {
                currentText = fullText.Substring(0, i);
                text.GetComponent<Text>().text = currentText;
                yield return new WaitForSeconds(delay);
            }
            
            yield return new WaitForSeconds(3);
        }
        playActivity();
    }

    public void stopText()
    {
        StopCoroutine(cutscene);
    }
    
    public void playActivity()
    {
        cutsceneCanvas.SetActive(false);
        activityCanvas.SetActive(true);
    }
}
