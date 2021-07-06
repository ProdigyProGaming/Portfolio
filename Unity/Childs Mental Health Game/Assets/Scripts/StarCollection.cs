using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarCollection : MonoBehaviour
{
    public ScoreLoader scores;
    private void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("CollectionStar"))
        {
            PlayerPrefs.SetInt("stars", PlayerPrefs.GetInt("stars") + 1);
            scores.updateScores();
            Destroy(other.gameObject);
        }
    }
}
