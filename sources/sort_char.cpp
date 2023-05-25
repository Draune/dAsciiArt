#include"../headers/sort_char.hpp"
#include<stdlib.h>

char ascii_shades_string[DASCIIART_NB_SHADES+1] = " .\'`^\",:;Il!i<>~+_-?[]{}1()|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

char d_find_char_shade(int num){
    if(num>69)
        num = 69;
    else if(num<0)
        num = 0;
    return ascii_shades_string[num];
}

