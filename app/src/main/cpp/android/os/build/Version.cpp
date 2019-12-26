//
// Created by Ananta Yudica on 26/12/2019.
//

#include "Version.h"

#include "jni.h"
#include <cstring>

#include "../../../Log.h"

android::os::build::Version *
android::os::build::Version::ms_instance = nullptr;

void android::os::build::Version::__SetValueFromString(char * &ref_value,
    const char * cstr, const size_t & size)
{
    ref_value = new char[size + 1];
    strncpy(ref_value, cstr, size);
    ref_value[size] = '\0';
}

void android::os::build::Version::__SetValueFromStaticField(char * &ref_value,
    size_t & ref_size, JNIEnv* pEnv, jclass * pClass, jfieldID * pFieldID)
{
    jstring jstr = (jstring) pEnv->GetStaticObjectField(*pClass, *pFieldID);
    ref_size = pEnv->GetStringUTFLength(jstr);
    const char * cstr = pEnv->GetStringUTFChars(jstr, 0);
    __SetValueFromString(ref_value, cstr, ref_size);
    pEnv->ReleaseStringUTFChars(jstr, cstr);
}

void android::os::build::Version::__ResetValue(char * &ref_value)
{
    if (!ref_value) return;
    delete[] ref_value;
    ref_value = nullptr;
}

void android::os::build::Version::Load(JNIEnv* pEnv)
{
    LOG_DEBUG("android::os::build::Version", "Load(...)");
    if (ms_instance) return;
    ms_instance = new Version(pEnv);
}

void android::os::build::Version::Reset()
{
    LOG_DEBUG("android::os::build::Version", "Reset(...)");
    if (!ms_instance) return;
    delete ms_instance;
    ms_instance = nullptr;
}

const char * android::os::build::Version::Codename()
{
    if (!ms_instance) return nullptr;
    return ms_instance->m_codename;
}

size_t android::os::build::Version::CodenameSize()
{
    if (!ms_instance) return 0;
    return ms_instance->m_codenameSize;
}

const char * android::os::build::Version::Incremental()
{
    if (!ms_instance) return nullptr;
    return ms_instance->m_incremental;
}

size_t android::os::build::Version::IncrementalSize()
{
    if (!ms_instance) return 0;
    return ms_instance->m_incrementalSize;
}

const char * android::os::build::Version::Release()
{
    if (!ms_instance) return nullptr;
    return ms_instance->m_release;
}

size_t android::os::build::Version::ReleaseSize()
{
    if (!ms_instance) return 0;
    return ms_instance->m_releaseSize;
}

int android::os::build::Version::SDK()
{
    if (!ms_instance) return -1;
    return ms_instance->m_sdk;
}

android::os::build::Version::Version(JNIEnv* pEnv) :
    m_env(pEnv),
    m_class(nullptr),
    m_codename(nullptr),
    m_incremental(nullptr),
    m_release(nullptr),
    m_sdk(-1),
    m_codenameSize(0),
    m_incrementalSize(0),
    m_releaseSize(0)
{
    LOG_DEBUG("android::os::build::Version", "Constructor(...)");
    InitClass();
    InitCodename();
    InitIncremental();
    InitRelease();
    InitSDK();
}

android::os::build::Version::~Version()
{
    LOG_DEBUG("android::os::build::Version", "Destructor(...)");
    m_env = nullptr;
    m_class = nullptr;
    __ResetValue(m_codename);
    __ResetValue(m_incremental);
    __ResetValue(m_release);
    m_sdk = -1;
    m_codenameSize = 0;
    m_incrementalSize = 0;
    m_releaseSize = 0;
}

void android::os::build::Version::InitClass()
{
    LOG_DEBUG("android::os::build::Version", "InitClass(...)");
    m_class = m_env->FindClass(ms_class_name_cstr);
    LOG_DEBUG("android::os::build::Version", "class : %p", (void *)m_class);
}

void android::os::build::Version::InitCodename()
{
    LOG_DEBUG("android::os::build::Version", "InitCodename(...)");
    jfieldID codenameFieldID = m_env->GetStaticFieldID(m_class,
            ms_codename_cstr, "Ljava/lang/String;");
    __SetValueFromStaticField(m_codename, m_codenameSize, m_env, &m_class,
            &codenameFieldID);
    LOG_DEBUG("android::os::build::Version", "codename : %s, size : %d",
            m_codename, m_codenameSize);
}

void android::os::build::Version::InitIncremental()
{
    LOG_DEBUG("android::os::build::Version", "InitIncremental(...)");
    jfieldID incrementFieldID = m_env->GetStaticFieldID(m_class,
            ms_incremental_cstr, "Ljava/lang/String;");
    __SetValueFromStaticField(m_incremental, m_incrementalSize, m_env, &m_class,
            &incrementFieldID);
    LOG_DEBUG("android::os::build::Version", "incremental : %s, size : %d",
            m_incremental, m_incrementalSize);
}

void android::os::build::Version::InitRelease()
{
    LOG_DEBUG("android::os::build::Version", "InitRelease(...)");
    jfieldID releaseFieldID = m_env->GetStaticFieldID(m_class,
            ms_release_cstr, "Ljava/lang/String;");
    __SetValueFromStaticField(m_release, m_releaseSize, m_env, &m_class,
            &releaseFieldID);
    LOG_DEBUG("android::os::build::Version", "release : %s, size : %d",
              m_release, m_releaseSize);
}

void android::os::build::Version::InitSDK()
{
    LOG_DEBUG("android::os::build::Version", "InitSDK(...)");
    jfieldID sdkFieldID = m_env->GetStaticFieldID(m_class, ms_sdk_cstr, "I");
    m_sdk = m_env->GetStaticIntField(m_class, sdkFieldID);
    LOG_DEBUG("android::os::build::Version", "sdk : %d", m_sdk);
}
