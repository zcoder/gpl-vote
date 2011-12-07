#ifndef EXT_DATAH
#define EXT_DATAH

#include "idata.h"
#include "link.h"
#include "rawdata.h"

class data:
    public rawdata,
    public link
{
protected:
using rawdata::m_begin;
using rawdata::m_size;

char*           m_buff;
char*           m_end;
size_t          m_capacity;

inline  void    Init();
inline  void    FreeNoInit();

public:
using rawdata::operator <;
using rawdata::operator >;
using rawdata::operator ==;
using rawdata::operator !=;
using rawdata::begin;
using rawdata::size;

inline                  data();
inline                  data(const idata& origin);
inline                  data(const const_rawdata& origin);
inline                  data(const data& origin);
inline                  ~data();

inline  size_t          alloc(size_t size);
inline  size_t          realloc(size_t size);
inline  void            clear();
inline  void            free();

inline  size_t          truncate(ssize_t size);
inline  data&           swap(const data& data);

inline  const char*     end() const;
inline  size_t          capacity() const;

inline  data&          operator  = (const idata& rvalue);
inline  data&          operator  = (const const_rawdata& rvalue);
inline  data&          operator  = (const data& rvalue);

inline  data&          operator += (const idata& rvalue);
inline  data&          operator += (const const_rawdata& rvalue);
inline  data&          operator += (const data& rvalue);

inline  data           operator +  (const idata& rvalue) const;
inline  data           operator +  (const const_rawdata& rvalue) const;
inline  data           operator +  (const data& rvalue) const;

inline  data&          operator <<(istream& i);

inline  data           SubData(ssize_t offset, ssize_t size) const;
};

#include "data.inc"

#endif


