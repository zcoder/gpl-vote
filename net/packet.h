#ifndef NET_PACKETH
#define NET_PACKETH

#include <stdint.h>
#include <stddef.h>
#include "proto.h"

namespace net
{
namespace packet
{

#pragma pack(push)
#pragma pack(1)
class header
{
const uint16_t  m_proto;
uint16_t        m_size;

public:
inline                  header(const proto::enum_proto p) throw();
inline                  header(const proto::enum_proto p, const size_t size) throw();
inline  const header*   get_header() const throw();
inline  const proto     get_proto() const throw();
inline  const size_t    get_size() const throw();      
};
#pragma(pop)

#pragma pack(push)
#pragma pack(1)
template <class T>
class fixed_size:
    private header,
    public T
{
public:
typedef fixed_size<T>   base;
using header::get_header;
using header::get_proto;
using header::get_size;

inline              fixed_size(const proto::enum_proto p) throw();
inline  T*          get_data() throw();
inline  const T*    get_data() const throw();
};
#pragma pack(pop)

//---- class header methods
header::header(const proto::enum_proto p) throw():
    m_proto( (uint16_t)p )
{
}

header::header(const proto::enum_proto p, const size_t size) throw():
    m_proto( (uint16_t)p ), m_size( size )
{
}

const header* header::get_header() const throw()
{
return this;
}

const proto header::get_proto() const throw()
{
return (proto::enum_proto)m_proto;
}

const size_t header::get_size() const throw()
{
return m_size;
}

//---- class fixed_size methods
template <class T>
fixed_size<T>::fixed_size(proto::enum_proto p) throw():
    header( p, sizeof(header) + sizeof(T) )
{
}

template <class T>
T* fixed_size<T>::get_data() throw()
{
return this;
}

template <class T>
const T* fixed_size<T>::get_data() const throw()
{
return this;
}

}//namespace packet
}//namespace net

#endif

