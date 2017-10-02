
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>
#include "widegolf.h"
// NB must be run with an argument

main (ic, v)char**v;
{
  wchar_t buffer[16] = L"";
  FILE *f;
  FILE *o = fopen ("UTF-16_REPR.txt", "r");

  if (fgetc (o) != 0xFF)
    f = fopen ("UTF-16_REPR.txt", "r,ccs=UTF16BE");
  else
    f = fopen ("UTF-16_REPR.txt", "r,ccs=UTF16LE");
  fclose (o);

  int *ip = &buffer[0];
  wint_t c = fgetwc (f);
  while (c != WEOF)
    {
      printf ("%llx", c);
      *(ip++) = c;
      c = fgetwc (f);
    }
  //printf ("\n");
  if (printwideStuff (f, buffer) ==-1)
    {
      perror ("wprintf");
    }
  fclose (f);
  printf ("\n");

  wchar_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?";
  for (i; i < 32; i += 2, puts (""))
    for (j = atoi (v[1]); j--;)
      for (k = 2; k--;)
        for (m = 256; m > 1; (m >>= 1, printf ((w[i + 1 - k] & m) ? "  " : "##")));



  for (j = atoi (v[1]); j--;)
    for (k = 2; k--;)
      for (m = 256; m > 1; (m >>= 1, printf ((buffer[i + 1 - k] & m) ? "  " : "##")));

  return 0;
}
