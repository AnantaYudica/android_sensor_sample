//
// Created by Ananta Yudica on 12/01/2020.
//

#include "CollectionManager.h"

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
