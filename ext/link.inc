#include <stddef.h>

namespace ext
{

link::link()
{
m_links = NULL;
}

link::link(const link& origin)
{
origin.Link();
m_links = origin.m_links;
}

link::~link()
{
UnLink();
}

void link::Init()
{
if ( NULL != m_links )
    {
    if ( 1 == *m_links )
        {
        return;
        }
    else
        {
        UnLink();
        }
    }
m_links = new int( 1 );
}

void link::Link() const
{
if ( NULL != m_links )
    {
    ++*m_links;
    }
}

void link::UnLink()
{
if ( NULL == m_links )
    {
    return;
    }
--*m_links;
if ( 0 == *m_links )
    {
    delete m_links;
    }
m_links = NULL;
}

link& link::operator = (const link& rvalue)
{
UnLink();
rvalue.Link();
m_links = rvalue.m_links;
return *this;
}

bool link::IsLinked() const
{
return (NULL != m_links) && (1 != *m_links);
}

} namespace ext

