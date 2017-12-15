#include "logger.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* loglevel_str[] = { "CRITICAL", "ERROR", "WARNING", "INFO", "DEBUG", "VERBOSE" };

typedef struct logger
{
    uint8_t id;
    char* name;
    loglevel_t level;
} logger_t;

logger_t* loggers[256];

void createLogger( uint8_t logid, char* logname )
{
    size_t size = strlen( logname );
    logger_t* log = malloc( sizeof(logger_t) );
    log->id = logid;
    log->level = INFO;
    log->name = malloc( size+1 );
    strncpy( log->name, logname, size );
    loggers[ logid ] = log;
}

void log_output( uint8_t logid, loglevel_t level, char* msg, ... )
{
    va_list args;
    char buffer[256];
    char timebuffer[20];
    logger_t* log = loggers[ logid ];
    int ms = 0;
    time_t t;
    struct timespec ts;
    struct tm* timeinfo;

    if( log != NULL )
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        ms = ts.tv_nsec / 1.0e6; 
        timeinfo = localtime( &ts.tv_sec );
        
        va_start( args, msg );
        vsprintf( buffer, msg, args );
        strftime( timebuffer, 20, "%x %X",timeinfo);
        printf( "%s,%d [%s] <%s> %s\n", timebuffer, ms, loglevel_str[ level ], log->name, buffer );
        va_end( args );
    }
}

loglevel_t getloglevel( uint8_t logid )
{
    logger_t* log = loggers[ logid ];
    if( log != NULL )
    {
        return log->level;
    }
    return CRITICAL;
}
