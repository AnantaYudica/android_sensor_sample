package com.example.android_sensor_sample.storage.col

import androidx.room.*

@Dao
interface PropertyDao
{
    @Query("SELECT * FROM Property")
    fun getAll(): List<Property>

    @Query("SELECT `key` FROM Property")
    fun getKeys() : List<String>

    @Query("SELECT * FROM Property WHERE `key` LIKE :key LIMIT 1")
    fun find(key : String): Property

    @Update
    fun update(property: Property)

    @Insert
    fun insertAll(vararg property: Property)

    @Delete
    fun delete(property: Property)
}