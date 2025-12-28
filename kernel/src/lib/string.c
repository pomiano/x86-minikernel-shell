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
        buffer[i++] = '0';
    else {
        while(numb>0){
            buffer[i++] = (numb % 10) + '0';
            numb/=10;
        }
    }
    buffer[i]='\0';
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
    for(i =0; s[i];i++) {}
    return i;
}

int atoi(char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res = res * 10 + str[i] - '0';
        } else {
            break; 
        }
    }
    return res;
}

uint32_t str_to_hex(char *str) {
    uint32_t val = 0;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str += 2;
    }
    
    while (*str) {
        uint8_t byte = *str;
        if (byte >= '0' && byte <= '9') 
            byte = byte - '0';
        else if(byte >= 'a' && byte <= 'f') 
            byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F') 
            byte = byte - 'A' + 10;
        else break; 
        
        val = (val << 4) | (byte & 0x0F);
        str++;
    }
    return val;
}

void strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++));
    *dest = '\0';
}