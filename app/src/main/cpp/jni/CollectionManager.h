//
// Created by Ananta Yudica on 12/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_SAMPLE_BRIDGE_COLLECTIONMANAGER_H
#define ANDROID_SENSOR_SAMPLE_SAMPLE_BRIDGE_COLLECTIONMANAGER_H

#include "../CollectionManager.h"
#include "../func/Callback.h"

#include "jni.h"
#include <set>
#include <cstdint>
#include <functional>
#include <atomic>
#include <type_traits>
#include <mutex>

namespace bridge
{

class CollectionManager : public ::CollectionManager
{
private:
    static constexpr uint8_t FLAG_LINKED = 0x01;
    static constexpr uint8_t FLAG_INIT = 0x02;
    static constexpr uint8_t FLAG_PRE_INIT = 0x03;
private:
    static constexpr char NAME_CLASS[] =
        "com/example/android_sensor_sample/CollectionManager";
private:
    static constexpr char NAME_GET_INSTANCE[] = "getInstance";
    static constexpr char NAME_HAS_INSTANCE[] = "hasInstance";
    static constexpr char NAME_DESTROY_INSTANCE[] = "destroyInstance";
    static constexpr char NAME_HAS_PROPERTY[] = "hasProperty";
    static constexpr char NAME_GET_PROPERTY[] = "getProperty";
    static constexpr char NAME_INIT_PROPERTY[] = "initProperty";
    static constexpr char NAME_SET_PROPERTY[] = "setProperty";
private:
    static constexpr char SIGNATURE_GET_INSTANCE[] =
        "()Lcom/example/android_sensor_sample/CollectionManager;";
    static constexpr char SIGNATURE_HAS_INSTANCE[] = "()Z";
    static constexpr char SIGNATURE_DESTROY_INSTANCE[] = "()V";
    static constexpr char SIGNATURE_HAS_PROPERTY[] = "(Ljava/lang/String;J)V";
    static constexpr char SIGNATURE_GET_PROPERTY[] = "(Ljava/lang/String;J)V";
    static constexpr char SIGNATURE_INIT_PROPERTY[] = "(Ljava/lang/String;Ljava/lang/String;J)V";
    static constexpr char SIGNATURE_SET_PROPERTY[] = "(Ljava/lang/String;Ljava/lang/String;J)V";
private:
    static bool LinkMethod(JNIEnv * env, jclass * _class, const char * name_str,
        const char * signature_str, jmethodID *& out_methodid);
    static bool LinkStaticMethod(JNIEnv * env, jclass * _class, const char * name_str,
        const char * signature_str, jmethodID *& out_methodid);
private:
    std::atomic_uint8_t m_flags;
    JavaVM * m_jvm;
    JNIEnv * m_env;
    jclass * m_class;
    jmethodID * m_getInstanceMethodid;
    jmethodID * m_hasInstanceMethodid;
    jmethodID * m_destroyInstanceMethodid;
    jmethodID * m_hasPropertyMethodid;
    jmethodID * m_getPropertyMethodid;
    jmethodID * m_initPropertyMethodid;
    jmethodID * m_setPropertyMethodid;
    std::set<func::Callback *> m_callback;
    std::mutex m_callbackMutex;
public:
    CollectionManager(JNIEnv* env);
public:
    ~CollectionManager();
private:
    template<typename TRet, typename TFun, typename... TArgs>
    typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
    __Call(const TRet & _default, TFun fun, TArgs && ... args);
    template<typename TRet, typename TFun, typename... TArgs>
    typename std::enable_if<std::is_same<TRet, void>::value, void>::type
    __Call(TFun fun, TArgs && ... args);
private:
    bool __HasInstanceCall(bool def, JNIEnv * env);
    bool __HasInstance();
private:
    void __DestroyInstanceCall(JNIEnv * env);
    void __DestroyInstance();
private:
    void SetLinked();
    void SetUnlinked();
    void SetInit();
    void SetClean();
    void SetPreInit();
    void SetPreClean();
private:
    void Init();
    int Clean(int ret);
public:
    int Link(JNIEnv* p_env);
    void Unlink();
public:
    bool IsLinked() const;
    bool IsInit() const;
    bool IsPreInit() const;
public:
    template<typename TRet, typename ... TArgs>
    typename std::enable_if<std::is_same<TRet, void>::value, void>::type
    Callback(intptr_t addr, TArgs && ... args);
    template<typename TRet, typename ... TArgs>
    typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
    Callback(TRet def, intptr_t addr, TArgs && ... args);
private:
    void HasPropertyCall(JNIEnv * env, const char * key_cstr, void * callback_ptr);
public:
    void HasProperty(const char * key_cstr,
        std::function<void(const char *, bool)> callback);
private:
    void GetPropertyCall(JNIEnv * env, const char * key_cstr, void * callback_ptr);
public:
    void GetProperty(const char * key_cstr,
        std::function<void(const char *, const char *)> callback);
private:
    void InitPropertyCall(JNIEnv * env, const char * key_cstr, const char * val_cstr,
        void * callback_ptr);
public:
    void InitProperty(const char * key_cstr, const char * val_cstr,
        std::function<void(const char *, const char *, bool, const char *)> callback = nullptr);
private:
    void SetPropertyCall(JNIEnv * env, const char * key_cstr, const char * val_cstr,
         void * callback_ptr);
public:
    void SetProperty(const char * key_cstr, const char * val_cstr,
        std::function<void(const char *, const char *)> callback = nullptr);
};

template<typename TRet, typename TFun, typename... TArgs>
typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
CollectionManager::__Call(const TRet & _default, TFun fun, TArgs && ... args)
{
    JNIEnv * env;
    int env_stat = m_jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (env_stat == JNI_EDETACHED)
    {
        if (m_jvm->AttachCurrentThread(&env, NULL) != 0) return _default;

        if (env->ExceptionCheck()) return _default;

        TRet res = fun(_default, env, std::forward<TArgs>(args)...);

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }

        m_jvm->DetachCurrentThread();

        return res;
    }
    else if (env_stat == JNI_OK)
    {
        return fun(_default, env, std::forward<TArgs>(args)...);
    }
    return _default;
}

