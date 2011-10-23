#ifndef NET_PROTO_SYSTEM_0H
#define NET_PROTO_SYSTEM_0H

namespace net
{
namespace system_0
{

const cmn::UUID magic_number();

struct cmd
{
enum enum_cmd
    {
    request_magic,
    responce_magic
    };
};

#pragma pack(push)
#pragma pack(1)
class header:
    public net::packet::header
{
protected:
typedef net::packet::header base;
uint16_t    m_cmd;

public:
using base::get_proto;
using base::get_size;

inline                  header(const cmd c) throw();
inline                  header(const cmd c, const size_t size) throw();
inline const header*    get_header() const throw();
inline const cmd        get_cmd() const throw();
};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
template <class T>
class fixed_size:
    private header,
    public T
{
public:
using header::get_header;
using header::get_proto;
using header::get_size;
using header::get_cmd;

inline                  fixed_size(const cmd c) throw();
inline                  fixed_size(const cmd c, const T& origin) throw();
inline  const void*     get_data() const throw();
inline  const void*     get_all() const throw();
};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
class request_magic:
    public fixed_size<cmn::UUID>
{
public:
        reques_magic() throw();
bool    check() const throw();
};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
class responce_magic:
    public fixed_size<cmn::UUID>
{
public:
        responce_magic() throw();
bool    check() const throw();
};
#pragma pack(pop)

//---- class header
header::header(const cmd c) throw():
    header( net::proto::system_0 ), m_cmd( (uint16_t)c )
{
}

header::header(const cmd c, const size_t size) throw():
    header( net::proto::system_0, size ), m_cmd( (uint16_t)c )
{
}

const header* header::get_header() const throw()
{
return this;
}

const cmd header::get_cmd() const throw()
{
return cmd( (cmd::enum_cmd)m_cmd );
}

//---- class fixed_size
template <class T>
fixed_size::fixed_size(const cmd c):
    header( c, sizeof(header) + sizeof(T) )
{
}

template <class T>
fixed_size::fixed_size(const cmd c, const T& origin):
    header( c, sizeof(header) + sizeof(T) ), T( origin )
{
}

template <class T>
const void* fixed_size::get_data() const throw()
{
const T* data = this;
return this;
}

template <class T>
const void* fixed_sizeLLget_all() const throw()
{
return this;
}

//---- class request_magic
request_magic::reques_magic() throw():
    base( cmd::reques_magic, magic_number )
{
}

bool request_magic::check() throw()
{
return T::operator == ( magic_number );
}

//---- class responce_magic
responce_magic::responce_magic() throw():
    base( cmd::responce_magic, magic_number )
{
}

bool responce_magic::check() throw()
{
return T::operator == ( magic_number );
}

}//namespace system_0
}//namespace net

#endif

