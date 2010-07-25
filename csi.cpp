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

#define CS_TRUE 1
#define CS_FALSE 0
#define CS_INVALID -1

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

// file i/o
void csfopen(char *fd, char *path, char *mode)
{
    FILE *f = fopen(path, mode);
    if(!f)
    {
      intret(CS_FALSE);
      return;
    }
    defformatstring(fds)("%d", f);
    alias(fd, fds);
    intret(CS_TRUE);
}

void csfread(char *fds, char *csbuf, int len)
{
    FILE *fd;
    const char *a = getalias(fds);
    char buf[4096]; // TODO: memory management (refcounts? pool?)
    fd = (FILE *) atol(a);

    if(len > 4096)
    {
        intret(CS_FALSE);
        return;
    }

    size_t r = fread(buf, len, 1, fd);
    alias(csbuf, buf);
    intret((int) r);
}

void csfclose(char *fds)
{
    FILE *fd;
    const char *a = getalias(fds);
    fd = (FILE *) atol(a);
    intret(fclose(fd) ? CS_FALSE : CS_TRUE);
}

ICOMMAND(wait, "i", (int *secs), cswait(*secs));
ICOMMAND(getcwd, "", (), { char r[MAX_PATH]; getcwd(r, MAX_PATH); result(r); });
ICOMMAND(fopen, "sss", (char *fd, char *path, char *mode), csfopen(fd, path, mode));
ICOMMAND(fread, "ssi", (char *fds, char *csbuf, int *len), csfread(fds, csbuf, *len));
ICOMMAND(fclose, "s", (char *fds), csfclose(fds));
