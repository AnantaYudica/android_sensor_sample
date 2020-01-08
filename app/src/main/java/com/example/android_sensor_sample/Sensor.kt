package com.example.android_sensor_sample

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.FrameLayout
import android.widget.Switch

abstract class Sensor (private var id : Int,
              private var ctx : Context,
              private var parent : ViewGroup)
{
    private var sensor_layout : View
    private var enable_switch : Switch
    private var detail_expand_layout : FrameLayout
    private var output_expand_layout : FrameLayout
    private var event_expand_layout : FrameLayout
    private var sensor_detail : SensorDetail
    private var sensor_event : SensorEvent
    init
    {
        sensor_layout = LayoutInflater.from(ctx).inflate(R.layout.sensor, null)
        enable_switch = sensor_layout.findViewById(R.id.enable_switch)
        detail_expand_layout = sensor_layout.findViewById(R.id.detail_expand_layout)
        output_expand_layout = sensor_layout.findViewById(R.id.output_expand_layout)
        event_expand_layout = sensor_layout.findViewById(R.id.event_expand_layout)
        sensor_detail = SensorDetail(id, ctx, detail_expand_layout)
        sensor_event = SensorEvent(id, ctx, event_expand_layout)
        enable_switch.setOnClickListener(::enableSwitchOnClick)
        parent.addView(sensor_layout)

        sensor_detail.update()
        sensor_event.update()
        enable_switch.isChecked = SensorManager.getInstance().isEnable(id)
    }
    protected fun addOutputLayout(child : View)
    {
        output_expand_layout.addView(child)
    }
    protected fun removeOutputLayout(child : View)
    {
        output_expand_layout.removeView(child)
    }
    abstract fun typeName() : String
    private fun enableSwitchOnClick(v : View) {
        if (v is Switch) {
            if (v.isChecked) {
                SensorManager.getInstance().enable(id)
            } else {
                SensorManager.getInstance().disable(id)
            }
        }
    }
    open fun update()
    {
    }
    protected fun setTypeName(value : String)
    {
        enable_switch.text = value
    }
}
