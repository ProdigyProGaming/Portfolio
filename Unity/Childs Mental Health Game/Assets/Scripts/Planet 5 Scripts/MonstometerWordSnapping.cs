using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonstometerWordSnapping : MonoBehaviour
{
    private int collided;
    private Vector3 collisionPosition1;
    private Vector3 collisionPosition2;
    private bool secondWord;
    private int positionStorageFlip;
    public MonstometerScoreCheck scoreCheckScript;
    
    // Start is called before the first frame update
    void Start()
    {
        collided = 0;
        positionStorageFlip = 0;
    }

    private void OnMouseDown()
    {
        var pos = this.gameObject.transform.position;
        this.gameObject.transform.position = new Vector3(pos.x, pos.y, pos.z + 1);
    }

    private void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.tag.Equals("MonstometerWord"))
        {
            //secondWord = true;
        }
        if (other.gameObject.tag.Equals("MonstometerBox"))
        {
            Vector3 temp = new Vector3(other.transform.position.x, other.transform.position.y, 0);
            if (positionStorageFlip == 0 && !(collisionPosition2.Equals(temp)))
            {
                collisionPosition1 = temp;
            }
            else if (positionStorageFlip == 1 && !(collisionPosition1.Equals(temp)))
            {
                collisionPosition2 = temp;
            }
            positionStorageFlip = positionStorageFlip == 0 ? 1 : 0;
            collided++;
        }
        
    }

    private void OnCollisionExit2D(Collision2D other)
    {
        if (other.gameObject.tag.Equals("MonstometerBox"))
        {
            collided--;
        }

        if (other.gameObject.tag.Equals("MonstometerWord"))
        {
            secondWord = false;
        }
    }

    private void OnMouseUp()
    {
        if (collided >= 1 && !secondWord)
        {
            int result = scoreCheckScript.CheckWordCollision(collisionPosition1, collisionPosition2);
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            float distance1 = Vector3.Distance(mousePos, collisionPosition1);
            float distance2 = Vector3.Distance(mousePos, collisionPosition2);
            if (result == 0)
            {
                if (distance1 <= distance2)
                {
                    this.gameObject.transform.position = collisionPosition1;
                }
                else
                {
                    this.gameObject.transform.position = collisionPosition2;
                }
            }
            else if (result == 1)
            {
                if (distance1 <= distance2)
                {
                    this.gameObject.transform.position = collisionPosition1;
                }
            }
            else if (result == 2)
            {
                if (distance2 <= distance1)
                {
                    this.gameObject.transform.position = collisionPosition2;
                }
            }
        }
    }
}
