﻿================================================================================
                                样例使用说明
================================================================================
版本历史 
日期        版本    负责人         IAR     MDK   描述
2018-04-18  0.1     CJ             7.70    5.16 first version
================================================================================
功能描述
================================================================================
本样例主要涉及I2C读写E2PROM功能

说明：
配置PA11、PA12为SCL SDA 
内部4M pclk时钟
使能波特率100k
I2C模块使能
================================================================================
测试环境
================================================================================
测试用板:
HC32L136_STK
---------------------
（需要填）

辅助工具:
---------------------

辅助软件:
---------------------
串口调试工具
================================================================================
使用步骤
1、PA11、PA12端口与E2PROM的SDA和SCL正确连接
2、重新编译此代码
3、烧录代码
4、数据正常写入E2
5、读出数据仿真查看是否与写入相同
================================================================================

================================================================================
注意：
================================================================================

================================================================================
