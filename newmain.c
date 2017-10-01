/*
 * The MIT License
 *
 * Copyright 2016 Anthony Campbell.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/**
 * @author Anthony Campbell contact@claydonkey.com
 */



#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>
//char * ascii = "óÿ[ÿûû{ýÁÿüðà>þÿ";
char * mhex = "f3ffadfffeff6f7fdc1ffc1ff007e003e003c001c021e023e043f007f80ffe3f";

//0b111100111111111110101101111111111111111011111111110111101111111110111000001111111111100000111111111000000000111111000000000001111100000000000111100000000000001110000000010000111100000001000111110000001000011111100000000011111111000000011111111111000111111
//0b0000110000000000010100100000000000000001000000001001000010000000001000111110000000000011111000000000111111111000000111111111110000011111111111000011111111111110001111111101111000011111110111000001111110111100000011111111100000000111111100000000000111000000óÿ­ÿþÿoÜüðààÀÀ!à#àCðøþ?▒▒▒▒▒▒o▒▒▒▒▒▒▒!▒#▒C▒▒▒?

void f2(int k) {
    int d[] = {3072, 20992, 256, 36992, 9184, 992, 4088, 8188, 8188, 16382, 16350, 8156, 8124, 4088, 2032, 448, 0}, m, c, *i = d;
    for (; *i; i++, puts(""))for (c = k; c--;)for (m = 32768; m; write(1, &"##  "[m&*i ? 0 : 2], 2), m >>= 1);
}

a[] = {224, 1016, 2044, 4062, 4078, 8175, 8191, 4094, 4094, 2044, 496, 4592, 18496, 128, 10496, 1536};

b(n, i, j) {
    for (i = 16; i--; puts(" "))for (j = n * 15; j--; printf(a[i]&1 << j % 16 ? "##" : "  "));
}

void f(r) {
    uint16_t i, j, k, m;
    unsigned short * w2 = (unsigned short *) L"óÿ­ÿþÿoÜüðààÀÀ!à#àCðøþ?!à#àCðøþ?";
    for (i; i < 32; i += 2, puts("")) for (j = r; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m >>= 1, printf((w2[i + 1 - k] & m) ? "  " : "##")));
}

main2(c, v)char** v;
{
    uint16_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!à#àCðøþ?";
    for (i; i < 32; i += 2, puts("")) for (j = atoi(v[1]); j--;) for (k = 2; k--;) for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}

int main(int c, char** v) {
    uint16_t i, j, k, m, w[] = L"óÿ­ÿþÿoÜüðààÀÀ!à#àCðøþ?";
    char w2[32];
    mpf_t mpf_bin;
    int slen;
    char * dec = gmp_todec("0b\
1111001111111111\
1010110111111111\
1111111011111111\
0110111101111111\
1101110000011111\
1111110000011111\
1111000000000111\
1110000000000011\
1110000000000011\
1100000000000001\
1100000000100001\
1110000000100011\
1110000001000011\
1111000000000111\
1111100000001111\
1111111000111111\
");
    char * hex = gmp_tobase(dec, 16);
    printf(hex);
    printf("\n");
    slen = strlen(hex);
    printf("Length of hex string is = %d\n", slen);

    char str2[2];

    for (int i = 0; i < 32; i++) {
	strncpy(str2, hex, sizeof (str2));
	hex += 2;
	w[i] = (wchar_t) strtol(str2, NULL, 16);
	w2[i] = (char) strtol(str2, NULL, 16);
    }
    FILE *pFile = fopen("test.txt", "w");
    fwrite(w, sizeof (wchar_t), wcslen(w), pFile);

    fclose(pFile);


    printf("\n");
    printf(w2);
    printf("\n");
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(w);
    wprintf("\n");

    _setmode(_fileno(stdout), _O_TEXT);

    f(atoi(v[1]));
    //  f2(atoi(v[1]));
    /*
	char b [200], l = 0;
	for (int i = 0; i < wcslen(w) - 2; i++) {
	    wchar_t n = w[i];
	    l = 0;
	    for (wchar_t m = 0x80; m > 0; m >>= 1)
		b[l++] = b[l++] = (n & m) ? ' ' : '#';
	    b[l++] = '\0';
	    if (!(i % 2))printf("\n");
	    printf("%s", b);
	}
     */


    /*/
	printf("\n");

	for (int i = 0; i < 16; i++, printf("\n"))
	    for (unsigned int m = 1000000; m > 1; (m >>= 1, printf((ww[i] & m) ? "  " : "##")));
     */

    //  d[] = {3072, 20992, 256, 36992, 9184, 992, 4088, 8188, 8188, 16382, 16350, 8156, 8124, 4088, 2032, 448, 0}, m, c, *i = d;for (; *i; i++, puts(""))for (c = k; c--;)for (m = 32768; m; write(1, &"#//#  "[m&*i ? 0 : 2], 2), m >>= 1);


    //  printf("\n");

    //  int i, j, k;for (i =0; i < 32; i = i + 2, puts("")) for (j = 0; j < 4; j++) for (k = 0; k < 2; k++) for (wchar_t m = 256; m > 1; (m >>= 1, printf((w[i + k] & m) ? "  " : "##")));




    /*
 printf("\n");

 for (int i = 0; i < 32; i++, (!(i % 2)) ? printf("\n") : NULL)
     for (wchar_t m = 256; m > 1; (m >>= 1, printf((w[i] & m) ? "  " : "##")));

	printf("\n");
	wchar_t *i = w;
	for (; *i; i++)
	    for (wchar_t m = 0x100; m > 1; (m >>= 1, printf((m&*i) ? "0" : "1")));

	printf("\n");


		 char buffer [200];
		 for (int i = 0; i < wcslen(w); i++) {
		     wchar_t n = w[i];
		     itoa(n, buffer, 2);
		     _setmode(_fileno(stdout), _O_TEXT);
		     printf("%s", buffer);
		     if (i % 2 == 0)printf("\n");

		 }

		 printf("\n");


		 for (int i = 0; i < wcslen(w); i++) {
		     _setmode(_fileno(stdout), _O_U16TEXT);
		     wprintf(L"%02x", w[i]);
		 }
		 _setmode(_fileno(stdout), _O_TEXT);

		 //   char buffer [33];
		 //   itoa(0xFF, buffer, 2);
		 // printf("binary: %s\n", buffer);
		 // for (int i = 0; i < strlen(hex); i++)
		 //wprintf("The ASCII Code: %x\n", hex[i]);
		 /*/





    return 0;

    //  long long a = 1684008837394607823326142550656720065274811973287834839046269468351397663;
    //   printf("%lld", a);
}



