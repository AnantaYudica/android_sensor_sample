package com.example.android_sensor_sample

import androidx.appcompat.app.AppCompatDialog
import android.content.Context
import android.content.DialogInterface
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView

class NumberDialog(private var ctx : Context,
                   var onUpdateCallback: ((Int)->Unit)? = null) :
    DialogInterface.OnCancelListener,
    AppCompatDialog(ctx, true, null)
{
    private var value_name : TextView?
    private var value_update : EditText?
    private var unit_name : TextView?
    private var cancel_btn : Button?
    private var update_btn : Button?
    init
    {
        setOnCancelListener(this)
        setContentView(R.layout.number_dialog)
        setTitle(R.string.number_dialog_title_name)
        value_name = findViewById<TextView>(R.id.value_name)
        value_update = findViewById<EditText>(R.id.value_update)
        unit_name = findViewById<TextView>(R.id.unit_name)
        cancel_btn = findViewById<Button>(R.id.cancel_btn)
        update_btn = findViewById<Button>(R.id.update_btn)
        cancel_btn?.setOnClickListener(::onCancel)
        update_btn?.setOnClickListener(::onUpdate)

    }
    override fun onCancel(dialog: DialogInterface)
    {

    }

    private fun onCancel(v : View)
    {
        cancel()
    }

    private fun onUpdate(v : View)
    {
        onUpdateCallback?.invoke(value_update?.text.toString().toInt())
        dismiss()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    fun SetTitleName(value: String)
    {
        setTitle(value)
    }

    fun SetValueName(value : String)
    {
        value_name?.text = value
    }

    fun SetValue(value : Int)
    {
        value_update?.setText("" + value.toString())
    }

    fun SetUnitName(value : String)
    {
        unit_name?.text = value
    }

    fun SetButtonCancelName(value : String)
    {
        cancel_btn?.text = value
    }

    fun SetButtonUpdateName(value : String)
    {
        update_btn?.text = value
    }
}
