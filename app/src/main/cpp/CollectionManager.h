//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_COLLECTIONMANAGER_H
#define ANDROID_SENSOR_SAMPLE_COLLECTIONMANAGER_H

#include "Log.h"

#include <functional>
#include <utility>

class CollectionManager
{
private:
    static CollectionManager * ms_instance;
public:
    template<typename TDerived, typename ... TArgs>
    static CollectionManager & CreateInstance(TArgs && ... args);
    static CollectionManager & GetInstance();
    static bool HasInstance();
    static void DestroyInstance();
protected:
    CollectionManager();
public:
    virtual ~CollectionManager();
protected:
    virtual bool __HasInstance() = 0;
    virtual void __DestroyInstance() = 0;
public:
    virtual void HasProperty(const char * key_cstr,
        std::function<void(const char *, bool)> callback) = 0;
    bool HasProperty(const char * key_cstr);
public:
    virtual void GetProperty(const char * key_cstr,
        std::function<void(const char *, const char *)> callback) = 0;
    void GetProperty(const char * key_cstr, char * out_value, const size_t & value_size);
public:
    virtual void InitProperty(const char * key_cstr, const char * val_cstr,
        std::function<void(const char *, const char *, bool, const char *)> callback) = 0;
    void InitProperty(const char * key_cstr, const char * val_cstr);
public:
    virtual void SetProperty(const char * key_cstr, const char * val_cstr,
         std::function<void(const char *, const char *)> callback) = 0;
    void SetProperty(const char * key_cstr, const char * val_cstr);
};

template<typename TDerived, typename ... TArgs>
CollectionManager & CollectionManager::CreateInstance(TArgs && ... args)
{
    LOG_DEBUG("CollectionManager", "CollectionManager::CreateInstance(...)");
    if (!ms_instance)
        ms_instance = new TDerived(std::forward<TArgs>(args)...);
    return *ms_instance;
}

#endif //ANDROID_SENSOR_SAMPLE_COLLECTIONMANAGER_H