template<typename TRet, typename TFun, typename... TArgs>
typename std::enable_if<std::is_same<TRet, void>::value, void>::type
CollectionManager::__Call(TFun fun, TArgs && ... args)
{
    JNIEnv * env;
    int env_stat = m_jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (env_stat == JNI_EDETACHED)
    {
        if (m_jvm->AttachCurrentThread(&env, NULL) != 0) return;

        fun(env, std::forward<TArgs>(args)...);

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }

        m_jvm->DetachCurrentThread();

    }
    else if (env_stat == JNI_OK)
    {
        return fun(env, std::forward<TArgs>(args)...);
    }
}

template<typename TRet, typename ... TArgs>
typename std::enable_if<std::is_same<TRet, void>::value, void>::type
CollectionManager::Callback(intptr_t addr, TArgs && ... args)
{
    using CallbackFunType = std::function<TRet(TArgs...)>;
    if (addr == 0) return;
    void * ptr = reinterpret_cast<void *>(addr);
    func::Callback * cb = static_cast<func::Callback *>(ptr);
    cb->template Call<void, CallbackFunType>(std::forward<TArgs>(args)...);
    const std::lock_guard<std::mutex> lock(m_callbackMutex);
    m_callback.erase(cb);
    delete cb;
}

template<typename TRet, typename ... TArgs>
typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
CollectionManager::Callback(TRet def, intptr_t addr, TArgs && ... args)
{
    using CallbackFunType = std::function<TRet(TArgs...)>;
    if (addr == 0) return def;
    void * ptr = reinterpret_cast<void *>(addr);
    func::Callback * cb = static_cast<func::Callback *>(ptr);
    TRet res = cb->template Call<TRet, CallbackFunType>(def, std::forward<TArgs>(args)...);
    const std::lock_guard<std::mutex> lock(m_callbackMutex);
    m_callback.erase(cb);
    delete cb;
    return res;
}

} //!bridge

#endif //ANDROID_SENSOR_SAMPLE_SAMPLE_BRIDGE_COLLECTIONMANAGER_H
