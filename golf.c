
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>

main2(c, v)char**v;
{
    uint16_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!à#àCðøþ?";
    for (i; i < 32; i += 2, puts(""))for (j = atoi(v[1]); j--;)for (k = 2; k--;)for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}

void f(r, i, j, k, m) {
    wchar_t *z = L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?ⓙ";
    for (i; i < 32; i += 2, puts(""))for (j = r; j--;)for (k = 2; k--;)for (m = 256; m > 1; (m >>= 1, printf((z[i + 1 - k] & m) ? "  " : "##")));
}

main3
(c, v)char**v;
{
    f(3, 0, 0, 0, 0);
    return 0;
}

main(c, v)char**v;
{
    wchar_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?ⓙ";
    for (i; i < 32; i += 2, puts(""))
	for (j = atoi(v[1]); j--;)
	    for (k = 2; k--;)
		for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}