//
// Created by Ananta Yudica on 04/01/2020.
//

#include "Sensor.h"

namespace bridge
{

constexpr char Sensor::ms_format_method_signature[];

constexpr size_t Sensor::ms_format_method_signature_size;

Sensor::Sensor() :
    m_linked(false),
    m_env(nullptr),
    m_class(nullptr),
    m_object(nullptr),
    m_callMethodid(nullptr)
{}

Sensor::~Sensor()
{
    if (m_linked) Clean();
    m_linked = false;
}

Sensor::Sensor(const Sensor & cpy) :
    m_linked(cpy.m_linked),
    m_env(cpy.m_env),
    m_class(cpy.m_class),
    m_object(cpy.m_object),
    m_callMethodid(cpy.m_callMethodid)
{}

Sensor::Sensor(Sensor && mov) :
    m_linked(mov.m_linked),
    m_env(mov.m_env),
    m_class(mov.m_class),
    m_object(mov.m_object),
    m_callMethodid(mov.m_callMethodid)
{
    mov.m_linked = false;
    mov.m_env = nullptr;
    mov.m_class = nullptr;
    mov.m_object = nullptr;
    mov.m_callMethodid = nullptr;
}

void Sensor::Init()
{
    m_env = new JNIEnv;
    m_class = new jclass;
    m_object = new jobject;
    m_callMethodid = new jmethodID;
}

void Sensor::Clean()
{
    if (m_env) delete m_env;
    m_env = nullptr;
    if (m_class) delete m_class;
    m_class = nullptr;
    if (m_object) delete m_object;
    m_object = nullptr;
    if (m_callMethodid) delete m_callMethodid;
    m_callMethodid = nullptr;
}

const char * Sensor::MethodSignature(char *& buf, const size_t & size, const char * param_sig)
{
    std::snprintf(buf, size, ms_format_method_signature, param_sig);
    return buf;
}

int Sensor::Link(JNIEnv* p_env, jobject p_this, const char * link_method_name)
{
    if (IsLink()) return 0;
    if (!p_env) return -2;
    if (!p_this) return -3;
    Init();
    m_env = p_env;
    *m_object = p_this;
    *m_class = p_env->GetObjectClass(p_this);
    if (!*m_class)
    {
        Clean();
        return -4;
    }
    auto param_sig_pair = ParameterSignature();
    const size_t method_sig_size = ms_format_method_signature_size + param_sig_pair.second + 1;
    char * method_sig = new char[method_sig_size];
    *m_callMethodid = p_env->GetMethodID(*m_class, link_method_name,
            MethodSignature(method_sig, method_sig_size, param_sig_pair.first));
    delete[] method_sig;
    if (!*m_callMethodid)
    {
        Clean();
        return -5;
    }
    m_linked = true;
    return 1;
}

bool Sensor::IsLink() const
{
    return m_linked;
}

}
