#include <stdio.h>
#include "bmp.h"
#include "playfair.h"
#include <string.h>
#include <stdlib.h>

int main(){

    bmp_decrypt("hello", "hello");
    bmp_encrypt("hello", "hello");
    bit_encrypt("hello");
    bit_decrypt("hello");
    playfair_encrypt("hello","hello");
    playfair_decrypt("hello","hello");
    vigenere_decrypt("hello","hello");
    vigenere_encrypt("hello","hello");
    reverse("hello");

    return 0;
}
