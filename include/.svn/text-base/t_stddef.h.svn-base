/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     t_stddef.h
 *
 *        @brief    常用类型定义
 *
 *        @version  0.1
 *        @date     2011/3/21 21:32:45
 *
 *        @author:  Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2011/3/21   create orignal file
 * =====================================================================================
 */

#ifndef  T_STDDEF_INC
#define  T_STDDEF_INC

#include <stdint.h>

/**
 *  常见的数据类型
 */
typedef int		    bool_t;		/**< bool布尔值 */
typedef unsigned char	char_t;		/**< 无符号字符类型 */

typedef signed int		int_t;		/**< 自然大小的符号整数（32位） */
typedef unsigned int	uint_t;		/**< 自然大小的无符号整数（32位） */

typedef signed long		long_t;		/**< 有符号长整形数 */
typedef unsigned long	ulong_t;	/**< 无符号长整形数 */


typedef volatile int8_t               vint8_t;
typedef volatile uint8_t              vuint8_t;
typedef volatile int16_t              vint16_t;
typedef volatile uint16_t             vuint16_t;
typedef volatile int32_t              vint32_t;
typedef volatile uint32_t             vuint32_t;

typedef int_t			FN;			/**< 功能代码 */
typedef	 int_t			ER;			/**< 错误代码 */
typedef	 int_t			ID;			/**< ID号 */
typedef uint_t			ATR;		/**< 对象的属性 */
typedef	 uint_t			STAT;		/**< 对象的状态 */
typedef	 uint_t			MODE;		/**< 运行模式 */
typedef	 int_t			PRI;		/**< 优先级 */
typedef	 uintptr_t		SIZE;		/**< 数据存储大小 */
typedef int_t          PIN;        /**< 引脚 */
typedef int_t          PORT;       /**< 端口 */

typedef	 int_t			TMO;		/**< 超时时间 */
typedef	 uint_t			RELTIM;		/**< 相对时间 */
typedef	 ulong_t		SYSTIM;		/**< 系统时间 */
typedef	 ulong_t		SYSUTM;		/**< 时间效率 */

typedef	void		   (*FP)(void); /**< 启动程序地址 */

typedef int_t			ER_BOOL;	/**< 一个布尔值的错误代码 */
typedef	 int_t			ER_ID;		/**< 错误ID号  */
typedef	 int_t			ER_UINT;	/**< 无符号整数错误代码 */

/**
 *  常量定义
 */
#ifndef NULL
#define NULL            0           /**< 空指针 */
#endif /* NULL */

#ifndef TRUE
#define TRUE            1           /**< 真 */
#endif /* TRUE */

#ifndef FALSE
#define FALSE           0           /**< 假 */
#endif /* FALSE */

#define HIGH_POWER      1          /**< 高电平 */
#define LOW_POWER       0          /**< 低电平 */

#define OUT_PUT         1           /**< 输出 */
#define IN_PUT          0           /**< 输入 */


#define E_OK		    0			/**< 正常返回 */

/**
 *  主要的错误代码
 */
#define E_SYS		(-1) 		/**< 系统错误 */
#define E_NOSPT		(-2) 		/**< 不支持的功能 */
#define E_PAR		(-3) 		/**< 参数错误 */
#define E_ID		(-4) 		/**< ID错误 */
#define E_ILUSE		(-5) 		/**< 未授权的服务 */
#define E_PIN		(-6) 	    /**< 管脚设置错误 */
#define E_INIT		(-7) 	    /**< 初始化失败*/
#define E_DROUT		(-8) 	    /**< 数据接收超时 */
#define E_DSOUT		(-9) 	    /**< 数据发送超时 */
#define E_OBJ		(-10) 	    /**< 数据发送超时 */
#define E_CHN      (-11)       /**< 通道错误 */
#define E_MOD      (-12)       /**< 模块错误 */

/**
 * ERCD用以从主错误码(mercd)和子错误码(sercd)合成错误码
 */
#define  ERCD(mercd, sercd)

/**
 * MERCD用以从错误码(ercd)中分离主错误码
 */
#define  MERCD(ercd)

/**
 *SERCD用以从错误码(ercd)中分离子错误码.
 */
#define  SERCD(ercd)


#endif   /* ----- #ifndef T_STDDEF_INC  ----- */




