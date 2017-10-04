/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   widegolf.h
 * Author: anthony
 *
 * Created on 02 October 2017, 00:13
 */
#include <wchar.h>
#ifndef WIDEGOLF_H
#define WIDEGOLF_H


#if defined(_MSC_VER) || defined  (__MINGW32__)

#else
#define  _O_U8TEXT 0x00040000
#define  _O_U16TEXT 0x00020000
#endif

 uint8_t ascii_to_utf8(uint8_t *out, uint8_t asc, uint8_t ctr);

#endif