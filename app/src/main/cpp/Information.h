//
// Created by Ananta Yudica on 21/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_INFORMATION_H
#define ANDROID_SENSOR_SAMPLE_INFORMATION_H

#include "jni.h"
#include <utility>

class Information
{
private:
    static Information * ms_instance;
private:
    static void __SetValueFromString(char * &ref_value, const char * cstr,
            const size_t & size);
    static void __SetValueFromStaticField(char * &ref_value, JNIEnv* pEnv,
           jclass * pClass, jfieldID * pFieldid);
    static void __ResetValue(char * &ref_value);
public:
    static Information & GetInstance();
    template<typename... TArgs>
    static inline Information & CreateInstance(TArgs && ... args);
    static void DestroyInstance();
    static bool HasInstance();
private:
    char * m_os;
    char * m_version;
    char * m_brand;
    char * m_device;
    char * m_hardware;
    char * m_manufacturer;
    char * m_model;
    char * m_product;
private:
    void LoadInformation(const char * os, JNIEnv* pEnv);
    void InitOS(const char * os);
    void InitVersion(JNIEnv* pEnv, jclass * pClass);
    void InitBrand(JNIEnv* pEnv, jclass * pClass);
    void InitDevice(JNIEnv* pEnv, jclass * pClass);
    void InitHardware(JNIEnv* pEnv, jclass * pClass);
    void InitManufacturer(JNIEnv* pEnv, jclass * pClass);
    void InitModel(JNIEnv* pEnv, jclass * pClass);
    void InitProduct(JNIEnv* pEnv, jclass * pClass);
private:
    Information(const char * os, JNIEnv* pEnv);
public:
    ~Information();
public:
    Information(const Information &) = delete;
    Information(Information &&) = delete;
public:
    Information & operator=(const Information &) = delete;
    Information &operator=(Information &&) = delete;
public:
    const char * OS() const;
    const char * Version() const;
    const char * Brand() const;
    const char * Device() const;
    const char * Hadrdware() const;
    const char * Manufacturer() const;
    const char * Model() const;
    const char * Product() const;
};

template<typename... TArgs>
inline Information & Information::CreateInstance(TArgs && ... args)
{
    if (ms_instance) return *ms_instance;
    ms_instance = new Information(std::forward<TArgs>(args)...);
    return *ms_instance;
}

#endif //ANDROID_SENSOR_SAMPLE_INFORMATION_H
