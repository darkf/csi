// console functions
// license: zlib
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include "cube.h"

// console

enum
{
    CON_INFO  = 1<<0,
    CON_WARN  = 1<<1,
    CON_ERROR = 1<<2,
    CON_DEBUG = 1<<3,
    CON_INIT  = 1<<4,
    CON_ECHO  = 1<<5
};

void conoutfv(int type, const char *fmt, va_list args);
void conoutf(const char *fmt, ...);
void conoutf(int type, const char *fmt, ...);
void fatal(const char *s, ...);

#endif // CONSOLE_H_INCLUDED
