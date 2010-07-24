// this file implements csi-specific functions
// license: zlib
// copyright (c) 2010 darkf
#include "cube.h"
#include <unistd.h>

#ifdef WIN32
#define getcwd _getcwd
#endif

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

ICOMMAND(exit, "", (), exit(0));

// blocking sleep
void cswait(int secs)
{
    #ifdef WIN32
    Sleep(1000 * secs);
    #else
    sleep(secs);
    #endif
}

ICOMMAND(wait, "i", (int *secs), cswait(*secs));
ICOMMAND(getcwd, "", (), { char r[MAX_PATH]; getcwd(r, MAX_PATH); result(r); });
