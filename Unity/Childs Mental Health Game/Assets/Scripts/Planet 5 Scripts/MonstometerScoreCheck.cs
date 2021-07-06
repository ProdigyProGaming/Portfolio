using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonstometerScoreCheck : MonoBehaviour
{
    public ScoreLoader scores;
    public CamersSwitcher switcher;
    
    private int[] correctValues;
    private int[] freeBoxes;
    public GameObject[] boxes;
    public GameObject[] words;
    private int score;
    private int addedScore;
    
    // Start is called before the first frame update
    void Start()
    {
        correctValues = new[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        freeBoxes = new[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        addedScore = 0;
    }
    
    public int CheckWordCollision(Vector3 colPos1, Vector3 colPos2)
    {
        int returnVal = 0;
        int collisionStack = 0;
        foreach (GameObject word in words)
        {
            var pos = word.transform.position;
            if (pos.x == colPos1.x && pos.y == colPos1.y)
            {
                returnVal = 2;
                collisionStack++;
            }
            if (pos.x == colPos2.x && pos.y == colPos2.y)
            {
                returnVal = 1;
                collisionStack++;
            }
        }

        if (collisionStack == 2)
        {
            returnVal = 3;
        }
        return returnVal;
    }
    public void CheckAnswers()
    {
        for (int i = 0; i < words.Length; i++)
        {
            Vector3 tempVector = words[i].transform.localPosition + new Vector3(0, 0, 0f);
            float distance = Vector3.Distance(tempVector, boxes[correctValues[i]].transform.localPosition);
            float tol = 0.00000001f;
            if (distance <= tol)
            {
                score++;
            }
        }

        if (addedScore < score)
        {
            PlayerPrefs.SetInt("bags", PlayerPrefs.GetInt("bags") + (score - addedScore));
            scores.updateScores();
            addedScore = score;
        }
        if (score == 10)
        {
            switcher.NextActivity();
            Debug.Log("WIN");
        }
        
        score = 0;
    }
}
