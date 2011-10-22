#ifndef NET_CFGH
#define NET_CFGH

#include "../cmn/pugixml.hpp"
#include "../cmn/exception.h"

namespace net
{

void check_cfg(const pugi::xml_node& root) throw(cmn::exception);

}//namespace net

#endif

