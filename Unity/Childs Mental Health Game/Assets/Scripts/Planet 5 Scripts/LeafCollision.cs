using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LeafCollision : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D other)
    {
        this.gameObject.GetComponent<Rigidbody2D>().gravityScale = 0;
        this.gameObject.GetComponent<Rigidbody2D>().velocity = new Vector3(0, 0, 0);
    }

    private void OnTriggerExit2D(Collider2D other)
    {
        this.gameObject.GetComponent<Rigidbody2D>().gravityScale = 1;
    }
}
