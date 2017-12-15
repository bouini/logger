#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdint.h>


typedef enum loglevel
{
    CRITICAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    VERBOSE
} loglevel_t;


void createLogger( uint8_t logid, char* logname );
void log_output( uint8_t logid, loglevel_t level, char* msg, ... );
loglevel_t getloglevel( uint8_t logid );

#define LOG( ID, LVL, MSG, ... ) do { if( LVL <= getloglevel( ID ) ) log_output( ID, LVL, MSG, ##__VA_ARGS__ ); } while( 0 );
 

#endif
