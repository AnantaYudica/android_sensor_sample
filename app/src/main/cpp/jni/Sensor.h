//
// Created by Ananta Yudica on 04/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_H
#define ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_H

#include "jni.h"
#include <type_traits>
#include <utility>
#include <cstdio>

namespace bridge
{

class Sensor
{
public:
    typedef typename std::remove_pointer<JNIEnv>::type EnvironmentType;
private:
    static constexpr char ms_format_method_signature[] = "(%s)I";
    static constexpr size_t ms_format_method_signature_size =
            sizeof(ms_format_method_signature);
private:
    bool m_linked;
    JavaVM * m_jvm;
    JNIEnv * m_env;
    jclass * m_class;
    jobject * m_object;
    jmethodID * m_callMethodid;
public:
    Sensor();
public:
    virtual ~Sensor();
public:
    Sensor(const Sensor & cpy);
    Sensor(Sensor && mov);
public:
    Sensor & operator=(const Sensor &) = delete;
    Sensor & operator=(Sensor &&) = delete;
private:
    void Init();
    void Clean();
    const char * MethodSignature(char *& buf, const size_t & size, const char * param_sig);
protected:
    virtual std::pair<const char *, size_t> ParameterSignature() = 0;
protected:
    template<typename T,  typename... TArgs>
    T Environment(T(EnvironmentType::*fun_mem)(TArgs...), TArgs && ... args);
public:
    int Link(JNIEnv* p_env, jobject p_this, const char * link_method_name);
    void Unlink(JNIEnv* p_env);
public:
    template<typename... TArgs>
    int Call(TArgs &&... args);
public:
    bool IsLink() const;
};

template<typename... TArgs>
int Sensor::Call(TArgs &&... args)
{
    JNIEnv * env;
    int env_stat = m_jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (env_stat == JNI_EDETACHED)
    {
        if (m_jvm->AttachCurrentThread(&env, NULL) != 0) return 0;
        auto ret = env->CallIntMethod(*m_object, *m_callMethodid,
                std::forward<TArgs>(args)...);

        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }

        m_jvm->DetachCurrentThread();

        return ret;
    }
    else if (env_stat == JNI_OK)
    {
        return m_env->CallIntMethod(*m_object, *m_callMethodid,
                std::forward<TArgs>(args)...);
    }
    return 0;

}

template<typename T,  typename... TArgs>
T Sensor::Environment(T(EnvironmentType::*fun_mem)(TArgs ...), TArgs && ... args)
{
    return (m_env->*fun_mem)(std::forward<TArgs>(args)...);
}

} //!bridge

#endif //ANDROID_SENSOR_SAMPLE_BRIDGE_SENSOR_H
