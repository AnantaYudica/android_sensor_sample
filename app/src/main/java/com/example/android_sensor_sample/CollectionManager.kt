package com.example.android_sensor_sample

import android.content.Context
import androidx.room.Room
import com.example.android_sensor_sample.storage.Collection
import com.example.android_sensor_sample.storage.col.Property
import java.util.*

class CollectionManager(private val ctx : Context)
{
    companion object
    {
        @Volatile private var ms_instance : CollectionManager? = null
        @JvmStatic fun createInstance(ctx : Context)
        {
            if (ms_instance != null) return
            ms_instance = CollectionManager(ctx)
            ms_instance?.start()
        }
        @JvmStatic fun destroyInstance()
        {
            ms_instance?.close()
            ms_instance?.stop()
            ms_instance?.join()
            ms_instance = null
        }
        @JvmStatic fun hasInstance() : Boolean
        {
            return ms_instance != null
        }
        @JvmStatic fun getInstance() : CollectionManager?
        {
            return ms_instance
        }
    }
    private var m_thread : Thread
    private var m_db : Collection?
    private var m_queue : Queue<(()->Unit)?>
    private var m_run : Boolean
    private var m_join : Boolean
    init
    {
        System.loadLibrary("Bridge")
        m_thread = Thread(::run)
        m_db = Room.databaseBuilder(ctx.applicationContext,
            Collection::class.java, "test_db").
            fallbackToDestructiveMigration().build()
        m_queue = LinkedList()
        m_run = false
        m_join = true
    }
    private fun start()
    {
        if (m_run || !m_join) return
        m_run = true
        m_join = false
        m_thread.start()
    }
    private fun stop()
    {
        m_run = false
    }
    private fun join()
    {
        m_thread.join()
        m_join = true
    }
    private fun close()
    {
        m_db?.close()
    }
    fun hasProperty(key: String,
                    callback : (String, Boolean)->Unit)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            callback(key, f != null)
        }
    }
    fun getProperty(key: String,
                    callback : (String, String)->Unit)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            callback(key, f?.value ?: "")
        }
    }
    fun initProperty(key: String, value: String,
                     callback: ((String, String, Boolean, String) -> Unit)? = null)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            var curr = value
            if(f == null) m_db?.property()?.insertAll(Property(key = "$key", value = "$value"))
            else curr = f.value
            callback?.invoke(key, value, f == null, curr)
        }
    }
    fun setProperty(key: String, value: String,
                    callback : ((String, String)->Unit)? = null)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            val valueF = f?.value ?: ""
            if(f == null) m_db?.property()?.insertAll(Property(key = "$key", value = "$value"))
            else if (valueF.compareTo(value) != 0)
                m_db?.property()?.update(Property(id = f?.id, key = "$key", value = "$value"))
            callback?.invoke(key, value)
        }
    }
    fun run() : Unit
    {
        while (m_run)
        {
            if (m_queue.size != 0)
            {
                val ts = m_queue.remove()
                ts?.invoke()
            }
        }
    }
}
