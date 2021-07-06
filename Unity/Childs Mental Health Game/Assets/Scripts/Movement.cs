using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Movement : MonoBehaviour
{
    private Vector3 screenPoint;
    private Vector3 offset;
    
    private void OnMouseDown()
    {
        if (!Paused.paused)
        {
            screenPoint = Camera.main.WorldToScreenPoint(transform.position);
            offset = transform.position -
                     Camera.main.ScreenToWorldPoint(
                         new Vector3(Input.mousePosition.x, Input.mousePosition.y, screenPoint.z));
        }
        
    }

    private void OnMouseDrag()
    {
        if (!Paused.paused)
        {
            Vector3 curScreenPoint = new Vector3(Input.mousePosition.x, Input.mousePosition.y, screenPoint.z);
            Vector3 curPosition = Camera.main.ScreenToWorldPoint(curScreenPoint) + offset;
            transform.position = curPosition;
        }
        
    }
}
