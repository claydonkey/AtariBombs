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
//#include <gmp.h>
#include "gmgmp.h"
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>

int main(int c, char** v) {
    uint16_t i, j, k, m, w[32];
    mpf_t mpf_bin;

    char hex[32];

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
1100000001000011\
1110000001000011\
1111000000000111\
1111100000001111\
1111111000111111");

    printf("DECIMAL REPR:");
    printf(dec);
    printf("\n");
    memcpy(hex, gmp_tobase(dec, 16), 64);

    printf("HEX REPR:");
    printf(hex);
    printf("\n");
    printf("LENGTH of HEX string is = %d\n", strlen(hex));

    char str2[2];

    printf("\n");

    for (int i = 0; i < 32; i++) {
	strncpy(str2, hex + (i * 2), sizeof (str2));
	w[i] = (wchar_t) strtol(str2, NULL, 16);
	printf("%02X ", w[i]);
    }
    printf("\n");

    _setmode(_fileno(stdout), _O_TEXT);
    FILE *fp = fopen("ASCII REPR.txt", "w");
    fwrite(w, sizeof (wchar_t), wcslen(w), fp);
    fclose(fp);
    printf("_O_TEXT:\n");
    wprintf(w);
    printf("\n");
    printf("_O_U16TEXT:\n");

    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(w);

    _setmode(_fileno(stdout), _O_TEXT);
    printf("\n");

    for (int i = 0; i < 32; i += 2, puts("")) for (int j = 3; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m >>= 1, printf((~w[i + 1 - k] & m) ? "##" : "  ")));

    return 0;

}