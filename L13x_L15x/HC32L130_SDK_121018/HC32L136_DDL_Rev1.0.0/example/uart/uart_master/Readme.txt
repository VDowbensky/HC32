﻿================================================================================
                                样例使用说明
================================================================================
版本历史 
日期        版本    负责人         IAR     MDK   描述
2018-05-04  0.1     CJ             7.70    5.16 first version
================================================================================
功能描述
================================================================================
本样例主要涉及串口主机数据发送功能

说明：
配置PA02、PA03为UART收发端口
配置波特率9600bps
使能UART收发功能
================================================================================
测试环境
================================================================================
测试用板:
HC32L136_STK
---------------------
（需要填）

辅助工具:
---------------------
杜邦线

辅助软件:
---------------------

================================================================================
使用步骤
1、用杜邦线将板子1的RX和TX分别与板子2的TX和RX连接，共电源共地
2、分别烧录主从机代码
3、仿真进入从机板子，在代码最后设定断点
4、复位主机板子从而重新发送数据
5、仿真观察从机是否正常接收数据0xaa，0x55
6、仿真观察主机是否正常接收数据0xaa，0x55

================================================================================

================================================================================
注意：
================================================================================
无
================================================================================
