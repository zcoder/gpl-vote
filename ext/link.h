#ifndef EXT_LINKH
#define EXT_LINKH

namespace ext
{

class link
{
protected:
mutable int*    m_links;

inline  void    Init();
inline  void    Link() const;
inline  void    UnLink();

public:
inline          link();
inline          link(const link& origin);
inline          ~link();
inline  link&   operator = (const link& rvalue);

inline  bool    IsLinked() const;
};

} //namespace ext

#include "link.inc"

#endif

