using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Audio;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public GameObject optionsMenu;
    public GameObject mainMenu;
    public GameObject resetProgessPopUp;

    

    public void PlayGame()
    {
        LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
        levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 1);
        //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void OpenOptionsMenu()
    {
        optionsMenu.SetActive(true);
        mainMenu.SetActive(false);
    }
    
    public void QuitGame()
    {
        Debug.Log("Quit");
        Application.Quit();
    }
    
    public void CloseOptionsMenu()
    {
        mainMenu.SetActive(true);
        optionsMenu.SetActive(false);
    }

    public void ResetProgress()
    {
        resetProgessPopUp.SetActive(true);
    }

    public void ResetProgressYes()
    {
        PlayerPrefs.DeleteKey("levelCompleted");
        PlayerPrefs.DeleteKey("stars");
        PlayerPrefs.DeleteKey("bags");
        ResetProgressNo();
    }

    public void ResetProgressNo()
    {
        resetProgessPopUp.SetActive(false);
    }
}
