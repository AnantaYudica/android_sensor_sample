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
        std::function<void(bool)> callback) = 0;
    virtual void GetProperty(const char * key_cstr,
        std::function<void(const char *)> callback) = 0;
    virtual void InitProperty(const char * key_cstr, const char * val_cstr,
        std::function<void(bool)> callback = nullptr) = 0;
    virtual void SetProperty(const char * key_cstr, const char * val_cstr,
         std::function<void()> callback = nullptr) = 0;
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
