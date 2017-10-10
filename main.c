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
#include "bitFlip.h"

/*
 require CFLAGS=-march=x86-64 -mtune=generic -O2 -pipe -fno-stack-protector
 * this is from GPG and it is how it was compiled
 * -fwide-exec-charset=utf-16  -finput-charset=utf-16 -fexec-charset=utf-16 for getting to 16bit widechars
 */

uint16_t flips(uint16_t o) {
    uint8_t i, s = sizeof (o)*8;
    uint16_t r;
    for (i = 0; i < s; i++)
	r |= ((o >> i) & 1) << (s - 1 - i);
    return r;
}

uint8_t flip(uint8_t o) {
    uint8_t i, s = sizeof (o)*8;
    uint8_t r;
    for (i = 0; i < s; i++)
	r |= ((o >> i) & 1) << (s - 1 - i);
    return r;
}

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
    uint8_t *w = "ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ";
    for (i; i < 32; i += 2, puts(""))for (j = r; j--;)for (m = 1 << 16; m > 1; printf(((m /= 2)&((w[i + 1] << 8) + w[i]) ? "  " : "##")));
}

void AnswerUTF(int r) {
    uint8_t i, j;
    int32_t m;
#ifdef __MINGW32__
    uint16_t
#else
    uint32_t
#endif
	    *w = L"ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ";

    for (i = 0; i < 32; i += 2, puts(""))for (j = r; j--;)for (m = 65536; m > 1; (m /= 2, printf(((w[i + 1] << 8) + w[i] & m) ? "  " : "##")));

}

int main(int c, char** v) {

    AnswerUTF(3);
    //  AnswerASCII(3);
    uint16_t i, k, m;
    uint16_t w16[33], w16b[33];
    uint8_t w8[33];

    uint8_t str[3];
    uint8_t str2[5];

    uint8_t * dec = gmp_todec("0b\
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

    uint8_t * dec2 = gmp_todec("0b\
    0000110000000000\
    0101001000000000\
    0000000100000000\
    1001000010000000\
    0010001111100000\
    0000001111100000\
    0000111111111000\
    0001111111111100\
    0001111111111100\
    0011111111111110\
    0011111111011110\
    0011111110111100\
    0001111110111100\
    0000111111111000\
    0000011111110000\
    0000000111000000");


    const uint8_t * hex = gmp_tobase(dec, 16);

    uint16_t rhex = flips(0b0000110001111001);


    printf("SIZE OF uint8_t  is  %d\n", sizeof (uint8_t));
    printf("SIZE OF wchar _t is  %d\n", sizeof (wchar_t));
    printf("DEC REPR: %s\n", dec);
    printf("LENGTH of DEC string is  %d\n", strlen(dec));
    printf("HEX REPR: %s\n", hex);
    printf("LENGTH of HEX string is  %d\n", strlen(hex));
    printf("HEX REPR 2: ");

    FILE *pFile = fopen("HEX_REPR.txt", "w");

    for (uint8_t i = 0; i < 32; i++) {
	strncpy(str, hex + (i * 2), 2);
	str[2] = '\0';
	w16b[i] = flips((uint16_t) strtol(str, '\0', 16)) >> 8;
	printf("%04X ", w16b[i]);
    }

    for (uint8_t i = 0; i < 16; i++) {
	strncpy(str2, hex + (i * 4), 4);
	str2[4] = '\0';
	w16[i] = ((uint16_t) strtol(str2, '\0', 16)) >> 1;
	w16[i] |= 0x8000;
	w16[i] = flips(w16[i]);
	//w16[i] =  ((uint16_t) strtol(str2, '\0', 16));
	printf("%04X ", w16[i]);
    }


    printf("'\n");
    for (uint8_t i = 0; i < 32; i++) {
	strncpy(str, hex + (i * 2), 2);
	str[2] = '\0';
	w8[i] = flip((uint8_t) (strtol(str, '\0', 16)));
	printf("%02X ", w8[i]);
    }
    fwrite(&w16[0], 2, 16, pFile);
    //fwrite(&w8[0], 1, 64, pFile);

    fclose(pFile);
    printf("\n");
#if defined(__MINGW32__)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    uint8_t bom16[] = {0xFF, 0xFE};
    uint8_t bom8[] = {0xEF, 0xBB, 0xBF};
    w16[32] = '\0';
    w8[32] = '\0';

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
    for (int i = 0; i < 16; i++, puts("")) for (int j = 3; j--;) for (m = 32768; m; m /= 2) printf((~w16[i] & m) ? "##" : "  ");
    for (int i = 0; i < 32; i += 2, puts("")) for (int j = 3; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m /= 2, printf((~w16b[i + 1 - k] & m) ? "##" : "  ")));
    for (int i = 0; i < 32; i += 2, puts("")) for (int j = 3; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m /= 2, printf((~w8[i + 1 - k] & m) ? "##" : "  ")));
    free(dec);
    free(dec2);
    return 0;

}
