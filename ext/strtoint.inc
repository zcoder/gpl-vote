template <class T>
T& strtoint::ToNumeric(T& result) const
{
if ( 0 == m_str.size() )
    {
	return result;
	}

unsigned long i = 1;

const char* begin = m_str.begin();
const char* end = m_str.end();

for (const char* pos = end-1; pos >= begin; --pos, i *= 10)
    {
    if ( '-' != *pos )
        {
        result += (*pos - '0') * i;
        }
    else
        {
        result *= -1;
        }
    }

return result;
}

strtoint::strtoint(const idata& str):
	m_str( str )
{
}

strtoint::operator bool() const
{
bool result = false;
return ToNumeric( result );
}

strtoint::operator int() const
{
int result = 0;
return ToNumeric( result );
}

strtoint::operator char() const
{
char result = 0;
return ToNumeric( result );
}

strtoint::operator short() const
{
short result = 0;
return ToNumeric( result );
}

strtoint::operator long() const
{
long result = 0;
return ToNumeric( result );
}

strtoint::operator unsigned int() const
{
unsigned int result = 0;
return ToNumeric( result );
}

strtoint::operator unsigned char() const
{
unsigned char result = 0;
return ToNumeric( result );
}

strtoint::operator unsigned short() const
{
unsigned short result = 0;
return ToNumeric( result );
}

strtoint::operator unsigned long() const
{
unsigned long result = 0;
return ToNumeric( result );
}

