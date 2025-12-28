#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int strcmp(char str1[], char str2[]);
void to_string(int numb, char * buffer);
void reverse(char s[]);
int strlen(char s[]);
int atoi(char *str);
uint32_t str_to_hex(char *str);
void strcpy(char *dest, const char *src);

#endif