using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StarCollectionMovingBackground : MonoBehaviour
{
    private int counter;
    static Vector3 amountToMove;
    // Start is called before the first frame update
    void Start()
    {
        counter = 0;
        amountToMove = new Vector3(-0.004f, 0, 0); //-0.002f
    }

    // Update is called once per frame
    void Update()
    {
        if (counter != 17822) //35765
        {
            transform.localPosition = transform.localPosition + amountToMove;
            //transform.position = transform.position + amountToMove;
            counter++;
        }
        else
        {
            LevelChanger levelChanger = FindObjectOfType<LevelChanger>();
            levelChanger.FadeToLevel(SceneManager.GetActiveScene().buildIndex + 1);
            //SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        }
    }
}
