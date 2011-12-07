#include <string.h>

namespace ext
{

c_str::c_str():
    idata(), rawdata(), istring()
{
}

c_str::c_str(const char* str):
    idata(), rawdata( str, strlen( str ) ), istring()
{
}

c_str::operator const char*() const
{
return m_begin;
}

const_c_str::const_c_str():
   idata(), rawdata(), c_str()
{
}

const_c_str::const_c_str(const char* str):
    idata(), rawdata( str, strlen( str ) ), c_str(), const_rawdata()
{
}

} //namespace ext

