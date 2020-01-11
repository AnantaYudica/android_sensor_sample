package com.example.android_sensor_sample.storage.col

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Property(
    @PrimaryKey(autoGenerate = true) val id: Int? = null,
    @ColumnInfo(name = "key") val key: String,
    @ColumnInfo(name = "value") val value: String
)
