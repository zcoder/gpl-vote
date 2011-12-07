#ifndef EXT_STRINGH
#define EXT_STRINGH

#include "cstr.h"
#include "istring.h"
#include "data.h"
#include "cstrtocstr.h"

namespace ext
{

class string:
    public istring,
    public data
{
private:
static  char        m_null;

protected:
using data::m_begin;
using data::m_end;
using data::m_size;
using data::realloc;
using data::SubData;

inline              string(const data& origin);

public:
inline              string();
inline              string(const idata& origin);
inline              string(const const_c_str& origin);
inline              string(const string& origin);
inline              ~string();

//idata
using data::begin;
using data::end;
using data::size;
using data::clear;
//data
using data::operator <;
using data::operator ==;

//overload basic oerators
inline  string&     operator  = (const idata& rvalue);
inline  string&     operator  = (const const_rawdata& rvalue);
inline  string&     operator  = (const data& rvalue);

inline  string&     operator += (const idata& rvalue);
inline  string&     operator += (const const_rawdata& rvalue);
inline  string&     operator += (const data& rvalue);

inline  string      operator +  (const idata& rvalue) const;
inline  string      operator +  (const const_rawdata& rvalue) const;
inline  string      operator +  (const data& rvalue) const;
inline  string      operator +  (const char sym) const;

inline  const char& operator [] (size_t offset) const;
inline  string&     operator += (const char sym);

inline  strtocstr   c_str() const;

inline  ssize_t     Find(const char sym, ssize_t offset) const;
inline  ssize_t     FindBack(const char sym, ssize_t offset) const;
inline  ssize_t     Find(const string& substr, ssize_t offset) const;
inline  ssize_t     FindBack(const string& substr, ssize_t offset) const;

inline  int         strcmp(ssize_t offset, const istring& str) const;
inline  int         strcmp(const istring& str) const;

inline  string      SubStr(ssize_t offset, ssize_t size) const;
inline const idata& SafeCopy() const;

inline  string&    operator << (istream& in);

//istring
inline  string&    Printf(const const_c_str& fmt, ...);
//inline  CStrToInt 	ToInt() const;
template <class T>
inline  static string  FromInt(const T value);
};

} //namespace ext

#endif

