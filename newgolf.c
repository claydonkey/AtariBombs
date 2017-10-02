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

/*
 require CFLAGS=-march=x86-64 -mtune=generic -O2 -pipe -fno-stack-protector 
 * this is from 
  */

 void Answer2(int cnt) {
    wchar_t i, j, k, m, w[32] = L"";
    for (i; i < 32; i += 2, puts(""))
        for (j = cnt; j--;)
            for (k = 2; k--;)
                for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}


void Answer(int cnt) {
    wchar_t i, j, k, m, w[32] = L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?";
    for (i; i < 32; i += 2, puts(""))
        for (j = cnt; j--;)
            for (k = 2; k--;)
                for (m = 256; m > 1; (m >>= 1, printf((w[i + 1 - k] & m) ? "  " : "##")));
}

int main(int c, char** v) {
    uint16_t i, j, k, m;
    uint8_t w16[33]; //works as uint8_t ?
    // mpf_t mpf_bin; # pulls in stack protector
    uint8_t hex[33];
    uint8_t str[2];

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


    Answer(3);

    printf("DECIMAL REPR: ");
    printf(dec);
    printf("\n");

    memcpy(hex, gmp_tobase(dec, 16), 64);

    printf("HEX REPR: ");
    printf(hex);
    printf("\n");
    printf("LENGTH of HEX string is = %d\n", strlen(hex));
    printf("HEX REPR 2: ");
    char * pEnd;
    FILE *pFile = fopen("HEX REPR.txt", "w");
    uint8_t h[2];
    for (int i = 0; i < 33; i++) {
        strncpy(str, hex + (i * 2), sizeof (str));
        w16[i] = strtol(str, pEnd, 16);
        printf("%02X ", w16[i]);
    }
    fwrite(hex, sizeof (uint8_t), 64, pFile);
    fwrite(" ", sizeof (uint8_t), 1, pFile);
    fclose(pFile);
    printf("\n");
#if defined(_MSC_VER)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    uint8_t bom[] ={0xFF, 0xFE};
    pFile = fopen("ASCII REPR.txt", "w");
    //fwrite(w16, sizeof (wchar_t), wcslen(w16), pFile);
    fwrite(bom, sizeof (uint8_t), sizeof (bom), pFile);
    fwrite(w16, sizeof (uint8_t), 32, pFile);
    fclose(pFile);
    printf("_O_TEXT:\n");
    printf(w16);
    printf("\n");
    printf("_O_U16TEXT:\n");
#if defined(_MSC_VER)
    _setmode(_fileno(stdout), _O_U16TEXT)16;
#endif
    printf(w16);
#if defined(_MSC_VER)
    _setmode(_fileno(stdout), _O_TEXT);
#endif
    printf("\n");

    for (int i = 0; i < 32; i += 2, puts("")) for (int j = 3; j--;) for (k = 2; k--;) for (m = 256; m > 1; (m >>= 1, printf((~w16[i + 1 - k] & m) ? "##" : "  ")));
    //    free(pFile);
    //  free(dec);



    return 0;

}
