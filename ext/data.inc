#include <stdlib.h>

#define CDATAPAGESIZE (64)

namespace ext
{

data::data():
    idata(), rawdata(), link()
{
m_buff = NULL;
m_end = NULL;
m_capacity = 0;
}

data::data(const data& origin):
    idata(), rawdata( origin ), link( origin )
{
m_buff = origin.m_buff;
m_end = origin.m_end;
m_capacity = origin.m_capacity;
}

data::data(const idata& origin):
    idata(), rawdata(), link()
{
m_buff = NULL;
m_capacity = 0;
size_t l_size = origin.size();
if ( 0 == l_size )
    {
    return;
    }
const char* l_begin = origin.begin();
size_t ret = alloc( l_size );
if ( ret < l_size )
    {
    abort();
    }
register char* l_buff = m_begin;
memcpy( l_buff, l_begin, l_size );
m_end = l_buff + l_size;
m_size = l_size;
}

data::data(const const_rawdata& origin):
    idata(), rawdata( origin ), link()
{
m_buff = NULL;
m_capacity = 0;
m_size = origin.size();
m_end = m_begin + m_size;
}

data::~data()
{
FreeNoInit();
#ifdef DEBUG
    Init();
#endif
}

void data::Init()
{
m_buff  = NULL;
m_begin = NULL;
m_end   = NULL;
m_size = 0;
m_capacity = 0;
}

size_t data::alloc(size_t l_size)
{
register size_t l_newsize = (l_size / CDATAPAGESIZE + (0 != (l_size % CDATAPAGESIZE))) * CDATAPAGESIZE;
if ( (l_newsize <= m_capacity) && (NULL != m_buff) && !IsLinked() )
    {
    return m_capacity;
    }
FreeNoInit();
link::Init();
register char* l_buff = (char*)malloc( l_newsize );
l_newsize = (NULL != l_buff)? l_newsize : 0;
m_buff = l_buff;
m_begin = l_buff;
m_end = l_buff;
m_capacity = l_newsize;
m_size = 0;
return l_newsize;
}

size_t data::realloc(size_t l_size)
{
register ssize_t l_available = m_capacity - (m_begin - m_buff);
register bool islinked = IsLinked();
if ( ((ssize_t)l_size <= l_available) && (NULL != m_buff) && !islinked )
    {
    return m_capacity;
    }
if ( l_size <= m_capacity && (NULL != m_buff) && !islinked )
    {
    register char* l_buff = m_buff;
    memmove( l_buff, m_begin, m_size );
    m_begin = l_buff;
    m_end = l_buff + m_size;
    return m_capacity;
    }
register size_t l_newsize = (l_size / CDATAPAGESIZE + (0 != (l_size % CDATAPAGESIZE))) * CDATAPAGESIZE;
if ( (m_begin == m_buff) && !islinked )
    {
    register char* l_buff = (char*)::realloc( m_buff, l_newsize );
    if ( l_buff != m_begin )
        {
        m_buff = l_buff;
        m_begin = l_buff;
        m_end = l_buff + m_size;
        }
    link::Init();
    m_capacity = l_newsize;
    return l_newsize;
    }
register const char* l_begin = m_begin;
register char* l_buff = (char*)malloc( l_newsize );
register size_t l_oldsize = m_size;
if ( NULL == l_buff )
    {
    return 0;
    }
memcpy( l_buff, l_begin, l_oldsize );
FreeNoInit();
link::Init();
m_buff = l_buff;
m_begin = l_buff;
m_end = l_buff + l_oldsize;
m_size = l_oldsize;
m_capacity = l_newsize;
return l_newsize;
}

void data::clear()
{
if ( IsLinked() )
    {
    free();
    }
else
    {
    register char* l_buff = m_buff;
    m_begin = l_buff;
    m_end = l_buff;
    m_size = 0;
    }
}

void data::FreeNoInit()
{
if ( !IsLinked() && ( NULL != m_buff ) )
    {
    ::free( (void*)m_buff );
    }
else
    {
    UnLink();
    }
}

void data::free()
{
FreeNoInit();
Init();
}

const char* data::end() const
{
return m_end;
}

size_t data::capacity() const
{
return m_capacity;
}

data& data::operator  = (const idata& rvalue)
{
register size_t l_size = rvalue.size();
if ( 0 == l_size )
    {
    return *this;
    }
size_t ret = alloc( l_size );
if ( ret < l_size )
    {
    abort();
    }
register char* l_buff = m_begin;
memcpy( l_buff, rvalue.begin(), l_size );
m_end = l_buff + l_size;
m_size = l_size;
return *this;
}

data& data::operator  = (const data& rvalue)
{
if ( this == &rvalue )
    {
    return *this;
    }
FreeNoInit();
link::operator = ( rvalue );
m_buff = rvalue.m_buff;
m_begin = rvalue.m_begin;
m_end = rvalue.m_end;
m_size = rvalue.m_size;
m_capacity = rvalue.m_capacity;
return *this;
}

data& data::operator  = (const const_rawdata& rvalue)
{
FreeNoInit();
m_buff = NULL;
m_begin = (char*)rvalue.begin();
m_end = (char*)rvalue.end();
m_size = rvalue.size();
m_capacity = 0;
return *this;
}

data& data::operator += (const idata& rvalue)
{
register size_t l_size = rvalue.size();
if ( 0 == l_size )
    {
    return *this;
    }
register size_t newsize = m_size + l_size;
size_t ret = realloc( newsize );
if ( ret < newsize )
    {
    abort();
    }
memcpy( m_end, rvalue.begin(), l_size );
m_end += l_size;
m_size += l_size;
return *this;
}

data& data::operator += (const const_rawdata& rvalue)
{
if ( NULL == m_begin )
    {
    return operator = ( rvalue );
    }
else
    {
    return operator += ( (const idata&)rvalue );
    }
}

data& data::operator += (const data& rvalue)
{
if ( NULL == m_begin )
    {
    return operator = ( rvalue );
    }
else
    {
    return operator += ( (const idata&)rvalue );
    }
}

data data::operator +  (const idata& rvalue) const
{
data result;
register size_t l_size = m_size + rvalue.size();
if ( 0 == l_size )
    {
    return result;
    }
size_t ret = result.alloc( l_size );
if ( ret < l_size )
    {
    abort();
    }
memcpy( result.m_begin, m_begin, m_size );
memcpy( result.m_begin + m_size, rvalue.begin(), rvalue.size() );
result.m_size = l_size;
return result;
}

data data::operator +  (const const_rawdata& rvalue) const
{
if ( NULL == m_begin )
    {
    return data( rvalue );
    }
else
    {
    return operator + ( (const idata&)rvalue );
    }
}

data data::operator +  (const data& rvalue) const
{
if ( NULL == m_begin )
    {
    return data( rvalue );
    }
else
    {
    return operator + ( (const idata&)rvalue );
    }
}

data data::SubData(ssize_t l_offset, ssize_t l_size) const
{
if ( 0 > l_offset )
    {
    l_offset += m_size;
    }
if ( 0 > l_size )
    {
    l_size += m_size - l_offset + 1;
    }
assert( ((size_t)l_offset + (size_t)l_size) <= m_size );
data result( *this );
result.m_size = l_size;
result.m_begin = m_begin + l_offset;
result.m_end = result.m_begin + l_size;
return result;
}

} //namespace ext

