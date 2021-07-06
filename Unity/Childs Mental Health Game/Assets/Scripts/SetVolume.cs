using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class SetVolume : MonoBehaviour
{
    public AudioMixer mixer;
    public Slider volumeSlider;

    private void OnEnable()
    {
        SetSlider();
    }

    public void SetLevel(float sliderValue)
    {
        mixer.SetFloat("MusicVolume", Mathf.Log10(sliderValue) * 20);
    }
    
    private void SetSlider()
    {
        float value;
        float value2 = 10;

        mixer.GetFloat("MusicVolume", out value);
        volumeSlider.value = Mathf.Pow(value2, value / 20);
    }
}
