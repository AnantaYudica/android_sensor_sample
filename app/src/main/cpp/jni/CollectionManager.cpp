//
// Created by Ananta Yudica on 12/01/2020.
//

#include "CollectionManager.h"

#include <functional>

namespace bridge
{
constexpr uint8_t CollectionManager::FLAG_LINKED;
constexpr uint8_t CollectionManager::FLAG_INIT;
constexpr uint8_t CollectionManager::FLAG_PRE_INIT;

constexpr char CollectionManager::NAME_CLASS[];

constexpr char CollectionManager::NAME_GET_INSTANCE[];
constexpr char CollectionManager::NAME_HAS_INSTANCE[];
constexpr char CollectionManager::NAME_DESTROY_INSTANCE[];
constexpr char CollectionManager::NAME_HAS_PROPERTY[];
constexpr char CollectionManager::NAME_GET_PROPERTY[];
constexpr char CollectionManager::NAME_INIT_PROPERTY[];
constexpr char CollectionManager::NAME_SET_PROPERTY[];

constexpr char CollectionManager::SIGNATURE_GET_INSTANCE[];
constexpr char CollectionManager::SIGNATURE_HAS_INSTANCE[];
constexpr char CollectionManager::SIGNATURE_DESTROY_INSTANCE[];
constexpr char CollectionManager::SIGNATURE_HAS_PROPERTY[];
constexpr char CollectionManager::SIGNATURE_GET_PROPERTY[];
constexpr char CollectionManager::SIGNATURE_INIT_PROPERTY[];
constexpr char CollectionManager::SIGNATURE_SET_PROPERTY[];

bool CollectionManager::LinkMethod(JNIEnv * env, jclass * _class, const char * name_str,
    const char * signature_str, jmethodID *& out_methodid)
{
    return (*out_methodid = env->GetMethodID(*_class, name_str,
            signature_str)) != NULL;
}

bool CollectionManager::LinkStaticMethod(JNIEnv * env, jclass * _class, const char * name_str,
     const char * signature_str, jmethodID *& out_methodid)
{
    return (*out_methodid = env->GetStaticMethodID(*_class, name_str,
            signature_str)) != NULL;
}

CollectionManager::CollectionManager(JNIEnv* env) :
    m_flags(0),
    m_jvm(nullptr),
    m_class(nullptr),
    m_getInstanceMethodid(nullptr),
    m_hasInstanceMethodid(nullptr),
    m_destroyInstanceMethodid(nullptr),
    m_hasPropertyMethodid(nullptr),
    m_getPropertyMethodid(nullptr),
    m_initPropertyMethodid(nullptr),
    m_setPropertyMethodid(nullptr)
{
    Link(env);
}

CollectionManager::~CollectionManager()
{}

bool CollectionManager::__HasInstanceCall(bool def, JNIEnv * env)
{
    return env->CallStaticBooleanMethod(*m_class, *m_hasInstanceMethodid);
}

bool CollectionManager::__HasInstance()
{
    using namespace std::placeholders;
    if (!IsLinked()) return false;
    std::function<bool(bool, JNIEnv *)> fun =
        std::bind(&CollectionManager::__HasInstanceCall, this, _1, _2);
    return __Call<bool>(false, fun);
}

void CollectionManager::__DestroyInstanceCall(JNIEnv * env)
{
    env->CallStaticVoidMethod(*m_class, *m_destroyInstanceMethodid);
}

void CollectionManager::__DestroyInstance()
{
    using namespace std::placeholders;
    if (!IsLinked() && !IsPreInit() && !IsInit()) return;
    SetPreClean();
    std::function<void(JNIEnv *)> fun =
        std::bind(&CollectionManager::__DestroyInstanceCall, this, _1);
    __Call<void>(fun);
    Unlink();
}

void CollectionManager::SetLinked()
{
    m_flags.fetch_or(FLAG_LINKED, std::memory_order_release);
}

void CollectionManager::SetUnlinked()
{
    m_flags.fetch_and(~FLAG_LINKED, std::memory_order_release);
}

void CollectionManager::SetInit()
{
    m_flags.fetch_or(FLAG_INIT, std::memory_order_release);
}

void CollectionManager::SetClean()
{
    m_flags.fetch_and(~FLAG_INIT, std::memory_order_release);
}

void CollectionManager::SetPreInit()
{
    m_flags.fetch_or(FLAG_PRE_INIT, std::memory_order_release);
}

void CollectionManager::SetPreClean()
{
    m_flags.fetch_and(~FLAG_PRE_INIT, std::memory_order_release);
}

void CollectionManager::Init()
{
    SetPreInit();
    m_env = nullptr;
    m_jvm = nullptr;
    m_class = new jclass;
    m_getInstanceMethodid = new jmethodID;
    m_hasInstanceMethodid = new jmethodID;
    m_destroyInstanceMethodid = new jmethodID;
    m_hasPropertyMethodid = new jmethodID;
    m_getPropertyMethodid = new jmethodID;
    m_initPropertyMethodid = new jmethodID;
    m_setPropertyMethodid = new jmethodID;
    SetInit();
}

int CollectionManager::Clean(int ret)
{
    SetPreClean();
    if (m_jvm) m_jvm = nullptr;
    if (m_env) m_env = nullptr;
    {
        const std::lock_guard<std::mutex> lock(m_callbackMutex);
        for (auto it = m_callback.begin(); it != m_callback.end(); it++)
            delete (*it);
        m_callback.clear();
    }
    if (m_class) delete m_class;
    m_class = nullptr;
    if (m_getInstanceMethodid) delete m_getInstanceMethodid;
    m_getInstanceMethodid = nullptr;
    if (m_hasInstanceMethodid) delete m_hasInstanceMethodid;
    m_hasInstanceMethodid = nullptr;
    if (m_destroyInstanceMethodid) delete m_destroyInstanceMethodid;
    m_destroyInstanceMethodid = nullptr;
    if (m_hasPropertyMethodid) delete m_hasPropertyMethodid;
    m_hasPropertyMethodid = nullptr;
    if (m_getPropertyMethodid) delete m_getPropertyMethodid;
    m_getPropertyMethodid = nullptr;
    if (m_initPropertyMethodid) delete m_initPropertyMethodid;
    m_initPropertyMethodid = nullptr;
    if (m_setPropertyMethodid) delete m_setPropertyMethodid;
    m_setPropertyMethodid = nullptr;
    SetClean();
    return ret;
}

int CollectionManager::Link(JNIEnv* p_env)
{
    if (IsLinked() && !IsInit() && !IsPreInit()) return 0;
    if (!p_env) return -2;
    Init();
    m_env = p_env;
    p_env->GetJavaVM(&m_jvm);
    *m_class = (jclass) p_env->NewGlobalRef((jobject)p_env->FindClass(NAME_CLASS));
    if (!*m_class) return Clean(-3);
    if (!LinkStaticMethod(p_env, m_class, NAME_GET_INSTANCE, SIGNATURE_GET_INSTANCE,
            m_getInstanceMethodid)) return Clean(-4);
    if (!LinkStaticMethod(p_env, m_class, NAME_HAS_INSTANCE, SIGNATURE_HAS_INSTANCE,
            m_hasInstanceMethodid)) return Clean(-4);
    if (!LinkStaticMethod(p_env, m_class, NAME_DESTROY_INSTANCE, SIGNATURE_DESTROY_INSTANCE,
            m_destroyInstanceMethodid)) return Clean(-4);
    if (!LinkMethod(p_env, m_class, NAME_HAS_PROPERTY, SIGNATURE_HAS_PROPERTY,
            m_hasPropertyMethodid)) return Clean(-4);
    if (!LinkMethod(p_env, m_class, NAME_GET_PROPERTY, SIGNATURE_GET_PROPERTY,
            m_getPropertyMethodid)) return Clean(-4);
    if (!LinkMethod(p_env, m_class, NAME_INIT_PROPERTY, SIGNATURE_INIT_PROPERTY,
            m_initPropertyMethodid)) return Clean(-4);
    if (!LinkMethod(p_env, m_class, NAME_SET_PROPERTY, SIGNATURE_SET_PROPERTY,
            m_setPropertyMethodid)) return Clean(-4);
    SetLinked();
    return 1;
}

void CollectionManager::Unlink()
{
    if (!IsLinked() && IsInit() && IsPreInit()) return;
    m_env->DeleteGlobalRef((jobject)*m_class);
    Clean(0);
    SetUnlinked();
}

bool CollectionManager::IsLinked() const
{
    return m_flags.load(std::memory_order_consume) & FLAG_LINKED;
}

bool CollectionManager::IsInit() const
{
    return m_flags.load(std::memory_order_consume) & FLAG_INIT;
}

bool CollectionManager::IsPreInit() const
{
    return m_flags.load(std::memory_order_consume) & FLAG_PRE_INIT;
}

void CollectionManager::HasPropertyCall(JNIEnv * env, const char * key_cstr,
    void * callback_ptr)
{
    jobject obj = env->CallStaticObjectMethod(*m_class, *m_getInstanceMethodid);
    if (obj == NULL) return;
    jstring key = env->NewStringUTF(key_cstr);
    jlong native_cb = reinterpret_cast<jlong>(callback_ptr);
    env->CallVoidMethod(obj, *m_hasPropertyMethodid, key, native_cb);
}

void CollectionManager::HasProperty(const char * key_cstr,
    std::function<void(const char *, bool)> callback)
{
    using namespace std::placeholders;
    using CallbackFunType = std::function<void(const char *, bool)>;
    if (!IsLinked()) return;

    func::Callback * cb = new func::callback::Function<CallbackFunType>(callback);
    {
        const std::lock_guard<std::mutex> lock(m_callbackMutex);
        m_callback.insert(m_callback.end(), cb);
    }
    std::function<void(JNIEnv *, const char *, void *)> fun =
        std::bind(&CollectionManager::HasPropertyCall, this, _1, _2, _3);
    __Call<void>(fun, key_cstr, (void *)cb);
}

void CollectionManager::GetPropertyCall(JNIEnv * env, const char * key_cstr,
    void * callback_ptr)
{
    jobject obj = env->CallStaticObjectMethod(*m_class, *m_getInstanceMethodid);
    if (obj == NULL) return;
    jstring key = env->NewStringUTF(key_cstr);
    jlong native_cb = reinterpret_cast<jlong>(callback_ptr);
    env->CallVoidMethod(obj, *m_getPropertyMethodid, key, native_cb);
}

void CollectionManager::GetProperty(const char * key_cstr,
    std::function<void(const char *, const char *)> callback)
{
    using namespace std::placeholders;
    using CallbackFunType = std::function<void(const char *, const char *)>;
    if (!IsLinked()) return;

    func::Callback * cb = new func::callback::Function<CallbackFunType>(callback);
    {
        const std::lock_guard<std::mutex> lock(m_callbackMutex);
        m_callback.insert(m_callback.end(), cb);
    }
    std::function<void(JNIEnv *, const char *, void *)> fun =
        std::bind(&CollectionManager::GetPropertyCall, this, _1, _2, _3);
    __Call<void>(fun, key_cstr, (void *)cb);
}

void CollectionManager::InitPropertyCall(JNIEnv * env, const char * key_cstr,
    const char * val_cstr, void * callback_ptr)
{
    jobject obj = env->CallStaticObjectMethod(*m_class, *m_getInstanceMethodid);
    if (obj == NULL) return;
    jstring key = env->NewStringUTF(key_cstr);
    jstring val = env->NewStringUTF(val_cstr);
    jlong native_cb = reinterpret_cast<jlong>(callback_ptr);
    env->CallVoidMethod(obj, *m_initPropertyMethodid, key, val, native_cb);
}

void CollectionManager::InitProperty(const char * key_cstr, const char * val_cstr,
    std::function<void(const char *, const char *, bool, const char *)> callback)
{
    using namespace std::placeholders;
    using CallbackFunType = std::function<void(const char *,
            const char *, bool, const char *)>;
    if (!IsLinked()) return;

    void * ptr = nullptr;
    if (callback)
    {
        func::Callback * cb = new func::callback::Function<CallbackFunType>(callback);
        const std::lock_guard<std::mutex> lock(m_callbackMutex);
        m_callback.insert(m_callback.end(), cb);
        ptr = (void *)cb;
    }
    std::function<void(JNIEnv *, const char *, const char *, void *)> fun =
        std::bind(&CollectionManager::InitPropertyCall, this, _1, _2, _3, _4);
    __Call<void>(fun, key_cstr, val_cstr, ptr);
}

void CollectionManager::SetPropertyCall(JNIEnv * env, const char * key_cstr,
    const char * val_cstr, void * callback_ptr)
{
    jobject obj = env->CallStaticObjectMethod(*m_class, *m_getInstanceMethodid);
    if (obj == NULL) return;
    jstring key = env->NewStringUTF(key_cstr);
    jstring val = env->NewStringUTF(val_cstr);
    jlong native_cb = reinterpret_cast<jlong>(callback_ptr);
    env->CallVoidMethod(obj, *m_setPropertyMethodid, key, val, native_cb);
}

void CollectionManager::SetProperty(const char * key_cstr, const char * val_cstr,
    std::function<void(const char *, const char *)> callback)
{
    using namespace std::placeholders;
    using CallbackFunType = std::function<void(const char *, const char *)>;
    if (!IsLinked()) return;

    void * ptr = nullptr;
    if (callback)
    {
        func::Callback * cb = new func::callback::Function<CallbackFunType>(callback);
        const std::lock_guard<std::mutex> lock(m_callbackMutex);
        m_callback.insert(m_callback.end(), cb);
        ptr = (void *)cb;
    }

    std::function<void(JNIEnv *, const char *, const char *, void *)> fun =
        std::bind(&CollectionManager::SetPropertyCall, this, _1, _2, _3, _4);
    __Call<void>(fun, key_cstr, val_cstr, ptr);
}

extern "C"
void Java_com_example_android_1sensor_1sample_CollectionManager_hasPropertyNativeCallback(
    JNIEnv* pEnv, jobject pThis, jstring key, jboolean result, jlong native_cb)
{
    auto instance = dynamic_cast<bridge::CollectionManager*>(&CollectionManager::GetInstance());
    if (!instance) return;

    const char * key_cstr = pEnv->GetStringUTFChars(key, NULL);
    instance->template Callback<void>(native_cb, key_cstr, (bool)result);
    pEnv->ReleaseStringUTFChars(key, key_cstr);
}

extern "C"
void Java_com_example_android_1sensor_1sample_CollectionManager_getPropertyNativeCallback(
    JNIEnv* pEnv, jobject pThis, jstring key, jstring result, jlong native_cb)
{
    auto instance = dynamic_cast<bridge::CollectionManager*>(&CollectionManager::GetInstance());
    if (!instance) return;

    const char * key_cstr = pEnv->GetStringUTFChars(key, NULL);
    const char * result_cstr = pEnv->GetStringUTFChars(result, NULL);
    instance->template Callback<void>(native_cb, key_cstr, result_cstr);
    pEnv->ReleaseStringUTFChars(key, key_cstr);
    pEnv->ReleaseStringUTFChars(result, result_cstr);
}

extern "C"
void Java_com_example_android_1sensor_1sample_CollectionManager_initPropertyNativeCallback(
    JNIEnv* pEnv, jobject pThis, jstring key, jstring value,
    jboolean is_init, jstring curr_value, jlong native_cb)
{
    auto instance = dynamic_cast<bridge::CollectionManager*>(&CollectionManager::GetInstance());
    if (!instance) return;

    const char * key_cstr = pEnv->GetStringUTFChars(key, NULL);
    const char * value_cstr = pEnv->GetStringUTFChars(value, NULL);
    const char * curr_value_cstr = pEnv->GetStringUTFChars(curr_value, NULL);
    instance->template Callback<void>(native_cb, key_cstr, value_cstr, (bool)is_init,
            curr_value_cstr);
    pEnv->ReleaseStringUTFChars(key, key_cstr);
    pEnv->ReleaseStringUTFChars(value, value_cstr);
    pEnv->ReleaseStringUTFChars(curr_value, curr_value_cstr);
}

extern "C"
void Java_com_example_android_1sensor_1sample_CollectionManager_setPropertyNativeCallback(
    JNIEnv* pEnv, jobject pThis, jstring key, jstring value, jlong native_cb)
{
    auto instance = dynamic_cast<bridge::CollectionManager*>(&CollectionManager::GetInstance());
    if (!instance) return;

    const char * key_cstr = pEnv->GetStringUTFChars(key, NULL);
    const char * value_cstr = pEnv->GetStringUTFChars(value, NULL);
    instance->template Callback<void>(native_cb, key_cstr, value_cstr);
    pEnv->ReleaseStringUTFChars(key, key_cstr);
    pEnv->ReleaseStringUTFChars(value, value_cstr);
}


} //!bridge
