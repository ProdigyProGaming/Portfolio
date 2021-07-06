using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelSelection : MonoBehaviour
{
    public Button[] levelButtons;
    public Sprite emptyStar;
    public Sprite fullStar;
    
    void Start()
    {
        int levelCompleted = PlayerPrefs.GetInt("levelCompleted", 0);
        for (int i = 0; i < levelButtons.Length; i++)
        {
            if (i > levelCompleted)
            {
                levelButtons[i].interactable = false;
                levelButtons[i].transform.GetChild(1).gameObject.GetComponent<Image>().sprite = emptyStar;
            }

            if (i < levelCompleted)
            {
                levelButtons[i].transform.GetChild(1).gameObject.GetComponent<Image>().sprite = fullStar;
            }
        }
    }

    public void loadLevel(int level)
    {
        LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
        levelChanger.FadeToLevel(level * 3);
        //SceneManager.LoadScene(level * 3);
    }
}
