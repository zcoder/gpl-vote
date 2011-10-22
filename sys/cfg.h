#ifndef SYS_CFGH
#define SYS_CFGH

#include "../cmn/pugixml.hpp"
#include "../cmn/exception.h"

namespace sys
{

void check_cfg(const pugi::xml_node& root) throw(cmn::exception);

}//namespace sys

#endif

