================================================================================
                                样例使用说明
================================================================================
版本历史 
日期        版本    负责人         IAR     MDK         描述
2019-04-22  1.0     Husj           7.70    5.26       first version
================================================================================
功能描述
================================================================================
本样例主要展示ADC 被TIM4触发启动顺序扫描采样，TIM4的触发频率是1K


================================================================================
测试环境
================================================================================
测试用板:
---------------------
HC32LF07x_EVB

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
1）打开工程编译并运行
2）Timer4每隔1ms触发ADC采样
3）在ADC中断内读取转换值



================================================================================
注意
================================================================================

================================================================================
