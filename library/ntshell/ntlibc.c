/**
 * @file ntlibc.c
 * @author Shinichiro Nakamura
 * @brief NT-Shellで用いる小規模libcの実装。
 */

/*
 * ===============================================================
 *  Natural Tiny Shell (NT-Shell)
 *  Version 0.0.6
 * ===============================================================
 * Copyright (c) 2010-2011 Shinichiro Nakamura
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * ===============================================================
 */

#include "ntlibc.h"

size_t ntlibc_strlen(const char *s)
{
    const char *p = s;
    int cnt = 0;
    while (*p) {
        cnt++;
        p++;
    }
    return cnt;
}

char *ntlibc_strcpy(char *des, const char *src)
{
    char *d = des;
    const char *s = src;
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return des;
}

char *ntlibc_strcat(char *des, const char *src)
{
    char *d = des;
    const char *s = src;
    while (*d) {
        d++;
    }
    while (*s) {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return des;
}

int ntlibc_strcmp(const char *s1, const char *s2)
{
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;
    while (*p1 || *p2) {
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        p1++;
        p2++;
    }
    if (*p1 == *p2) {
        return 0;
    } else {
        return (*p1 < *p2) ? -1 : 1;
    }
}

int ntlibc_strncmp(const char *s1, const char *s2, size_t n)
{
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;
    size_t len = 0;
    while (*p1 || *p2) {
        if (n <= len) {
            break;
        }
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }
        p1++;
        p2++;
        len++;
    }
    return 0;
}

#if 0
#include <stdio.h>
int main(void);
int main(void) {
    char *str_a = "That";
    char *str_b = "The";
    printf("strcmp(%s,%s) = %d, %d\n",
            str_a, str_b,
            strcmp(str_a, str_b),
            ntlibc_strcmp(str_a, str_b));
    printf("strncmp(%s,%s,2) = %d, %d\n",
            str_a, str_b,
            strncmp(str_a, str_b, 2),
            ntlibc_strncmp(str_a, str_b, 2));
    printf("strncmp(%s,%s,3) = %d, %d\n",
            str_a, str_b,
            strncmp(str_a, str_b, 3),
            ntlibc_strncmp(str_a, str_b, 3));
    return 0;
}
#endif

