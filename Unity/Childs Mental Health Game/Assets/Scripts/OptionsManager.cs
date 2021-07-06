using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class OptionsManager : MonoBehaviour
{
    public GameObject pauseMenuUI;
    public Slider volumeSlider;
    public AudioMixer mixer;

    public void pauseResumeCheck()
    {
        if (Paused.paused)
        {
            Resume();
        }
        else
        {
            Pause();
        }
    }
    
    public void Pause()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0;
        Paused.paused = true;

        //player.GetComponent<PolygonCollider2D>().enabled = false;
        
        float value;
        float value2 = 10;
        bool result = mixer.GetFloat("MusicVolume", out value);
        volumeSlider.value = Mathf.Pow(value2, value/20);
    }
    
    public void Resume()
    {
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1;
        Paused.paused = false;
        //player.GetComponent<PolygonCollider2D>().enabled = true;
    }

    public void MenuButton()
    {
        Resume();
        SceneManager.LoadScene("1 - MainMenu");
    }

    public void QuitButton()
    {
        Debug.Log("Quit");
        Application.Quit();
    }
}
