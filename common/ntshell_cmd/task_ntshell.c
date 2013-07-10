/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     task_ntshell.c
 *
 *        @brief    task for ntshell
 *
 *        @version  0.1
 *        @date     2011/11/14 16:11:49
 *
 *        @author   Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei   2011/11/14    create orignal file
 *  @0.2    Hu Chunxu 2012/3/22     移植到K60
 * =====================================================================================
 */
#include <stdio.h>

#include "common.h"
#include "serial.h"
#include "task_ntshell.h"
#include "ntshell.h"
#include "ntopt.h"
#include "ntlibc.h"

typedef void (* call_func)(int argc, char **argv);

typedef struct ntshell_call {
	const char * name;         /**< call's name */
	call_func	func;
} NTSHELL_CALL;


static NTSHELL_CALL	ntshell_call_table[TNUM_NTSHELL_CALL];
static ntshell_t ntshell;

static int func_read(char *buf, int cnt)
{
    return serial_rea_dat(NTSHELL_PORTID, (char_t *)buf, cnt);
}

static int func_write(const char *buf, int cnt)
{
    return serial_wri_dat(NTSHELL_PORTID, (const char_t *)buf, cnt);
}

static int func_cb(const char *text)
{
    /**
     * Here is the user defined command interfaces.
     */
	int i;
	char buf[NTOPT_MAXLEN_ARGV];

	if (ntopt_get_text(text, 0, buf, sizeof(buf)) != 0)
	{
		for ( i = 0; i < TNUM_NTSHELL_CALL; i++) {
			/* serach call's name in ntshell_call_table */
			if (ntlibc_strcmp(ntshell_call_table[i].name, buf) == 0) {
				ntopt_parse(text, ntshell_call_table[i].func);
				return 0;
			}
		}

		puts("No such a command\n");
	}
    return 0;
}

/**
 *    @brief register a function call in ntshell
 *
 *    @param   name   function call's name
 *    @param   call   function call's address
 *
 *    @return  value  call number(>=0)   -1	fail
 */
int ntshell_register(const char *name, call_func call)
{
	int i;

	for ( i = 0; i < TNUM_NTSHELL_CALL; i++) {
		if (ntshell_call_table[i].name == 0 && ntshell_call_table[i].func == 0) {
			ntshell_call_table[i].name = name;
			ntshell_call_table[i].func = call;
			return i;
		}
	}

	return -1; /* there is no space in ntshell_call_table */
}

void task_ntshell(intptr_t exinf)
{
	serial_ctl_por(NTSHELL_PORTID, (IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV));

    ntshell_execute(&ntshell,func_read, func_write, func_cb);
}
