/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     task_ntshell.h
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

#ifndef TASK_NTSHELL_H_
#define TASK_NTSHELL_H_

#define TNUM_NTSHELL_CALL	10

#define TSKPRI_NTSHELL 5			            /* priority for ntshell task */
#define STACK_SIZE_NTSHELL  40960	            /* stack size for ntshell task(40k) */
#define NTSHELL_PORTID		UART_NO_GET(UART_NO)	/* serial port id for ntshell task */

#ifndef TOPPERS_MACRO_ONLY
extern void task_ntshell(intptr_t exinf);
extern int ntshell_register(const char *name, void (* call)(int argc, char **argv));
extern int text_puts(const char *str);
#endif	/* TOPPERS_MACRO_ONLY */

#endif /* TASK_NTSHELL_H_ */
