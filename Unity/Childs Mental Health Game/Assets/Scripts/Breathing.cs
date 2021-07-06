using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;
using UnityEngine.SceneManagement;

public class Breathing : MonoBehaviour
{
    public GameObject tw;
    public GameObject countdownText;

    public GameObject timer;
    public PlayableAsset breatheIn;
    public PlayableAsset breatheOut;
    
    private bool finished;
    
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(Breathe());
        finished = false;


    }

    private void Update()
    {
        if (finished)
        {
            LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
            levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 1);
        }
        
    }

    void PlayBreatheIn()
    {
        timer.GetComponent<PlayableDirector>().playableAsset = breatheIn;
        timer.GetComponent<PlayableDirector>().Play();
    }
    
    void PlayBreatheOut()
    {
        timer.GetComponent<PlayableDirector>().playableAsset = breatheOut;
        timer.GetComponent<PlayableDirector>().Play();
    }

    IEnumerator Breathe()
    {
        int repeat = 2;
        for (int i = 0; i < 3; i++)
        {
            tw.GetComponent<TypeWriter>().BeginTyping("Take a deep breath in and count to 3" + ((i == 0) ? " with me": ""));
            countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "0";
            yield return new WaitForSeconds(3);
            StartCoroutine(Counter());
            PlayBreatheIn();
            yield return new WaitForSeconds(3);
            tw.GetComponent<TypeWriter>().BeginTyping("And breathe out and count to 3");
            countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "0";
            yield return new WaitForSeconds(3);
            StartCoroutine(Counter());
            PlayBreatheOut();
            yield return new WaitForSeconds(4);
            if (repeat != 0)
            {
                tw.GetComponent<TypeWriter>().BeginTyping(((i == 0) ? "Now do it " : "") + repeat + " more time" + ((repeat == 1) ? "" : "s"));
                repeat--;
            }
            countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "0";
            yield return new WaitForSeconds(3);
        }
        tw.GetComponent<TypeWriter>().BeginTyping("Well Done!");
        yield return new WaitForSeconds(2);
        finished = true;
    }
    
    IEnumerator Counter()
    {
        countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "1";
        yield return new WaitForSeconds(1);
        countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "2";
        yield return new WaitForSeconds(1);
        countdownText.GetComponent<TMPro.TextMeshProUGUI>().text = "3";
        yield return new WaitForSeconds(1);
    }
}
