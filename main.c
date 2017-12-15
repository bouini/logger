#include "logger.h"

int main(int argc, char **argv)
{
    createLogger( 0, "Log" );
    createLogger( 1, "AnotherLog" );
    LOG( 0, INFO, "test" );
    LOG( 1, ERROR, "test 2" );
    LOG( 1, CRITICAL, "%d %s", 12, "34" );
    return 0;
}

