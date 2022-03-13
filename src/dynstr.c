#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynstr.h"

size_t get_cap(size_t len) {
    len--;
    len |= len >> 1;
    len |= len >> 2;
    len |= len >> 4;
    len |= len >> 8;
    len |= len >> 16;
    len++;
    return len;
}

String *new_stringa(const char *str) {
    String *s = malloc(sizeof(String));
    s->len = strlen(str);
    s->arr = malloc(s->len + 1);  // add a byte for null char
    strcpy(s->arr, str);
    s->cap = get_cap(s->len);
    return s;
}

String *new_stringc(const char ch) {
    String *s = malloc(sizeof(String));
    s->len = 1;
    s->arr = malloc(s->len + 1);  // add a byte for null char
    s->arr[0] = ch;
    s->arr[1] = '\0';
    s->cap = get_cap(s->len);
    return s;
}

String *new_stringo(const String *str) {
    String *s = malloc(sizeof(String));
    s->len = str->len;
    s->arr = malloc(s->len + 1);  // add a byte for null char
    strcpy(s->arr, str->arr);
    s->cap = str->cap;
    return s;
}

String *new_stringf(const char *fn) {
    FILE *fp = fopen(fn, "rb");
    if (fp == NULL) {
        return NULL;
    }
    String *str = malloc(sizeof(String));
    fseek(fp, 0, SEEK_END);
    str->len = ftell(fp);
    str->cap = get_cap(str->len);
    fseek(fp, 0, SEEK_SET);
    str->arr = malloc(str->len);
    if (str->arr == NULL) {
        free(str);
        fclose(fp);
        return NULL;
    }
    fread(str->arr, 1, str->len, fp);
    fclose(fp);
    return str;
}

String *new_string() {
    String *s = malloc(sizeof(String));
    s->len = 0;
    s->arr = malloc(s->len + 1);
    s->arr[0] = '\0';
    s->cap = 1;
    return s;
}

bool str_resize(String *str, size_t size) {
    if (str == NULL) return false;
    str->cap = size;
    str->arr = realloc(str->arr, size);
    return str->arr == NULL;
}

bool str_append(String *dest, const String *str) {
    if (dest == NULL || str == NULL) return false;
    for (size_t i = 0; i < str->len; ++i) {
        bool status = str_pushc(dest, str->arr[i]);
        if (!status) return false;
    }
    return true;
}

bool str_appends(String *dest, const char *str) {
    if (dest == NULL) return false;
    for (size_t i = 0; i < strlen(str); ++i) {
        bool status = str_pushc(dest, str[i]);
        if (!status) return false;
    }
    return true;
}

bool str_pushc(String *dest, const char ch) {
    if (dest == NULL) return false;
    if (dest->cap == dest->len + 1) {
        bool status = str_resize(dest, dest->cap * 2);
        if (!status) return status;
    }
    dest->arr[dest->len++] = ch;
    dest->arr[dest->len] = '\0';
    return true;
}

char str_at(const String *str, size_t i) {
    if (str == NULL || i >= str->len) return '\0';
    return str->arr[i];
}

void del_string(String *str) {
    if (str == NULL) return;
    free(str->arr);
    free(str);
}
