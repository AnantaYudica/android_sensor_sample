package com.example.android_sensor_sample.storage

import androidx.room.Database
import androidx.room.RoomDatabase
import com.example.android_sensor_sample.storage.col.Property
import com.example.android_sensor_sample.storage.col.PropertyDao

@Database( entities = [Property::class], version = 1)
abstract class Collection : RoomDatabase()
{
    abstract fun property() : PropertyDao
}