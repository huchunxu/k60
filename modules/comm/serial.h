/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     serial.h
 *
 *        @brief    带双环缓冲的串行口通用模块实现
 *
 *        @version  0.1
 *        @date     2012/3/14 15:20:10
 *
 *        @author:  Ren Wei , renweihust@gmail.com
 *//* ==================================================================================
 *  @0.1    Ren Wei   2012/3/14 create orignal file
 *  @0.2    Hu Chunxu 2012/3/21 成功移植到K60上
 * =====================================================================================
 */

#ifndef SERIAL_H
#define SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  查询串行口状态的专用数据结构
 */
typedef struct {
    uint_t      reacnt;         /**< 接收缓存中的数据数 */
    uint_t      wricnt;         /**< 发送缓存中的数据数 */
} T_SERIAL_RPOR;

/**
 *  串行口通用模块初始化函数
 */
extern void     serial_initialize(intptr_t exinf);

/**
 * 从串行口发送缓存中取出尚未发送的数据
 */
extern bool_t   serial_get_chr(ID portid, char_t *p_c);

/**
 *  串行口通用模块服务调用
 */
extern ER       serial_opn_por(ID portid);
extern ER       serial_cls_por(ID portid);
extern ER_UINT  serial_rea_dat(ID portid, char_t *buf, uint_t len);
extern ER_UINT  serial_wri_dat(ID portid, const char_t *buf, uint_t len);
extern ER       serial_ctl_por(ID portid, uint_t ioctl);
extern ER       serial_ref_por(ID portid, T_SERIAL_RPOR *pk_rpor);

uint8_t serial_get_char(ID portid);

/**
 * 串行口通用模块控制代码宏定义
 *
 */
#define IOCTL_NULL  0U          /**< 空 */
#define IOCTL_ECHO  0x0001U     /**< 接收回显 */
#define IOCTL_CRLF  0x0010U     /**< (\n)LF之前附加(\r)CR */
#define IOCTL_FCSND 0x0100U     /**< 发送流控制 */
#define IOCTL_FCANY 0x0200U     /**< 接收到任意字符后都要重新开始发送 */
#define IOCTL_FCRCV 0x0400U     /**< 接收流控制 */

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_H */
