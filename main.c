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
#include "gmgmp.h"
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <fcntl.h>
#include <string.h>
#include "widegolf.h"


/*
 require CFLAGS=-march=x86-64 -mtune=generic -O2 -pipe -fno-stack-protector
 * this is from GPG and it is how it was compiled
 * -fwide-exec-charset=utf-16  -finput-charset=utf-16 -fexec-charset=utf-16 for getting to 16bit widechars
 */


uint8_t ascii_to_utf8(uint8_t *out, uint8_t asc, uint8_t ctr) {
    if (asc < 128) {
	out[ctr] = asc;
	return 1;
    } else {
	out[ctr] = (asc >> 6) | 0xC0;
	out[ctr + 1] = (asc & 0x3F) | 0x80;
	return 2;
    }
}


void AnswerASCII(int r) {
    uint8_t i, j;
    int32_t m;
    uint8_t   *w = "ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ";
    for (i; i < 32; i += 2, puts(""))for (j = r; j--;)for (m = 1 << 16; m > 1; printf(((m /= 2)&((w[i+1] << 8) + w[i]) ? "  " : "##")));
}


void AnswerUTF(int r) {
    uint8_t i, j;
    int32_t m;
    uint16_t *w = L"ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ";

    for (i = 0; i < 32; i += 2, puts(""))for (j = r; j--;)for (m = 65536; m > 1; (m /= 2, printf(((w[i+1] << 8) + w[i] & m) ? "  " : "##")));

}

int main(int c, char** v) {

    AnswerUTF(3);
    AnswerASCII(3);
    uint16_t i, k, m;
    uint16_t w16[33];
    w16[32] = '\0';
    uint8_t w8[33];
    w16[32] = '\0';
    uint8_t str[3];

    const uint8_t * dec = gmp_todec("0b\
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

    const uint8_t * hex = gmp_tobase(dec, 16);

    printf("SIZE OF uint8_t  is  %d\n", sizeof (uint8_t));
    printf("SIZE OF wchar _t is  %d\n", sizeof (wchar_t));
    printf("DEC REPR: %s\n", dec);
    printf("LENGTH of DEC string is  %d\n", strlen(dec));
    printf("HEX REPR: %s\n", hex);
    printf("LENGTH of HEX string is  %d\n", strlen(hex));
    printf("HEX REPR 2: ");

    FILE *pFile = fopen("HEX_REPR.txt", "w");

    for (uint8_t i = 0; i < 32; i++) {
	strncpy(str, hex + (i * 2), sizeof (str));
	str[2] = '\0';
	w16[i] = strtol(str, '\0', 16);
	printf("%04X ", w16[i]);
    }
    printf("'\n");
    for (uint8_t i = 0; i < 32; i++) {
	strncpy(str, hex + (i * 2), sizeof (str));
	str[2] = '\0';
	w8[i] = strtol(str, '\0', 16);
	printf("%02X ", w8[i]);
    }

    fwrite(hex, sizeof (wchar_t), 32, pFile);

    fclose(pFile);
    printf("\n");
#if defined(__MINGW32__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    uint8_t bom16[] = {0xFF, 0xFE};
    uint8_t bom8[] = {0xEF, 0xBB, 0xBF};
    w16[32] = '\0';

    pFile = fopen("UTF-8_REPR.txt", "w");
    uint8_t wutf8[64];
    uint8_t wusize = 0;
    for (uint8_t ct = 0; ct < 32; ++ct)
	wusize += ascii_to_utf8(wutf8, w16[ct], wusize);
    fwrite(wutf8, sizeof (uint8_t), wusize, pFile);
    fclose(pFile);

    pFile = fopen("UTF-8_BOM_REPR.txt", "w");
    fwrite(bom8, sizeof (uint8_t), sizeof (bom8), pFile);
    fwrite(wutf8, sizeof (uint8_t), wusize, pFile);
    fclose(pFile);

    pFile = fopen("UTF-16_REPR.txt", "w");
    fwrite(w16, sizeof (uint16_t), 32, pFile);
    fclose(pFile);

    pFile = fopen("UTF-16_BOM_REPR.txt", "w");
    fwrite(bom16, sizeof (uint8_t), sizeof (bom16), pFile);
    fwrite(w16, sizeof (uint16_t), 32, pFile);
    fclose(pFile);

    pFile = fopen("ISO8859_REPR.txt", "w");
    fwrite(w8, sizeof (uint8_t), 32, pFile);
    fclose(pFile);

    printf("_O_TEXT:\n");
    printf(w16);
    printf("\n");
    printf("_O_U16TEXT:\n");
#if defined(__MINGW32__)
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif
    printf("%s\n", w16);
#if defined(__MINGW32__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    printf("LENGTH of UTF-8 string is %d\n", strlen((const char *) w16));
    printf("\n");

    for (int i = 0; i < 32; i += 2, puts("")) for (int j = 3; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m/=2, printf((~w16[i + 1 - k] & m) ? "##" : "  ")));

    return 0;

}
