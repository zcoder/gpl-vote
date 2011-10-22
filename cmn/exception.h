#ifndef CMN_EXCEPTIONH
#define CMN_EXCEPTIONH

#include <exception>

namespace cmn //common
{

class exception:
    public std::exception
{
protected:
const char* m_msg;

public:
inline              exception(const char* msg) throw();
inline  const char* what() const throw();
};

exception::exception(const char* msg) throw():
    m_msg( msg )
{
}

const char* exception::what() const throw()
{
return m_msg;
}

}//namespace cmn

#endif

