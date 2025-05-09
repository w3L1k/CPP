#include "cstring.h"

size_t Strlen(const char* str) {
  size_t length = 0;
  while (str[length] != '\0') {
    ++length;
  }
  return length;
}

int Strcmp(const char* first, const char* second) {
  while (*first && (*first == *second)) {
    ++first;
    ++second;
  }
  return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
}

int Strncmp(const char* first, const char* second, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    if (first[i] != second[i]) {
      return static_cast<unsigned char>(first[i]) - static_cast<unsigned char>(second[i]);
    }
    if (first[i] == '\0') {
      return 0;
    }
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  char* result = dest;
  while ((*dest++ = *src++) != '\0') {}
  return result;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* result = dest;
  size_t i = 0;
  for (; i < count && src[i] != '\0'; ++i) {
    dest[i] = src[i];
  }
  for (; i < count; ++i) {
    dest[i] = '\0';
  }
  return result;
}

char* Strcat(char* dest, const char* src) {
  char* result = dest;
  while (*dest) {
    ++dest;
  }
  while ((*dest++ = *src++) != '\0') {}
  return result;
}

char* Strncat(char* dest, const char* src, size_t count) {
  char* result = dest;
  while (*dest) {
    ++dest;
  }
  size_t i = 0;
  while (i < count && src[i] != '\0') {
    *dest++ = src[i++];
  }
  *dest = '\0';
  return result;
}

const char* Strchr(const char* str, char symbol) {
  while (*str) {
    if (*str == symbol) {
      return str;
    }
    ++str;
  }
  return (symbol == '\0') ? str : nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  const char* result = nullptr;
  do {
    if (*str == symbol) {
      result = str;
    }
  } while (*str++);
  return result;
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = 0;
  for (; *dest; ++dest) {
    const char* s = src;
    while (*s && *s != *dest) {
      ++s;
    }
    if (*s == '\0') {
      break;
    }
    ++count;
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = 0;
  for (; *dest; ++dest) {
    const char* s = src;
    while (*s && *s != *dest) {
      ++s;
    }
    if (*s != '\0') {
      break;
    }
    ++count;
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  for (; *dest; ++dest) {
    for (const char* b = breakset; *b; ++b) {
      if (*dest == *b) {
        return dest;
      }
    }
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  if (!*pattern) {
    return str;
  }
  for (; *str; ++str) {
    const char* s = str;
    const char* p = pattern;
    while (*s && *p && *s == *p) {
      ++s;
      ++p;
    }
    if (!*p) {
      return str;
    }
  }
  return nullptr;
}
