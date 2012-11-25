#include "cube.h"

VARN(profiler, _profiler, 0, 0, 1);

#define LOGSTRLEN 512

static char *logfilename = NULL;
static FILE *logfile = NULL;

void closelogfile()
{
    if(logfile)
    {
        fclose(logfile);
        logfile = NULL;
    }
}

void setlogfile(const char *fname)
{
    closelogfile();
    if(fname && fname[0])
    {
        fname = findfile(fname, "w");
        if(fname)
        {
            logfilename = newstring(fname);
            logfile = fopen(fname, "w");
        }
    }
    if(logfile)
    {
        setvbuf(logfile, NULL, _IONBF, 0);
    }
}

void profoutfv(int type, const char *fmt, va_list args)
{
    if(logfile)
    {
        static char buf[LOGSTRLEN];
        //static uchar ubuf[512];
        vformatstring(buf, fmt, args, sizeof(buf));
        int len = strlen(buf);//, carry = 0;
        fwrite(buf, 1, len, logfile);
        /*while(carry < len)
        {
            int numu = encodeutf8(ubuf, sizeof(ubuf)-1, &((uchar *)buf)[carry], len - carry, &carry);
            if(carry >= len) ubuf[numu++] = '\n';
            fwrite(ubuf, 1, numu, logfile);
        }*/
    }
}

void profoutf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    profoutfv(CON_INFO, fmt, args);
    va_end(args);
}

void profoutf(int type, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    profoutfv(type, fmt, args);
    va_end(args);
}

ICOMMAND(profilerlogfile, "s", (char *filename),
{
    if(filename && filename[0])
    {
        setlogfile(filename);
    }
    strret(logfilename);
});
