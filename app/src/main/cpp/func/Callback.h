//
// Created by Ananta Yudica on 13/01/2020.
//

#ifndef ANDROID_SENSOR_SAMPLE_FUNC_CALLBACK_H
#define ANDROID_SENSOR_SAMPLE_FUNC_CALLBACK_H

#include <functional>
#include <cstdint>
#include <utility>
#include <type_traits>

namespace func
{

class Callback
{
protected:
    void * m_ptr;
protected:
    inline Callback(void * ptr);
public:
    inline Callback(const Callback &) = delete;
    inline Callback(Callback &&) = delete;
public:
    virtual inline ~Callback();
public:
    inline Callback & operator=(const Callback &) = delete;
    inline Callback & operator=(Callback &&) = delete;
public:
    template<typename TRet, typename TFun, typename ... TArgs>
    inline typename std::enable_if<std::is_same<TRet, void>::value, void>::type
        Call(TArgs && ... args);
    template<typename TRet, typename TFun, typename ... TArgs>
    inline typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
        Call(TRet def, TArgs && ... args);
public:
    inline operator bool() const;
};

inline Callback::Callback(void * ptr) :
    m_ptr(ptr)
{}

inline Callback::~Callback()
{}

template<typename TRet, typename TFun, typename ... TArgs>
inline typename std::enable_if<std::is_same<TRet, void>::value, void>::type
    Callback::Call(TArgs && ... args)
{
    if (!m_ptr) return;
    auto ptr = static_cast<TFun *>(m_ptr);
    (*ptr)(std::forward<TArgs>(args)...);
}

template<typename TRet, typename TFun, typename ... TArgs>
inline typename std::enable_if<!std::is_same<TRet, void>::value, TRet>::type
    Callback::Call(TRet def, TArgs && ... args)
{
    if (!m_ptr) return def;
    auto ptr = static_cast<TFun *>(m_ptr);
    return (*ptr)(std::forward<TArgs>(args)...);
}

inline Callback::operator bool() const
{
    return m_ptr != NULL;
}

namespace callback
{

template<typename TFun>
class Function : public ::func::Callback
{
public:
    inline Function();
    inline Function(const TFun & fun);
public:
    inline ~Function();
};

template<typename TFun>
inline Function<TFun>::Function() :
    ::func::Callback(nullptr)
{}

template<typename TFun>
inline Function<TFun>::Function(const TFun & fun) :
    ::func::Callback(new TFun(fun))
{}

template<typename TFun>
inline Function<TFun>::~Function()
{
    TFun * ptr = static_cast<TFun *>(m_ptr);
    delete ptr;
    m_ptr = nullptr;
}

} //!callback

} //!func

#endif //ANDROID_SENSOR_SAMPLE_FUNC_CALLBACK_H
