/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "widegolf.h"
#include <stdio.h>
#include <wchar.h>

int
printwideStuff (FILE * f, wchar_t buffer[])
{

  fseek (f, 0, SEEK_SET);
  wint_t c = fgetwc (f);
    while (c != WEOF)
      {
      c = fgetwc (f);
  
       putwchar (c);
     }
  
  if (wprintf (buffer) == -1 || !fputws (buffer, stdout) == -1)return -1;
  return 0;
}