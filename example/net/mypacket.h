#ifndef EXAMPLE_NET_MYPACKETH
#define EXAMPLE_NET_MYPACKETH

#include "../../net/packet.h"

namespace example
{
namespace net
{
namespace packet
{

typedef char TSecret[256];

#pragma pack(push)
#pragma pack(1)
struct mydata
{
uint32_t    m_id;
time_t      m_timestamp;
uint32_t    m_from;
uint32_t    m_to;
TSecret     m_secret;
};
#pragma(pop)

//fixed_size
#pragma pack(push)
#pragma pack(1)
struct fixed_packet:
    public ::net::packet::fixed_size<mydata>
{
inline fixed_packet(): base( ::net::proto::vote_0 ) {}
};
#pragma pack(pop)

}//namespace packet
}//namespace net
}//namespace example

#endif
