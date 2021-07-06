using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CamersSwitcher : MonoBehaviour
{
    public GameObject activityCamera1;
    public GameObject activityCamera2;
    public GameObject activityCamera3;
    private int currentActivity;

    public Cutscenes cutscene1;
    public Cutscenes cutscene2;
    public Cutscenes cutscene3;

    private void Start()
    {
        currentActivity = 1;
        cutscene1.Planet5Cutscene1();
    }

    public void NextActivity()
    {
        switch (currentActivity)
        {
            case 1:
                activityCamera1.SetActive(false);
                activityCamera2.SetActive(true);
                currentActivity++;
                cutscene2.Planet5Cutscene2();
                break;
            case 2:
                activityCamera2.SetActive(false);
                activityCamera3.SetActive(true);
                currentActivity++;
                cutscene3.Planet5Cutscene3();
                break;
            case 3:
                LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
                levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 1);
                //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
                break;
        }
    }
}
