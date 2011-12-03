#include <stddef.h>

namespace ext
{

rawdata::rawdata():
    idata()
{
m_begin = NULL;
m_size = 0;
}

rawdata::rawdata(const char* begin, size_t size):
    idata()
{
m_begin = (char*)begin;
m_size = size;
}

const char* rawdata::begin() const
{
return m_begin;
}

const char* rawdata::end() const
{
return m_begin + m_size;
}

size_t rawdata::size() const
{
return m_size;
}

bool rawdata::operator  < (const rawdata& rvalue) const
{
if ( m_begin == rvalue.m_begin )
    {
    return false;
    }
if ( m_size < rvalue.m_size )
    {
    return true;
    }
if ( rvalue.m_size < m_size )
    {
    return false;
    }
return 0 < memcmp( m_begin, rvalue.m_begin, m_size );
}

bool rawdata::operator  > (const rawdata& rvalue) const
{
return rvalue < *this;
}

bool rawdata::operator == (const rawdata& rvalue) const
{
register bool size = (rvalue.m_size == m_size);
register bool pointer = (rvalue.m_begin == m_begin);
return size && (pointer || !memcmp( rvalue.m_begin, m_begin, m_size ) );
}

bool rawdata::operator != (const rawdata& rvalue) const
{
return !operator == ( rvalue );
}

const_rawdata::const_rawdata():
    idata(), rawdata()
{
}

const_rawdata::const_rawdata(const char* begin, size_t size):
    idata(), rawdata( begin, size )
{
}

} //namespace ext

