#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

void vsyslog(int priority, const char *format, va_list args);

void cft_log(const char* format, ...)  {
    va_list arglist;
    va_start( arglist, format );
    vsyslog(LOG_ERR, format, arglist );
    //vprintf(format, arglist );
    va_end( arglist );
}

