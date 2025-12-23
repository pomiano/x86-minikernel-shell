#include "../include/lib/string.h"

int strcmp(char str1[], char str2[]) {
    while(*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

void to_string(int numb, char * buffer) {
    int i =0;
    if(numb==0) 
        buffer[i] = 0;
    else {
        while(numb>0){
            buffer[i] = (numb % 10) + '0';
            numb/=10;
        }
    }
    buffer[i]='/0';
    reverse(buffer);

}

void reverse(char s[]) {
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i;
    for(int i =0; s[i];i++) {}
    return i;
}