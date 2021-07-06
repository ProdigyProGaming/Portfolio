using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TypeWriter : MonoBehaviour
{
    public float delay = 0.1f;
    public string fullText;
    private string currentText = "";
    private bool stopVal = false;
    //int arrayValue = 0;


    public void BeginTyping(string text)
    {
        fullText = text;
        StartCoroutine(ShowText());
        stopVal = false;
    }
    
    void Update()
    {
        /*
        if (Input.GetMouseButtonDown(0))
        {
            stopVal = true;
            Skip();
        }    
        */
    }
    /*
    void Skip()
    {
        if (currentText.Length < fullText.Length)
        {
            currentText = fullText;
            GetComponent<Text>().text = currentText;
        }
        
    }
    */
    IEnumerator ShowText()
    {
        currentText = "";
        for (int i = 0; i <= fullText.Length; i++)
        {
            if (!stopVal)
            {
                currentText = fullText.Substring(0, i);
                GetComponent<Text>().text = currentText;
                yield return new WaitForSeconds(delay);
            }
        }

        stopVal = false;
    }
}