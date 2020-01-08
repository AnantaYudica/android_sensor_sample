package com.example.android_sensor_sample


class SensorManager
{
    companion object
    {
        @Volatile private var instance : SensorManager = SensorManager()
        @JvmStatic external fun hasInstance() : Boolean
        fun getInstance() : SensorManager
        {
            return instance
        }
    }
    init
    {
        System.loadLibrary("Bridge")
    }
    external fun size() : Int
    external fun findOne(sensor_type: Int) : Int
    external fun find(sensor_type : Int) : IntArray
    external fun type(id : Int) : Int
    external fun minDelay(id : Int) : Int
    external fun resolution(id : Int) : Float
    external fun name(id : Int) : String
    external fun vendor(id : Int) : String
    external fun lastErrorCode(id : Int) : Int
    external fun delay(id : Int, value : Int) : Void
    external fun delay(id : Int) : Int
    external fun enable(id : Int) : Void
    external fun disable(id : Int) : Void
    external fun pause(id : Int) : Void
    external fun resume(id : Int) : Void
    external fun start(id : Int) : Void
    external fun stop(id : Int) : Void
    external fun isError(id : Int) : Boolean
    external fun isEnable(id : Int) : Boolean
    external fun isPause(id : Int) : Boolean
    external fun isRun(id : Int) : Boolean
    external fun link(id : Int, obj : Any, name : String) : Int
    external fun unlink(id : Int) : Void
}
