
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>

// NB must be run with an argument
main2(c,v)char**v;
{
    wchar_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?ⓙ";
    for (i; i < 32; i += 2, puts(""))
	for (j = atoi(v[1]); j--;)
	    for (k = 2; k--;)
		for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}
