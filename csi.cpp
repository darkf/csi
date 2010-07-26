// this file implements csi-specific functions
// license: zlib
// copyright (c) 2010 darkf
#include "cube.h"
#include <unistd.h>

#ifdef WIN32
#define getcwd _getcwd
#define chdir _chdir
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
#define GET_FDS const char *a = getalias(fds); \
    fd = (FILE *) atol(a);

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
    GET_FDS
    char buf[4096]; // TODO: memory management (refcounts? pool?)

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
    GET_FDS
    intret(fclose(fd) ? CS_FALSE : CS_TRUE);
}

void csfseek(char *fds, long offset, int origin)
{
    FILE *fd;
    GET_FDS
    intret(fseek(fd, offset, origin) == 0 ? CS_TRUE : CS_FALSE);
}

void csftell(char *fds)
{
    FILE *fd;
    GET_FDS
    intret(ftell(fd));
}

ICOMMAND(wait, "i", (int *secs), cswait(*secs));
ICOMMAND(getcwd, "", (), { char r[MAX_PATH]; getcwd(r, MAX_PATH); result(r); });
ICOMMAND(chdir, "s", (char *path), intret(chdir(path) == 0 ? CS_TRUE : CS_FALSE));
ICOMMAND(fopen, "sss", (char *fd, char *path, char *mode), csfopen(fd, path, mode));
ICOMMAND(fread, "ssi", (char *fds, char *csbuf, int *len), csfread(fds, csbuf, *len));
ICOMMAND(fseek, "sii", (char *fds, int *offset, int *origin), csfseek(fds, (long) *offset, *origin));
ICOMMAND(ftell, "s", (char *fds), csftell(fds));
ICOMMAND(fclose, "s", (char *fds), csfclose(fds));
