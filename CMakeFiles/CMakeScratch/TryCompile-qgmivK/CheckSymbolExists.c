/* */
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <float.h>

int main(int argc, char** argv)
{
  (void)argv;
#ifndef memmove
  return ((int*)(&memmove))[argc];
#else
  (void)argc;
  return 0;
#endif
}
