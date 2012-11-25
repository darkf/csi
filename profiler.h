// profiler functions
// license: zlib
#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#include "cube.h"

// profiler

enum
{
    PROF_ALIAS   = 1<<0,
    PROF_COMMAND = 1<<1,
    PROF_CONC    = 1<<2,
    PROF_CONV    = 1<<3
};

extern int _profiler;

void profoutfv(int type, const char *fmt, va_list args);
void profoutf(const char *fmt, ...);
void profoutf(int type, const char *fmt, ...);

#endif // PROFILER_H_INCLUDED
