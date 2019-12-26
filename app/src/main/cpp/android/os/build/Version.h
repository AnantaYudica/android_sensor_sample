//
// Created by Ananta Yudica on 26/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_ANDROID_BUILD_OS_VERSION_H
#define ANDROID_SENSOR_SAMPLE_ANDROID_BUILD_OS_VERSION_H

#include "jni.h"

namespace android
{
namespace os
{
namespace build
{

class Version
{
private:
    static constexpr const char * ms_class_name_cstr = "android/os/Build$VERSION";
    static constexpr const char * ms_codename_cstr = "CODENAME";
    static constexpr const char * ms_incremental_cstr = "INCREMENTAL";
    static constexpr const char * ms_release_cstr = "RELEASE";
    static constexpr const char * ms_sdk_cstr = "SDK_INT";
private:
    static Version * ms_instance;
private:
    static void __SetValueFromString(char * &ref_value, const char * cstr,
        const size_t & size);
    static void __SetValueFromStaticField(char * &ref_value, size_t & ref_size,
        JNIEnv* pEnv, jclass * pClass, jfieldID * pFieldID);
    static void __ResetValue(char * &ref_value);
public:
    static void Load(JNIEnv* pEnv);
    static void Reset();
public:
    static const char * Codename();
    static size_t CodenameSize();
    static const char * Incremental();
    static size_t IncrementalSize();
    static const char * Release();
    static size_t ReleaseSize();
    static int SDK();
private:
    JNIEnv* m_env;
    jclass m_class;
    char * m_codename;
    char * m_incremental;
    char * m_release;
    int m_sdk;
    size_t m_codenameSize,
        m_incrementalSize,
        m_releaseSize;
private:
    Version(JNIEnv* pEnv);
public:
    Version(const Version &) = delete;
    Version(Version &&) = delete;
public:
    ~Version();
public:
    void InitClass();
    void InitCodename();
    void InitIncremental();
    void InitRelease();
    void InitSDK();
};

} //!build

} //!os

} //!android



#endif //ANDROID_SENSOR_SAMPLE_ANDROID_BUILD_OS_VERSION_H
