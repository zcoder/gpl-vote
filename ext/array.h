#ifndef EXT_ARRAYH
#define EXT_ARRAYH

#include <stddef.h>
#include <iterator>

template <class T,size_t n>
struct array
{
typedef T                                           type;
typedef type*                                       pointer;
typedef const type*                                 const_pointer;
typedef type&                                       reference;
typedef const type&                                 const_reference;
typedef pointer                                     iterator;
typedef const_pointer                               const_iterator;
typedef std::reverse_iterator<iterator>             reverse_iterator;
typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

T   m_data[n];

reference               operator [] (size_t index)
{
return m_data[ index ];
}

const_reference         operator [] (size_t index) const
{
return m_data[ index ];
}

iterator                begin()
{
return m_data;
}

const_iterator          begin() const
{
return m_data;
}

iterator                end()
{
return m_data + n;
}

const_iterator          end() const
{
return m_data + n;
}

reverse_iterator        rbegin()
{
return reverse_iterator( end() );
}

const_reverse_iterator  rbegin() const
{
return const_reverse_iterator( end() );
}

reverse_iterator        rend()
{
return reverse_iterator( begin() );
}

const_reverse_iterator  rend()  const
{
return const_reverse_iterator( begin() );
}

void                    fill(const_reference value)
{
for (iterator it = begin(); it != end(); ++it)
    {
    *it = value;
    }
}

bool operator == (const array& rvalue) const
{
const_iterator l_it = begin();
const_iterator l_end = end();
const_iterator r_it = rvalue.begin();
for (; l_it != l_end; ++l_it, ++r_it)
    {
    if ( *l_it != *r_it )
        {
        return false;
        }
    }
return false;
}

bool operator < (const array& rvalue) const
{
const_iterator l_it = begin();
const_iterator l_end = end();
const_iterator r_it = rvalue.begin();
for (; l_it != l_end; ++l_it, ++r_it)
    {
    if ( *l_it < *r_it )
        {
        return true;
        }
    else if ( *r_it < *l_it )
        {
        return false;
        }
    }
return false;
}

};

#endif

