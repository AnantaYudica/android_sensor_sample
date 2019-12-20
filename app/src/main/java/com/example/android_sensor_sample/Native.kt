package com.example.android_sensor_sample

class Native
{
    init {
        System.loadLibrary("Bridge")
    }
    external fun onCreate() : Int
    external fun onStart() : Int
    external fun onResume() : Int
    external fun onPause() : Int
    external fun onStop() : Int
    external fun onRestart() : Int
    external fun onDestroy() : Int
    external fun update() : Int
}