﻿================================================================================
                                样例使用说明
================================================================================
版本历史 
日期        版本    负责人         IAR     MDK   描述
2018-05-04  0.1     CJ             7.70    5.16 first version
================================================================================
功能描述
================================================================================
本样例主要展示SPI初始化以及主机模式发送和接收功能。
说明：
    

================================================================================
测试环境
================================================================================
测试用板:
---------------------
HC32L136_STK

辅助工具:
---------------------
示波器
电源

辅助软件:
---------------------
无

================================================================================
使用步骤
================================================================================
1）打开工程编译
2）连接两块STK板，与从机接口连线正确
3）运行程序，在live watch（IAR）或者watch(Keil)窗口观察u8Recvdata[]接收数据与发送数据u8Senddata[]是否一致。
4）示波器观测PA11、PA12、PA15、PB03可以观察到相应的波形
================================================================================
注意
================================================================================
1）主机SPI0 相应的引脚设置
PA11:MISO
PA12:MOSI
PA15:CS
PB03:SCK
2）从机SPI0相应引脚配置

PA11:MISO
PA12:MOSI
PA03:CS
PB03:SCK
================================================================================
