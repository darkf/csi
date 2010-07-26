// main program for csi
// license: zlib
// copyright (c) 2010 darkf
#include <cstdio>
#include "cube.h"

const int BUFSIZE = 1024;

int main(int argc, char *argv[])
{
  char buf[BUFSIZE];
  printf("csi v0.0\n");

  if(argc > 1)
  {
      char *filename = argv[1];
      char *buf;
      long len;
      FILE *fd = fopen(filename, "r");

      fseek(fd, 0, SEEK_END);
      len = ftell(fd);
      rewind(fd);
      buf = new char[len];
      fread(buf, len, 1, fd);

      if(ferror(fd))
      {
        printf("couldn't read input file '%s'\n", filename);
        return 1;
      }

      execute(buf);
      delete [] buf;
      return 0;
  }

  while(true)
  {
      printf(">>> ");
      fgets(buf, BUFSIZE, stdin);
      printf("> %s\n", executeret(buf));
  }

  return 0;
}
