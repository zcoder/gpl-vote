#ifndef CRYPT_RSAH
#define CRYPT_RSAH

#include <stddef.h>
#include <stdint.h>
#include <gcrypt.h>

#include "ext/array.h"

namespace gcrypt
{
namespace rsa
{

template <size_t size>
class pub
{
protected:
gcry_sexp_t m_key;

public:
typedef unsigned int    e_t;

template <class T>
inline      pub(const ext::array<T,size/8/sizeof(T)>& n, const e_t& e)
    {
    gcry_mpi_t  mpi_n;
    int err = gcry_mpi_scan( &mpi_n, GCRYMPI_FMT_USG, &n, size/8, NULL );
    //int err = gcry_sexp_build( &m_key, NULL, "(public-key(rsa(n%M)(e%u)))", mpi_n, e );
    gcry_mpi_release( mpi_n );
    }
inline      ~pub()
    {
    gcry_sexp_release( m_key );
    }
};

class priv
{

};

} //namespace rsa
} //namespace crypt

#endif

