#include <stdlib.h>
#include <iostream>

#include "sys/cfg.h"
#include "net/cfg.h"
#include "sys/main.h"

static void help(std::ostream& out, int argc, char* argv[])
{
out << "usage: " << argv[0] << " <config file name>" << std::endl;
}

int main(int argc, char* argv[])
{
if ( 2 != argc )
    {
    help( std::cerr, argc, argv );
    return EXIT_FAILURE;
    }

pugi::xml_document cfgfile;
pugi::xml_parse_result result = cfgfile.load_file( argv[1] );
pugi::xml_node cfg = cfgfile.first_child();
if ( !result || !cfg )
    {
    std::cerr << "invalid config file" << std::endl;
    return EXIT_FAILURE;
    }

try
    {
    sys::check_cfg( cfg );
    net::check_cfg( cfg );
    }
catch (cmn::exception& e)
    {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
    }
//TODO: detach here
return sys::run( cfg );
}

