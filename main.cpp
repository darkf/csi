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

  execfile("stdlib.cfg", true);

  if(argc > 1)
  {
      execfile(argv[1], true);
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
