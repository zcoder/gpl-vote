#ifndef EXT_ISTRINGH
#define EXT_ISTRINGH

#include "idata.h"
#include "strtoint.h"

namespace ext
{

class istring:
    virtual public idata
{
public:
virtual inline  strtoint    ToInt() const;
};

} //namespace ext

#include "istring.inc"

#endif

