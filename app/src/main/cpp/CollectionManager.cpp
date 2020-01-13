//
// Created by Ananta Yudica on 12/01/2020.
//

#include "CollectionManager.h"

#include <thread>
#include <chrono>
#include <cstring>

CollectionManager * CollectionManager::ms_instance = nullptr;

CollectionManager & CollectionManager::GetInstance()
{
    return *ms_instance;
}

bool CollectionManager::HasInstance()
{
    if (!ms_instance) return false;
    return ms_instance->__HasInstance();
}

void CollectionManager::DestroyInstance()
{
    LOG_DEBUG("CollectionManager", "CollectionManager::DestroyInstance(...)");
    if (!HasInstance()) return;
    ms_instance->__DestroyInstance();
    delete ms_instance;
    ms_instance = nullptr;
}

CollectionManager::CollectionManager()
{
    LOG_DEBUG("CollectionManager", "Constructor(...)");
}

CollectionManager::~CollectionManager()
{
    LOG_DEBUG("CollectionManager", "Destructor(...)");
}

bool CollectionManager::HasProperty(const char * key_cstr)
{
    bool result = false;
    std::atomic_bool flag(false);
    HasProperty(key_cstr, [&](const char * key, bool res)
    {
        result = res;
        flag.store(true, std::memory_order_release);
    });
    while(!flag.load(std::memory_order_consume))
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return result;
}

void CollectionManager::GetProperty(const char * key_cstr, char * out_value,
    const size_t & value_size)
{
    std::atomic_bool flag(false);
    GetProperty(key_cstr, [&](const char * key, const char * res)
    {
        strncpy(out_value, res, value_size);
        flag.store(true, std::memory_order_release);
    });
    while(!flag.load(std::memory_order_consume))
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void CollectionManager::InitProperty(const char * key_cstr, const char * val_cstr)
{
    std::atomic_bool flag(false);
    InitProperty(key_cstr, val_cstr, [&](const char * key, const char * val,
            bool is_init, const char * curr_val)
    {
        flag.store(true, std::memory_order_release);
    });
    while(!flag.load(std::memory_order_consume))
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void CollectionManager::SetProperty(const char * key_cstr, const char * val_cstr)
{
    std::atomic_bool flag(false);
    SetProperty(key_cstr, val_cstr, [&](const char * key, const char * val)
    {
        flag.store(true, std::memory_order_release);
    });
    while(!flag.load(std::memory_order_consume))
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
