using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TempNextLevel : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Next()
    {
        PlayerPrefs.SetInt("levelCompleted", PlayerPrefs.GetInt("levelCompleted") + 1);
        LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
        levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 3);
        //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 3);
    }
}
