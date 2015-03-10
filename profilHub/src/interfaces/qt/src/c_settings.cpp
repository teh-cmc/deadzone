#include <c_settings>


c_settings c_settings::m_instance = c_settings();

c_settings::c_settings()
{
}

c_settings::~c_settings
{
}

c_settings&
c_settings::f_getinstance(void)
{
    return m_instance;
}

