#ifndef EXT_STRTOINTH
#define EXT_STRTOINTH

#include "idata.h"

class strtoint
{
protected:
const idata&        m_str;

template <class T>
inline  T&          ToNumeric(T& result) const;

public:
inline				strtoint(const idata& str);
inline              operator bool() const;
inline              operator int() const;
inline              operator char() const;
inline              operator short() const;
inline              operator long() const;
inline              operator unsigned int() const;
inline              operator unsigned char() const;
inline              operator unsigned short() const;
inline              operator unsigned long() const;
};

#include "cstrtoint.inc"

#endif

