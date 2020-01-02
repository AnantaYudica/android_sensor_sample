package com.example.android_sensor_sample

import androidx.appcompat.app.AppCompatDialog
import android.content.Context
import android.content.DialogInterface
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView

class NumberDialog<T>(private var ctx : Context,
                      private var onUpdateCallback : ((T)->Int),
                      private var onCastFromString : ((String)->T),
                      private var onCastToString : ((T)->String)) :
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
        value_name = findViewById(R.id.value_name)
        value_update = findViewById(R.id.value_update)
        unit_name = findViewById(R.id.unit_name)
        cancel_btn = findViewById(R.id.cancel_btn)
        update_btn = findViewById(R.id.update_btn)
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
        onUpdateCallback.invoke(onCastFromString(value_update?.text.toString()))
        dismiss()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    fun setTitleName(value: String)
    {
        setTitle(value)
    }

    fun setValueName(value : String)
    {
        value_name?.text = value
    }

    fun setValue(value : T)
    {
        value_update?.setText(onCastToString(value))
    }

    fun setUnitName(value : String)
    {
        unit_name?.text = value
    }

    fun setButtonCancelName(value : String)
    {
        cancel_btn?.text = value
    }

    fun setButtonUpdateName(value : String)
    {
        update_btn?.text = value
    }
}
