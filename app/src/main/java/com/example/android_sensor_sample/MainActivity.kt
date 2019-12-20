package com.example.android_sensor_sample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper

class MainActivity : AppCompatActivity() {
    val native = Native()
    lateinit var updateHandler : Handler
    private val updateJob = object : Runnable {
        override fun run() {
            update()
            updateHandler.postDelayed(this, 1000)
        }
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        native.onCreate()
        setContentView(R.layout.activity_main)
        updateHandler = Handler(Looper.getMainLooper())
    }

    override fun onStart() {
        super.onStart()
        native.onStart()
    }

    override fun onResume() {
        super.onResume()
        native.onResume()
        updateHandler.post(updateJob)
    }

    override fun onPause() {
        super.onPause()
        native.onPause()
        updateHandler.removeCallbacks(updateJob)
    }

    override fun onStop() {
        super.onStop()
        native.onStop()
    }

    override fun onRestart() {
        super.onRestart()
        native.onRestart()
    }

    override fun onDestroy() {
        super.onDestroy()
        native.onDestroy()
    }

    fun update()
    {
        native.update()
    }

}
