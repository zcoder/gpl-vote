#include <string.h>

namespace ext
{

IData::~IData()
{
}

bool IData::operator  < (const IData& rvalue) const
{
if ( begin() == rvalue.begin() )
    {
    return false;
    }
if ( size() < rvalue.size() )
    {
    return true;
    }
if ( rvalue.size() < size() )
    {
    return false;
    }
return 0 < memcmp( begin(), rvalue.begin(), size() );
}

bool IData::operator  > (const IData& rvalue) const
{
return rvalue < *this;
}

bool IData::operator == (const IData& rvalue) const
{
return !(*this < rvalue) && !(rvalue < *this);
}

bool IData::operator != (const IData& rvalue) const
{
return !operator == ( rvalue );
}

} //namespace ext

