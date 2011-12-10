#ifndef CRYPT_RSAH
#define CRYPT_RSAH

#include <stddef.h>
#include <stdint.h>
#include <gcrypt.h>

#include <iostream>

#include "ext/array.h"

namespace gcrypt
{
namespace rsa
{

template <size_t keysize>
class pub
{
protected:
gcry_sexp_t m_key;

public:
typedef unsigned int    e_t;

template <class T>
inline      pub(const ext::array<T,keysize/8/sizeof(T)>& n, const e_t& e)
    {
    gcry_mpi_t  mpi_n;
    gcry_error_t err;
    err = gcry_mpi_scan( &mpi_n, GCRYMPI_FMT_USG, &n, keysize/8, NULL );
    if ( 0 != err )
        {
        throw;
        }
    err = gcry_sexp_build( &m_key, NULL, "(public-key(rsa(n%m)(e%d)))", mpi_n, e );
    if ( 0 != err )
        {
        throw;
        }
    gcry_mpi_release( mpi_n );
    }
inline      ~pub()
    {
    gcry_sexp_release( m_key );
    }

inline void dump() const
    {
    size_t size = gcry_sexp_sprint( m_key, GCRYSEXP_FMT_DEFAULT, NULL, 0 );
    char* buff = new char [ size ];
    //gcry_sexp_sprint( m_key, GCRYSEXP_FMT_DEFAULT, buff, size );
    //gcry_sexp_sprint( m_key, GCRYSEXP_FMT_CANON, buff, size );
    gcry_sexp_sprint( m_key, GCRYSEXP_FMT_ADVANCED, buff, size );
    std::cout << buff << std::endl;
    delete[] buff;
    }
};

class priv
{

};

} //namespace rsa
} //namespace crypt

#endif

