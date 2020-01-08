package com.example.android_sensor_sample

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView

class SensorDetail(private var id : Int,
                   private var ctx : Context,
                   private var parent : ViewGroup)
{
    private var sensor_detail_layout : View
    private var type_value : TextView
    private var name_value : TextView
    private var minDelay_value : TextView
    private var minDelay_unit_name : TextView
    private var resolution_value : TextView
    private var vendor_value : TextView
    init
    {
        sensor_detail_layout = LayoutInflater.from(ctx).inflate(R.layout.sensor_details, null)
        type_value = sensor_detail_layout.findViewById(R.id.type_value)
        name_value = sensor_detail_layout.findViewById(R.id.name_value)
        minDelay_value = sensor_detail_layout.findViewById(R.id.minDelay_value)
        minDelay_unit_name = sensor_detail_layout.findViewById(R.id.minDelay_unit_name)
        resolution_value = sensor_detail_layout.findViewById(R.id.resolution_value)
        vendor_value = sensor_detail_layout.findViewById(R.id.vendor_value)
        parent.addView(sensor_detail_layout)

        setType()
        setName()
        setMinDelay()
        setResolution()
        setVendor()
    }
    private fun setType()
    {
        type_value.text = String.format("%d", type())
    }
    private fun setName()
    {
        name_value.text = name()
    }
    private fun setMinDelay()
    {
        minDelay_value.text = String.format("%f", minDelay())
        minDelay_unit_name.setText(R.string.miliseconds)
    }
    private fun setResolution()
    {
        resolution_value.text = String.format("%f", resolution())
    }
    private fun setVendor()
    {
        vendor_value.text = vendor()
    }
    fun update()
    {
    }
    fun type() : Int
    {
        return SensorManager.getInstance().type(id)
    }
    fun name() : String
    {
        return SensorManager.getInstance().name(id)
    }
    fun minDelay() : Float
    {
        return SensorManager.getInstance().minDelay(id).toFloat() / 1000
    }
    fun resolution() : Float
    {
        return SensorManager.getInstance().resolution(id)
    }
    fun vendor() : String
    {
        return SensorManager.getInstance().vendor(id)
    }
}
