package com.example.android_sensor_sample

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageButton
import android.widget.TextView

class SensorEvent(private var id : Int,
                  private var ctx : Context,
                  private var parent : ViewGroup) {
    private var sensor_event_layout: View
    private var delay_value: TextView
    private var delay_unit_name: TextView
    private var delay_update_btn: Button
    private var pause_btn: ImageButton
    private var play_btn: ImageButton
    private var stop_btn: ImageButton
    private var delayNumberDialog: NumberDialog<Float>

    init {
        sensor_event_layout = LayoutInflater.from(ctx).inflate(R.layout.sensor_event, null)
        delay_value = sensor_event_layout.findViewById(R.id.delay_value)
        delay_unit_name = sensor_event_layout.findViewById(R.id.delay_unit_name)
        delay_update_btn = sensor_event_layout.findViewById(R.id.delay_update_btn)
        pause_btn = sensor_event_layout.findViewById(R.id.pause_btn)
        play_btn = sensor_event_layout.findViewById(R.id.play_btn)
        stop_btn = sensor_event_layout.findViewById(R.id.stop_btn)
        delayNumberDialog = NumberDialog(
            ctx, ::delayUpdateCallback,
            ::delayCastFromStringCallback, ::delayToStringCallback)
        delay_update_btn.setOnClickListener(::delayUpdateOnClick)
        pause_btn.setOnClickListener(::pauseOnClick)
        play_btn.setOnClickListener(::playOnClick)
        stop_btn.setOnClickListener(::stopOnClick)
        update()
        parent.addView(sensor_event_layout)
    }
    private fun delayUpdateOnClick(v: View)
    {
        delayNumberDialog.show()
    }
    private fun pauseOnClick(v: View)
    {
        SensorManager.getInstance().pause(id)
        update()
    }
    private fun playOnClick(v: View)
    {
        if (SensorManager.getInstance().isPause(id))
        {
            SensorManager.getInstance().resume(id)
        }
        else
        {
            SensorManager.getInstance().start(id)
        }
        update()
    }
    private fun stopOnClick(v: View)
    {
        SensorManager.getInstance().stop(id)
        update()
    }
    private fun delayUpdateCallback(value : Float) : Int
    {
        if (value == delay()) return 0
        val minDelayMicrosecond = SensorManager.getInstance().minDelay(id)
        val minDelay = minDelayMicrosecond.toFloat() / 1000
        if (value < minDelay)
        {
            SensorManager.getInstance().delay(id, minDelayMicrosecond)
            setDelay(minDelay)
        }
        else
        {
            SensorManager.getInstance().delay(id, (value * 1000).toInt())
            setDelay(value)
        }
        update()
        return 0
    }
    private fun delayCastFromStringCallback(value : String) : Float
    {
        return value.toFloat()
    }
    private fun delayToStringCallback(value : Float) : String
    {
        return String.format("%f", value)
    }
    private fun setDelay(value : Float)
    {
        delay_value.text = delayToStringCallback(value)
    }
    private fun setDelayUnitName()
    {
        delay_unit_name.setText(R.string.miliseconds)
    }
    fun update()
    {
        setDelay(delay())
        setDelayUnitName()
        if (SensorManager.getInstance().isEnable(id))
        {
            if (SensorManager.getInstance().isPause(id))
            {
                pause_btn.visibility = View.GONE
            }
            else
            {
                pause_btn.visibility = View.VISIBLE
            }
            if (SensorManager.getInstance().isRun(id))
            {
                stop_btn.visibility = View.VISIBLE
                play_btn.visibility = View.GONE
                play_btn.isClickable = false
            }
            else
            {
                stop_btn.visibility = View.GONE
                play_btn.visibility = View.VISIBLE
                play_btn.isClickable = true
            }
        }
        else
        {
            pause_btn.visibility = View.GONE
            stop_btn.visibility = View.GONE
            play_btn.visibility = View.VISIBLE
            play_btn.isClickable = false
        }
    }
    fun delay() : Float
    {
        return SensorManager.getInstance().delay(id).toFloat() / 1000
    }
}
