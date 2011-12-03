#ifndef EXT_RAWDATAH
#define EXT_RAWDATAH

#include "idata.h"

namespace ext
{

class rawdata:
    virtual public idata
{
public:
typedef     idata::const_iterator const_iterator;

protected:
char*       m_begin;
size_t      m_size;

inline      rawdata();

public:
inline      rawdata(const char* begin, size_t size);

inline      const char* begin() const;
inline      const char* end() const;
inline      size_t      size() const;

inline      bool        operator <  (const rawdata& rvalue) const;
inline      bool        operator >  (const rawdata& rvalue) const;
inline      bool        operator == (const rawdata& rvalue) const;
inline      bool        operator != (const rawdata& rvalue) const;
};

class const_rawdata:
    virtual public rawdata
{
public:
typedef     rawdata::const_iterator const_iterator;

protected:
inline  const_rawdata();

public:
using   rawdata::operator <;
using   rawdata::operator >;
using   rawdata::operator ==;
using   rawdata::operator !=;
using   rawdata::begin;
using   rawdata::end;
using   rawdata::size;

inline  const_rawdata(const char* begin, size_t size);
};

} //namespace ext

#include "rawdata.inc"

#endif

