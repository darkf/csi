// this file implements csi-specific functions
// license: zlib
// copyright (c) 2010 darkf
#include "cube.h"

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
