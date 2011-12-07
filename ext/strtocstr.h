#ifndef EXT_STRTOCSTRH
#define EXT_STRTOCSTRH

#include "idata.h"

class strtocstr
{
private:
char*   m_buff;

public:
inline  strtocstr(const IData& data);
inline  ~strtocstr();
inline  operator const char* () const;
};

strtocstr::strtocstr(const IData& data)
{
register size_t size = data.size();
if ( 0 < size )
    {
    m_buff = new char [ size+1 ];
    if ( NULL == m_buff )
        {
        abort();
        }
    memcpy( m_buff, data.begin(), size );
    m_buff[ size ] = '\0';
    }
else
    {
    m_buff = NULL;
    }
}

strtocstr::~strtocstr()
{
if ( NULL != m_buff )
    {
    delete []m_buff;
    }
}

strtocstr::operator const char* () const
{
return m_buff;
}

#endif

