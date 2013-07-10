/**
 * @file ntopt.c
 * @author Shinichiro Nakamura
 * @brief NT-Shell实施模块的选择分析
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

#include "ntopt.h"

#define IS_DELIM(c) \
    (((c) == '\r') || ((c) == '\n') || ((c) == '\t') || ((c) == '\0') || ((c) == ' '))

static int ntopt_get_count(const char *str);
//static char *ntopt_get_text(const char *str, const int n, char *buf, int siz);

int ntopt_get_count(const char *str)
{
    int cnt = 0;
    int wc = 0;
    char *p = (char *)str;
    while (*p) {
        if (!IS_DELIM(*p)) {
            wc++;
            if (wc == 1) {
                cnt++;
            }
        } else {
            wc = 0;
        }
        p++;
    }
    return cnt;
}

char *ntopt_get_text(const char *str, const int n, char *buf, int siz)
{
    int cnt = 0;
    int wc = 0;
    char *p = (char *)str;
    while (*p) {
        if (!IS_DELIM(*p)) {
            wc++;
            if ((wc == 1)) {
                if (cnt == n) {
                    char *des = buf;
                    int cc = 0;
                    while (!IS_DELIM(*p)) {
                        cc++;
                        if (siz <= cc) {
                            break;
                        }
                        *des = *p;
                        des++;
                        p++;
                    }
                    *des = '\0';
                    return buf;
                }
                cnt++;
            }
        } else {
            wc = 0;
        }
        p++;
    }
    return '\0';
}

int ntopt_parse(const char *str, void (*func)(int argc, char **argv))
{
    int argc;
    char argv[NTOPT_MAXCNT_ARGC][NTOPT_MAXLEN_ARGV];
    char *argvp[NTOPT_MAXCNT_ARGC];
    int i;

    argc = ntopt_get_count(str);
    if (NTOPT_MAXCNT_ARGC <= argc) {
        return -1;
    }

    for (i = 0; i < argc; i++) {
        argvp[i] = ntopt_get_text(str, i, argv[i], sizeof(argv[i]));
    }
    func(argc, &argvp[0]);

    return argc;
}

#if 0
#include <stdio.h>
void callback(int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }
}

int main(int argc, char **argv)
{
    char *str1 = "  This is a test.\n   ";
    char *str2 = "This is a test.\t  \r  \n  \t  It's good for you.  \n \n The important thing is LIFE-IS-SO-MUCH-BEAUTIFUL.";
    int i;
    int n1, n2;

    n1 = ntopt_get_count(str1);
    for (i = 0; i < n1; i++) {
        char buf[64];
        printf("%d: %s\n", i, ntopt_get_text(str1, i, buf, sizeof(buf)));
    }
    printf("\n");

    n2 = ntopt_get_count(str2);
    for (i = 0; i < n2; i++) {
        char buf[64];
        printf("%d: %s\n", i, ntopt_get_text(str2, i, buf, sizeof(buf)));
    }
    printf("\n");

    ntopt_parse(str1, callback);
    ntopt_parse(str2, callback);

    return 0;
}
#endif

