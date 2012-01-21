#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <string.h>

#include "sys/cfg.h"
#include "net/cfg.h"
#include "sys/main.h"
#include "version.h"
#include "cmn/pthread_cpu_time.h"

static void help(std::ostream& out, int argc, char* argv[], int topic = 0)
{
    switch(topic)
    {
        case 'c':
            out << "todo: man " << argv[0] << " -c|--config" << std::endl;
            break;
        case 'D':
            out << "todo: man " << argv[0] << " -D|--daemon" << std::endl;
            break;
        case 'v':
            out << "todo: man " << argv[0] << " -v|--version" << std::endl;
            break;
        default: 
            out << "usage: " << argv[0] << "\n";
            out << "\t -D|--daemon daemon mode\n";
            out << "\t -c|--config <config file name>" << std::endl;
            break;
    }
}

/*
 * Function will daemonize process.
 * Daemons are also characters in Greek mythology, some of whom handled tasks that the gods could not be bothered with.
 */
pid_t daemonize(const std::string &dir = "/", const std::string &stdinfile = "/dev/null", const std::string &stdoutfile = "/dev/null", const std::string &stderrfile = "/dev/null") throw (cmn::exception)
{
    pid_t pid;
    
    umask(0);
    rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) 
    {
        throw cmn::exception(strerror(errno)); //can't get file limit
    }
    if ((pid = fork()) < 0) 
    {
        throw cmn::exception(strerror(errno)); //Cannot fork!
    }
    else
    {
        if (pid != 0) 
        { 
            return pid; //exit(0); //parent
        }
    }   
    
    setsid();

    if (!dir.empty() && chdir(dir.c_str()) < 0) 
    {
        throw cmn::exception(strerror(errno)); // Oops we couldn't chdir to the new directory
    }
    if (rl.rlim_max == RLIM_INFINITY) 
    {
        rl.rlim_max = 1024;
    }
    for (unsigned int i = 0; i < rl.rlim_max; i++) 
    {
        close(i); // Close all open file descriptors
    }

    int fd0 = open(stdinfile.c_str(), O_RDONLY);
    int fd1 = open(stdoutfile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    int fd2 = open(stderrfile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd0 != STDIN_FILENO || fd1 != STDOUT_FILENO || fd2 != STDERR_FILENO) 
    {
        //Unexpected file descriptors
        throw cmn::exception("new standard file descriptors were not opened as expected");
    }
    return 0;    
}

int main(int argc, char* argv[])
{
    int option_index    = 0;    
    int opt_help        = 0;
    int opt_version     = 0;
    int opt_demonize    = 0;
    int opt_config_name = 0;
    int opt_default     = 0;
    char* config_name   = NULL;
    static const char options[] = "-:hvDc:W;";
    static const struct option long_options[] = {
        { "help",       no_argument,        &opt_help,          'h' },
        { "version",    no_argument,        &opt_version,       'v' },
        { "daemon",     no_argument,        &opt_demonize,      'D' },
        { "config",     required_argument,  NULL,               'c' },
        { 0,            0,                  0,                  0   },
    };

    while ( true )
        {
        int option = getopt_long( argc, argv, options, long_options, &option_index );
        if ( -1 == option )
            {
            break;
            }

        switch ( option )
            {
            case 'h':
                opt_help = option;
                break;
            case 'v':
                opt_version = option;
                break;
            case 'D':
                opt_demonize = option;
                break;
            case 'c':
                opt_config_name = option;
                if (NULL != optarg)
                {
                    config_name = optarg;
                }
                break;
            case 0: // getopt_long set var
                break;
            case 1:
                if (!opt_config_name && NULL != optarg)
                    {
                    opt_config_name = 1;
                    config_name = optarg;
                    }
                break;
            default:
                opt_default = 1;
                break;
            }
        }

    while (optind < argc)
        {
        opt_config_name = 1;
        config_name = argv[optind++];
        }        

    if (opt_help)  
        {
        help( std::cout, argc, argv, opt_version | opt_demonize | opt_config_name );
        return EXIT_SUCCESS;
        }
    if (opt_version)
        {
        version( std::cout );
        return EXIT_SUCCESS;    
        }
    if (opt_default)
        {
        help( std::cerr, argc, argv );
        return EXIT_FAILURE;
        }
    if ( !opt_config_name || NULL == config_name )
        {
        std::cerr << "set config file name" << std::endl;
        //return EXIT_FAILURE;
        }

    pugi::xml_document cfgfile;
    pugi::xml_parse_result result = cfgfile.load_file( config_name );
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

    if (opt_demonize)
    {
    pid_t err = daemonize("/", "/dev/null", "/tmp/fd1", "/tmp/fd2");
    if (err) return 0;
    std::cerr << "daemonize complited" << std::endl;
    }
    
    return sys::run( cfg );
}

