package com.example.android_sensor_sample

import android.content.Context
import androidx.room.Room
import com.example.android_sensor_sample.storage.Collection
import com.example.android_sensor_sample.storage.col.Property
import java.util.*

class StorageManager(private val ctx : Context)
{
    companion object
    {
        @Volatile private var ms_instance : StorageManager? = null
        fun createInstance(ctx : Context)
        {
            if (ms_instance != null) return
            ms_instance = StorageManager(ctx)
            ms_instance?.start()
        }
        fun destroyInstance()
        {
            ms_instance?.close()
            ms_instance?.stop()
            ms_instance?.join()
            ms_instance = null
        }
        fun hasInstance() : Boolean
        {
            return ms_instance != null
        }
        fun getInstance() : StorageManager?
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
        m_thread = Thread(::run)
        m_db = Room.databaseBuilder(ctx.applicationContext,
            Collection::class.java, "test_db").build()
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
    fun hasProperty(key: String, callback : (Boolean)->Unit)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            callback(f != null)
        }
    }
    fun getProperty(key: String, callback : (String)->Unit)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            callback(f?.value ?: "")
        }
    }
    fun initProperty(key: String, value: String, callback: ((Boolean) -> Unit)? = null)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            if(f == null) m_db?.property()?.insertAll(Property(key = "$key", value = "$value"))
            callback?.invoke(f == null)
        }
    }
    fun setProperty(key: String, value: String, callback : (()->Unit)? = null)
    {
        m_queue.offer{
            val f = m_db?.property()?.find(key)
            val valueF = f?.value ?: ""
            if(f == null) m_db?.property()?.insertAll(Property(key = "$key", value = "$value"))
            else
            {
                if (valueF.compareTo(value) != 0)
                {
                    m_db?.property()?.update(Property(id = f?.id, key = "$key", value = "$value"))
                }
            }
            callback?.invoke()
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
