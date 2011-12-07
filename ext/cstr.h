#ifndef EXT_CSTRH
#define EXT_CSTRH

#include "istring.h"
#include "rawdata.h"

namespace ext
{

class c_str:
    virtual public rawdata,
    public istring
{
public:
typedef rawdata::const_iterator const_iterator;

protected:
inline  c_str();

public:
using   rawdata::begin;
using   rawdata::end;
using   rawdata::size;

inline  c_str(const char* str);
inline  operator const char*() const;
};



class const_c_str:
    public c_str,
    public const_rawdata
{
public:
typedef c_str::const_iterator const_iterator;

protected:
inline  const_c_str();

public:
using   c_str::operator const char*;
using   c_str::begin;
using   c_str::end;
using   c_str::size;

inline  const_c_str(const char* str);
};

} //namespace ext

#include "cstr.inc"

#endif

