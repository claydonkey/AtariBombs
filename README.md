
# Atari Bombs
## Introduction
The Atari ST was a rather popular personal computer from the mid 80's to early 90's era, powered by a Motorola 68000 microprocessor. On this machine, the default behavior of the operating system for uncaught CPU exceptions was to display a row of bombs on the screen, as shown in the following picture:


Source: https://commons.wikimedia.org/wiki/File:Row_of_bombs.png

NB: Depending on the OS version, the bomb graphics may vary slightly. But let's take this one as reference.
The number of bombs depends on the exception vector, the most common ones being:
($008) Bus Error : 2 bombs
($00c) Address Error : 3 bombs
($010) Illegal Instruction : 4 bombs
Goal
Your goal is to write a program or function that prints or outputs an ASCII art of such Atari ST bombs.
Input
An integer representing the number of bombs to display. Your code must support the most common values: 2, 3 and 4. Supporting less and/or more bombs is fine, but it is neither required nor subject to a bonus.
Output
The original bomb consists of a 16x16 pixel tile, represented here in both ASCII and binary:
```
....##..........    0000110000000000
.#.#..#.........    0101001000000000
.......#........    0000000100000000
#..#....#.......    1001000010000000
..#...#####.....    0010001111100000
......#####.....    0000001111100000
....#########...    0000111111111000
...###########..    0001111111111100
...###########..    0001111111111100
..#############.    0011111111111110
..########.####.    0011111111011110
...#######.###..    0001111111011100
...######.####..    0001111110111100
....#########...    0000111111111000
.....#######....    0000011111110000
.......###......    0000000111000000
```
In this challenge, each ASCII bomb must be stretched to twice its original width for a better rendering. Therefore, it will consist of 16 rows of 32 characters, using ## for 'ON' pixels and two spaces for 'OFF' pixels. All bomb tiles must be put side by side. Leading spaces are forbidden. Trailing spaces are also forbidden, except the ones that are actually part of the bomb tile (i.e. the 31st and 32nd columns) which must be present. You may include no more than one leading line-break and no more than one trailing line-break.
Example
Below is the reference output for two bombs, where mandatory line-breaks are marked as \n and tolerated extra line-breaks are marked as (\n):
```
(\n)

        ####                            ####                    \n
  ##  ##    ##                    ##  ##    ##                  \n
              ##                              ##                \n
##    ##        ##              ##    ##        ##              \n
    ##      ##########              ##      ##########          \n
            ##########                      ##########          \n
        ##################              ##################      \n
      ######################          ######################    \n
      ######################          ######################    \n
    ##########################      ##########################  \n
    ################  ########      ################  ########  \n
      ##############  ######          ##############  ######    \n
      ############  ########          ############  ########    \n
        ##################              ##################      \n
          ##############                  ##############        \n
              ######                          ######            (\n)
              
```              
(Of course, other line-break formats such as \r or \r\n may be used just as well.)
Rules
This is code-golf, so the shortest answer in bytes wins. Standard loopholes are forbidden.


# Solution

#GCC C 135 bytes ISO8859/ 174 bytes UTF-8

## ASCII
```
f(r,i,j,d){
    for(;i<32;i+=2,puts(""))
        for(d=15*r;--d;)
             printf("%s",(*(int*)&("ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ"[i]))&(1<<d%15)?"  ":"##");
}
```
In one line:
```
f(r,i,j,d){for(;i<32;i+=2,puts(""))for(d=15*r;--d;)printf("%s",(*(int*)&("ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ"[i]))&(1<<d%15)?"  ":"##");}
```
### Run with:
```
main(c,v)char**v{f(2,0)}
```
Compile source as ISO8859-x (ASCII).
NB óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ? should contain the invisible ASCII Codes but it has been broken due to the way StackExchange presents its content. Please see the ideaone link for proper test encoding Alternatively the original ASCII String is at : https://github.com/claydonkey/AtariBombs/blob/master/ISO8859_REPR2.txt

## Explanation

First a conversion of the hex representation of bombs [f3 ff ad ff fe ff 6f 7f dc 1f fc 1f f0 07 e0 03 e0 03 c0 01 c0 21 c0 43 e0 43 f0 07 f8 0f fe 3f] to UTF-8 (in the UTF-8 version the compiler stores the string as Wide Char Array - 2 or 4 bytes for each character at runtime but this is academic). Whereas UTF-8 characters would be stored as 2-4 bytes, these values are all within ISO-8859-1 (ASCII) and thus only require 1 byte. Also it is safe to be stored as ISO-8859-x (there are no 0x8_ or 0x9_ values). Therefore the text consumes 32 bytes in ISO-8859 and the routine consumes 135 bytes in total.
(NB wide chars are stored as a 16 bit integer in windows and 32bit in linux but again this is irrelevant to the task at hand)
Caveat: Not all the characters are displayable (the control characters below 0x20) .They are, however still present . Most web pages are utf-8/ 8859/1253 (https://w3techs.com/technologies/overview/character_encoding/all) so I reckon this is legit(shifting all values below 0x20 to printable ASCII should fix that). 

## UTF-8

Here is the version closer to the original posting with UTF-8 encoded source. This consumes 174 bytes. The string itself being 50 bytes of the source. The routine is also longer as the ASCII bytes are now stored with padding 0's for the 16bit/32bit Wide Chars and have to be shifted instead of casted to uint16_t as above. I have kept this up as it can be verified with ideone which uses UTF-8 encoding.
```
*w=L"óÿ­ÿþÿoÜüðààÀÀ!ÀCàCðøþ?";
f(r,i,j,m){
    for(i;i<32;i+=2,puts(""))
        for(j=r;j--;)
            for(m=65536;m>1;(m>>=1,printf(((w[i]<<8)+w[i+1]&m)?"  ":"##")));
}
```
### Run with:
```
main(){f(2,0);} 
```

If you can set the implicit value to a 16bit integer in your complier you can omit the wchar_t type declaration of the Wide Char. Ideone doesn't complain so I reckon it's good to go.
Try it out on [ideone]: https://ideone.com/Aqz63S
 
