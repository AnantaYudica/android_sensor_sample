package com.example.android_sensor_sample.sensor

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.example.android_sensor_sample.R
import com.example.android_sensor_sample.Sensor
import com.example.android_sensor_sample.SensorManager
import java.text.SimpleDateFormat
import java.util.*

class Accelerometer(private var id : Int,
                    private var ctx : Context,
                    private var parent : ViewGroup) :
        Sensor(id, ctx, parent)
{
    private var x : Float
    private var y : Float
    private var z : Float
    private var timestamp : Long
    private var accelerometer_layout : View
    private var x_value : TextView
    private var y_value : TextView
    private var z_value : TextView
    private var timestamp_value : TextView
    private var x_unit_name : TextView
    private var y_unit_name : TextView
    private var z_unit_name : TextView
    init
    {
        accelerometer_layout = LayoutInflater.from(ctx).inflate(R.layout.accelerometer, null)
        x_value = accelerometer_layout.findViewById(R.id.x_value)
        y_value = accelerometer_layout.findViewById(R.id.y_value)
        z_value = accelerometer_layout.findViewById(R.id.z_value)
        timestamp_value = accelerometer_layout.findViewById(R.id.timestamp_value)
        x_unit_name = accelerometer_layout.findViewById(R.id.x_unit_name)
        y_unit_name = accelerometer_layout.findViewById(R.id.y_unit_name)
        z_unit_name = accelerometer_layout.findViewById(R.id.z_unit_name)
        addOutputLayout(accelerometer_layout)
        x = 0.toFloat()
        y = 0.toFloat()
        z = 0.toFloat()
        timestamp = 0

        setXUnitName()
        setYUnitName()
        setZUnitName()

        setTypeName(typeName())
        update()
    }
    private fun setXUnitName()
    {
        x_unit_name.text = ctx.resources.getString(R.string.acceleration_unit_name)
    }
    private fun setYUnitName()
    {
        y_unit_name.text = ctx.resources.getString(R.string.acceleration_unit_name)
    }
    private fun setZUnitName()
    {
        z_unit_name.text = ctx.resources.getString(R.string.acceleration_unit_name)
    }
    override fun typeName() : String
    {
        return ctx.resources.getString(R.string.sensor_accelerometer_name)
    }
    override fun update()
    {
        super.update()
        x_value.text = String.format("%f", x)
        y_value.text = String.format("%f", y)
        z_value.text = String.format("%f", z)
        val milisecond = timestamp / 1000000
        val nanosecond = timestamp - (milisecond * 1000000)
        val dt = Date(milisecond)
        val fmt = SimpleDateFormat("mm:ss:SSS")
        timestamp_value.text = String.format("%s.%d", fmt.format(dt), nanosecond)
    }
    fun link()
    {
        SensorManager.getInstance().link(id, this, "callbackNative")
    }
    fun unlink()
    {
        SensorManager.getInstance().unlink(id)
    }
    fun callbackNative(x : Float, y : Float, z :Float, timestamp : Long) : Int
    {
        this.x = x
        this.y = y
        this.z = z
        this.timestamp = timestamp
        return 1
    }
}
