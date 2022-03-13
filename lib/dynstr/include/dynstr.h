#pragma once

#include <stdbool.h>
#include <stdlib.h>

size_t getCap(size_t len);

typedef struct Str {
    size_t cap, len;
    char *arr;
} String;

String *new_stringa(const char *str);
String *new_stringc(const char ch);
String *new_stringo(const String *str);
String *new_stringf(const char *fn);
String *new_string();

bool str_resize(String *str, size_t size);

bool str_append(String *dest, const String *str);
bool str_appends(String *dest, const char *str);
bool str_pushc(String *dest, const char ch);

char str_at(const String *str, size_t i);

void del_string(String *str);
