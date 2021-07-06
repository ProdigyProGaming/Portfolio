using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EscPauseCheck : MonoBehaviour
{
    public OptionsManager optionsManager;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            optionsManager.pauseResumeCheck();
        }
    }
}
