#include <iostream>
#include <db_cxx.h>

#include "ext/array.h"

int main()
{
const char* filename = "test.db";
typedef ext::array<int,128> key_t;
typedef ext::array<int,1024> value_t;
key_t key;
value_t value;

try
    {
    Db db ( NULL, 0 );
    db.open( NULL, filename, NULL, DB_BTREE, DB_CREATE | DB_THREAD, 0 );
    
    Dbt db_key( &key, key.size() );
    Dbt db_value( &value, value.size() );

    for (int i = 0; i < 10 * 1024; ++i)
        {
        key.fill( i );
        value.fill( i );
        db.put( NULL, &db_key, &db_value, 0 );
        }

    db.close( 0 );
    }
catch (DbException& e)
    {
    std::cerr << e.what() << std::endl;
    }
return 0;
}

