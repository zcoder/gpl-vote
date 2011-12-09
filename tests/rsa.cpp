#include "gcrypt/rsa.h"

int main()
{
using namespace gcrypt;
ext::array<char,128> buff;
buff.fill( 0xFF );

rsa::pub<1024> key( buff, 3U );
return 0;
}

