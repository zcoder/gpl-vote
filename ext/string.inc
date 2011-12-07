#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

namespace ext
{

extern  const const_c_str STR_FORMAT_ZD;

string::string():
    idata(), istring(), data()
{
}

string::string(const idata& origin):
    idata(), istring(), data( origin )
{
}

string::string(const const_c_str& origin):
    idata(), istring(), data( origin )
{
}

string::string(const data& origin):
    idata(), istring(), data( origin )
{
}

string::string(const string& origin):
    idata(), istring(), data( origin )
{
}

string::~string()
{
}

string& string::Printf(const const_c_str& fmt, ...)
{
va_list list;
va_start( list, fmt );
char* buff;
int size = vasprintf( &buff, fmt, list );
va_end( list );
if ( size > 0 )
    {
    operator +=( rawdata( buff, size ) );
    ::free( buff );
    }
return *this;
}
 
const char& string::operator[] (size_t offset) const
{
if ( NULL != m_begin && offset < m_size )
    {
    return m_begin[ offset ];
    }
else
    return m_null;
}

//XML Object
void string::SetDefault()
{
clear();
}

bool string::IsSet() const
{
return m_size > 0;
}

bool string::SubSetOf(const string& origin) const
{
return !IsSet() || operator == ( origin );
}

TXML string::ToXML(const TString& name) const
{
return TXML( name, *this );
}

int string::ToXMLSTR(TString& xmlstr) const
{
xmlstr += *this;
return 0;
}

int string::FromXML(const const_TXMLP& xml)
{
if ( xml.end() != xml )
    {
    return FromXML( *xml );
    }
return -1;
}

int string::FromXML(const TXML& xml)
{
operator = ( xml.Value() );
return 0;
}

int string::FromXMLSTR(const TString& xmlstr)
{
operator = ( xmlstr );
return 0;
}

ssize_t string::Find(const char sym, ssize_t offset) const
{
if ( 0 == m_size )
    {
    return -1;
    }
if ( offset < 0 )
    {
    offset += m_size;
    }
assert( (size_t)offset < m_size );
register char symcmp = sym;
register int bigcmp = (m_size - offset) / sizeof(size_t);
register char* pos = m_begin + offset;
for (; bigcmp > 0; --bigcmp, pos += sizeof(size_t) )
    {
    register long data = *((size_t*)pos);
    for (register unsigned int roll = 0; roll < sizeof(size_t); ++roll)
        {
        if ( (data & 0xFF) == symcmp )
            {
            return (pos - m_begin) + roll;
            }
        data >>= 8;
        }
    }
register int smallcmp = (m_size - offset) % sizeof(size_t);
for (; smallcmp >= 0; --smallcmp, ++pos)
    {
    if ( symcmp == *pos )
        {
        return pos - m_begin;
        }
    }
return -1;
}

ssize_t string::FindBack(const char sym, ssize_t offset) const
{
//TODO: fastcmp logic
if ( 0 == m_size )
    {
    return -1;
    }
if ( offset < 0 )
    {
    offset += m_size;
    }
assert( (size_t)offset < m_size );
register char* begin = m_begin;
register char symcmp = sym;
for (register char* pos = begin + offset; pos >= begin; --pos)
    {
    if ( symcmp == *pos )
        {
        return pos - begin;
        }
    }
return -1;
}

ssize_t string::Find(const string& substr, ssize_t offset) const
{
//TODO: fastcmp logic
if ( 0 == m_size )
    {
    return -1;
    }
if ( offset < 0 )
    {
    offset += m_size;
    }
assert ( (substr.m_size + (size_t)offset) <= m_size );
register size_t lencmp = substr.m_size;
register char* begin = m_begin + offset;
register char* end = m_end - lencmp;
register char* datacmp = substr.m_begin;
for (register char* pos = begin; pos <= end; ++pos)
    {
    if ( !memcmp( pos, datacmp, lencmp ) )
        {
        return pos - m_begin;
        }
    }
return -1;
}

//ssize_t string::FindBack(const string& substr, size_t offset) const;

string& string::operator  = (const idata& rvalue)
{
data::operator = ( rvalue );
return *this;
}

string& string::operator  = (const const_rawdata& rvalue)
{
data::operator = ( rvalue );
return *this;
}

string& string::operator  = (const data& rvalue)
{
data::operator = ( rvalue );
return *this;
}

string& string::operator += (const idata& rvalue)
{
data::operator += ( rvalue );
return *this;
}

string& string::operator += (const const_rawdata& rvalue)
{
data::operator += ( rvalue );
return *this;
}

string& string::operator += (const data& rvalue)
{
data::operator += ( rvalue );
return *this;
}

string& string::operator += (const char sym)
{
realloc( m_size + 1 );
*m_end = sym;
++m_end;
++m_size;
return *this;
}

string string::operator +  (const idata& rvalue) const
{
return string( data::operator + ( rvalue ) );
}

string string::operator +  (const const_rawdata& rvalue) const
{
return string( data::operator + ( rvalue ) );
}

string string::operator +  (const data& rvalue) const
{
return string( data::operator + ( rvalue ) );
}

string string::operator +  (const char sym) const
{
return string( *this ) += sym;
}

cstrtocstr string::c_str() const
{
return cstrtocstr( *this );
}

int string::strcmp(ssize_t offset, const istring& str) const
{
assert( str.size() <= m_size );
return memcmp( m_begin + offset, str.begin(), str.size() );
}

int string::strcmp(const istring& str) const
{
return strcmp( 0, str );
}

string string::SubStr(ssize_t offset, ssize_t size) const
{
return SubData( offset, size );
}

const idata& string::SafeCopy() const
{
return *this;
}

string& string::operator << (istream& /*in*/)
{
abort();
return *this;
}

template <class T>
string string::FromInt(const T value)
{
string result;
result.Printf( STR_FORMAT_ZD, value );
return result;
}

} //namespace ext

