#ifndef EXT_IDATAH
#define EXT_IDATAH

#include <stddef.h>

namespace ext
{

class idata
{
public:
typedef const char*     const_iterator;
inline  virtual         ~idata();
inline  virtual bool    operator  < (const idata& rvalue) const;
inline  virtual bool    operator  > (const idata& rvalue) const;
inline  virtual bool    operator == (const idata& rvalue) const;
inline  virtual bool    operator != (const idata& rvalue) const;
virtual const_iterator  begin() const = 0;
virtual const_iterator  end() const = 0;
virtual size_t          size() const = 0;
};

} //namespace ext

#include "idata.inc"

#endif

