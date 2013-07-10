欢迎使用华中科技大学瑞萨实验室智能车软件平台！
=============================================

华中科技大学瑞萨实验室智能车软件平台提供一套完整的智能车软件开发库，
包括智能车驱动层、硬件抽象层等完整的代码，同时集成了ntshell、CMSIS
等库函数，提高调试和编程的效率。


本文档包括如下内容：
- 平台概述
- 工程目录
- 更新记录

========
平台概述
========

1、调试软硬件平台说明
---------------------
计算机系统：  ubuntu10.10/ubuntu12.04
开发工具链：  CodeSourcery 2011.03-42
   (https://sourcery.mentor.com/sgpp/lite/arm/portal/release1802)
集成开发环境：Eclipse helios
   (http://www.eclipse.org/downloads/)
调试烧写工具：openocd0.6.0 + openjtag   
单片机：     K60DX256ZVLQ100/k60DN512ZVLQ100   

========
工程目录
========
- k60              (顶层目录)
  - app                (顶层应用函数目录)
  - arch               (目标相关驱动函数)
  - common             (单片机通用模块函数)
  - doc                (doxygen生成文档)         
  - exe                (编译生成可执行文件目录)
  - include            (通用包含)
  - library            (通用代码库)
	- ntshell               (ntshell库)
	- CMSIS_V3P00           (CMSIS库)
	- fatfs                 (fatfs库)
  - modules            (硬件抽象层函数)
  - objs               (编译中间目标文件目录)
  - temp               (临时文件，不编译)
  cs.sh                (vim插件ctags、cscope库的生成脚本)
  k60.Doxyfile         (doxygen配置文件)
  K60_FLASH.ld         (烧写片内flash的链接脚本)
  K60_RAM.ld           (烧写片内ram的链接脚本)
  K60应用笔记.txt       (k60应用笔记)
  Makefile             (工程makefile)
  openocd.cfg          (openocd配置文件)
  readme.txt           (软件平台说明)
  
========
更新记录
========
版本0.1
- 对应K60最小系统板编写了启动代码和中断相关函数
- 提供了片内ram和flash两款链接脚本，方便调试使用
- 移植实现了系统printf函数
- 移植了ntshell，编写相应的调试程序就可以通过串口进行命令控制
- 提供了MCG、FTM、GPIO、UART、FLEXBUS、LPTMR、PIT、SDHC、ADC等模块的驱动程序
- 提供了LED灯、串口等硬件抽象层的代码
- 根据doxygen注释风格规范了代码
- 加入了fatfs，但是没有经过测试，编译可以通过
- 加入了CMSIS库，并且对简单的数学三角函数进行了测试

版本0.2
- 修改了原来程序中的一些错误和不合理的部分
- 对应电磁组的电路板进行了测试，使用到的所有功能都进行了测试
- 对应每一个测试模块写了ntshell命令
- 加入了doxygen文件
- 完成了通用硬件抽象层的代码

版本0.3
- 调整了代码目录，使扩展性和移植性更强
- 加入了SPI驱动，可以进行主从机的初始化和通讯
- 集成了spi模式下的SD卡驱动和fatfs文件系统
- 完成了大部分抽象层的测试函数

版本0.4
- 修改了部分代码的注释，doxygen生成的文档更加完善
- 对应摄像头电路板进行了移植
- 加入了双舵机控制

版本0.5
- 加入了SD卡非文件系统模式的写操作
- 修改了SPI模式下的SD卡速率问题，spi可以达到最快速度25Mbit/s
- 加入了引脚定义头文件t_devdef.h，方便了不同电路板的移植
- 加入了图像的中值滤波算法和动态阈值（大津法）算法