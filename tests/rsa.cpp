#include "gcrypt/rsa.h"

int main()
{
/* Version check should be the very first call because it
 * makes sure that important subsystems are intialized. */
if (!gcry_check_version (GCRYPT_VERSION))
    {
    std::cerr << "libgcrypt version mismatch" << std::endl;
    exit (2);
    }
/* Disable secure memory. */
gcry_control (GCRYCTL_DISABLE_SECMEM, 0);
/* ... If required, other initialization goes here.
 * Tell Libgcrypt that initialization has completed. */
gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

using namespace gcrypt;
ext::array<char,128> buff;
buff.fill( 0xFF );

rsa::pub<1024> key( buff, 3U );
key.dump();
return 0;
}

