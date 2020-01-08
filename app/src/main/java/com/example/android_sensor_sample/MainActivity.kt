package com.example.android_sensor_sample

import android.hardware.Sensor
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.widget.LinearLayout
import com.example.android_sensor_sample.sensor.Accelerometer

class MainActivity : AppCompatActivity() {
    val native = Native()
    lateinit var acclerometer : Accelerometer
        lateinit var updateHandler : Handler
    private val updateJob = object : Runnable {
        override fun run() {
            update()
            updateHandler.postDelayed(this, 10)
        }
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        native.onCreate()
        setContentView(R.layout.activity_main)
        val sensors_layout = findViewById<LinearLayout>(R.id.sensors_layout)
        updateHandler = Handler(Looper.getMainLooper())
        val res = SensorManager.getInstance().find(Sensor.TYPE_ACCELEROMETER)

        acclerometer = Accelerometer(res[0], this, sensors_layout)
        acclerometer.link()
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
        acclerometer.unlink()
        native.onDestroy()
    }

    fun update()
    {
        native.update()
        acclerometer.update()
    }

}
