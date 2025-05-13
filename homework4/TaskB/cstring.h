#ifndef CSTRING_H_
#define CSTRING_H_

#include <cstddef>

size_t Strlen(const char* str);
int Strcmp(const char* first, const char* second);
int Strncmp(const char* first, const char* second, size_t count);
char* Strcpy(char* dest, const char* src);
char* Strncpy(char* dest, const char* src, size_t count);
char* Strcat(char* dest, const char* src);
char* Strncat(char* dest, const char* src, size_t count);
const char* Strchr(const char* str, char symbol);
const char* Strrchr(const char* str, char symbol);
size_t Strspn(const char* dest, const char* src);
size_t Strcspn(const char* dest, const char* src);
const char* Strpbrk(const char* dest, const char* breakset);
const char* Strstr(const char* str, const char* pattern);

#endif
