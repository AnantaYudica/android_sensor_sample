//
// Created by Ananta Yudica on 21/12/2019.
//

#include "Information.h"
#include "Log.h"

#include "jni.h"
#include <cstring>

Information * Information::ms_instance = nullptr;

void Information::__SetValueFromString(char * &ref_value, const char * cstr,
      const size_t & size)
{
    ref_value = new char[size + 1];
    strncpy(ref_value, cstr, size);
    ref_value[size] = '\0';
}

void Information::__SetValueFromStaticField(char * &ref_value, JNIEnv* pEnv,
      jclass * pClass, jfieldID * pFieldID)
{
    jstring jstr = (jstring) pEnv->GetStaticObjectField(*pClass, *pFieldID);
    jsize size = pEnv->GetStringUTFLength(jstr);
    const char * cstr = pEnv->GetStringUTFChars(jstr, 0);
    __SetValueFromString(ref_value, cstr, size);
    pEnv->ReleaseStringUTFChars(jstr, cstr);
}

void Information::__ResetValue(char * &ref_value)
{
    if (ref_value)
    {
        delete[] ref_value;
        ref_value = nullptr;
    }
}

Information & Information::GetInstance()
{
    return *ms_instance;
}

void Information::DestroyInstance()
{
    if (ms_instance)
    {
        delete ms_instance;
        ms_instance = nullptr;
    }
}

bool Information::HasInstance()
{
    return ms_instance != nullptr;
}

void Information::LoadInformation(const char * os, JNIEnv * pEnv)
{
    const char * class_android_os_build_version_str = "android/os/Build$VERSION";
    const char * class_android_os_build_str = "android/os/Build";
    jclass class_android_os_build_version = pEnv->FindClass(class_android_os_build_version_str);
    jclass class_android_os_build = pEnv->FindClass(class_android_os_build_str);
    InitOS(os);
    InitVersion(pEnv, &class_android_os_build_version);
    InitBrand(pEnv, &class_android_os_build);
    InitDevice(pEnv, &class_android_os_build);
    InitHardware(pEnv, &class_android_os_build);
    InitManufacturer(pEnv, &class_android_os_build);
    InitModel(pEnv, &class_android_os_build);
    InitProduct(pEnv, &class_android_os_build);
}

void Information::InitOS(const char * os) {
    LOG_DEBUG("Information", "InitOS(...)");
    if (m_os) return;
    const size_t size = os ? strnlen(os, 255) : 0;
    __SetValueFromString(m_os, os, size);
    LOG_DEBUG("information", "os : \"%s\"", m_os);
}

void Information::InitVersion(JNIEnv * pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitVersion(...)");
    if (m_version) return;
    jfieldID version = pEnv->GetStaticFieldID(*pClass,
            "RELEASE", "Ljava/lang/String;");
    __SetValueFromStaticField(m_version, pEnv, pClass, &version);
    LOG_DEBUG("information", "version : \"%s\"", m_version);
}

void Information::InitBrand(JNIEnv * pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitBrand(...)");
    if (m_brand) return;
    jfieldID brand = pEnv->GetStaticFieldID(*pClass,
            "BRAND", "Ljava/lang/String;");
    __SetValueFromStaticField(m_brand, pEnv, pClass, &brand);
    LOG_DEBUG("information", "brand : \"%s\"", m_brand);
}

void Information::InitDevice(JNIEnv* pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitDevice(...)");
    if (m_device) return;
    jfieldID device = pEnv->GetStaticFieldID(*pClass,
            "DEVICE", "Ljava/lang/String;");
    __SetValueFromStaticField(m_device, pEnv, pClass, &device);
    LOG_DEBUG("information", "device : \"%s\"", m_device);
}

void Information::InitHardware(JNIEnv* pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitHardware(...)");
    if (m_hardware) return;
    jfieldID hardware = pEnv->GetStaticFieldID(*pClass,
            "HARDWARE", "Ljava/lang/String;");
    __SetValueFromStaticField(m_hardware, pEnv, pClass, &hardware);
    LOG_DEBUG("information", "hardware : \"%s\"", m_hardware);
}

void Information::InitManufacturer(JNIEnv* pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitManufacturer(...)");
    if (m_manufacturer) return;
    jfieldID manufacturer = pEnv->GetStaticFieldID(*pClass,
            "MANUFACTURER", "Ljava/lang/String;");
    __SetValueFromStaticField(m_manufacturer, pEnv, pClass, &manufacturer);
    LOG_DEBUG("information", "manufacturer : \"%s\"", m_manufacturer);
}

void Information::InitModel(JNIEnv* pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitModel(...)");
    if (m_model) return;
    jfieldID model = pEnv->GetStaticFieldID(*pClass,
            "MODEL", "Ljava/lang/String;");
    __SetValueFromStaticField(m_model, pEnv, pClass, &model);
    LOG_DEBUG("information", "model : \"%s\"", m_model);
}

void Information::InitProduct(JNIEnv* pEnv, jclass * pClass)
{
    LOG_DEBUG("Information", "InitProduct(...)");
    if (m_product) return;
    jfieldID product = pEnv->GetStaticFieldID(*pClass,
            "PRODUCT", "Ljava/lang/String;");
    __SetValueFromStaticField(m_product, pEnv, pClass, &product);
    LOG_DEBUG("information", "product : \"%s\"", m_product);
}

Information::Information(const char * os, JNIEnv* pEnv) :
    m_os(nullptr),
    m_version(nullptr),
    m_brand(nullptr),
    m_device(nullptr),
    m_hardware(nullptr),
    m_manufacturer(nullptr),
    m_model(nullptr),
    m_product(nullptr)
{
    LOG_DEBUG("Information", "Constructor Information");
    LoadInformation(os, pEnv);
}

Information::~Information()
{
    LOG_DEBUG("Information", "Destructor Information");
    __ResetValue(m_os);
    __ResetValue(m_version);
    __ResetValue(m_brand);
    __ResetValue(m_device);
    __ResetValue(m_hardware);
    __ResetValue(m_manufacturer);
    __ResetValue(m_model);
    __ResetValue(m_product);
}

const char * Information::OS() const
{
    return m_os;
}

const char * Information::Version() const
{
    return m_version;
}

const char * Information::Brand() const
{
    return m_brand;
}

const char * Information::Device() const
{
    return m_device;
}

const char * Information::Hadrdware() const
{
    return m_hardware;
}

const char * Information::Manufacturer() const
{
    return m_manufacturer;
}

const char * Information::Model() const
{
    return m_model;
}

const char * Information::Product() const
{
    return m_product;
}
