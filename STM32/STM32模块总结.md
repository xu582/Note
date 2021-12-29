# STM32模块总结

## 普通IO传感器类

### 1. 外设总结学习

1. GPIO
   - 是通用输入输出端口的简称，就是STM32可控制的引脚，STM32芯片的GPIO引脚与外部设备连接起来，从而实现与外部通讯、控制以及数据采集。
   - GPIO引脚接入到继电器或者三极管，就可以通过继电器或三极管控制外部大功率电路的通断。

2. 中断
   - 引起中断的事件
   - 中断优先级控制
   - 中断响应过程
     1. 保护断点，即保存下一条将要执行的指令的地址，就是把这个地址送入堆栈
     2. 寻找中断入口，根据不同中断源产生的中断，找到相对应的入口地址
     3. 执行中断处理程序
     4. 中断返回，中断事件处理完成之后要回到堆栈中保存的指令的地址继续执行的程序

3. 定时器
   - 能够定时、计数的器件称之为定时器
   - 基本定时器的主要功能就是定时，有各自的可编程预分频器驱动
   - 输入捕获/输出比较，产生PWM波形功能
   - 输出互补带死区的信号，一级刹车功能
   - 看门狗定时器能用于检测程序是否故障，在超出一定时间程序跑飞或者CPU不工作了会产生一次系统复位或者中断（只有窗口看门狗有中断功能）
   - 系统滴答定时器

### 2. 传感器与单片机IO电平匹配说明

1. STM32
   - 电源：在所有的STM32开发板中引出的电源均为3.3V和5V接口
   - IO引脚：在所有的STM32开发板中的I/O引脚作为普通输出时，均为3.3V

### 3. 普通IO反应模块程序流程思路

1. 继电器(参考[https://www.zhihu.com/question/37052790](https://www.zhihu.com/question/37052790))
   - 编写继电器驱动时，考虑到更改硬件环境的情况。建议把继电器检测引脚相关的宏定义到头文件
   - 程序运行第一件事，就是将用到的外设初始化。

2. 光敏
   - 光敏电阻，就是遇到不同的光强，电阻的阻值不同

### 4. 单总线协议模块 

1. DS18B20
   - DS18B20是常用的数字温度传感器，其输出的是数字信号，具有体积小，硬件开销低，抗干扰能力强，精度高的特点（参考[https://baike.baidu.com/item/DS18B20/10295269?fr=aladdin](https://baike.baidu.com/item/DS18B20/10295269?fr=aladdin)）

2. DHT11温湿度传感器
   - DHT11是一款有已校准数字信号输出的温湿度传感器（参考[https://baike.sogou.com/v73984313.htm?fromTitle=DHT11](https://baike.sogou.com/v73984313.htm?fromTitle=DHT11)）

3. 1838红外遥控模块
   - 红外遥控是一种无线、非接触控制技术，具有抗干扰能力强，信息传输可靠，功耗低，成本低，易实现等显著优点(参考[红外遥控简介](https://baike.baidu.com/item/%E7%BA%A2%E5%A4%96%E9%81%A5%E6%8E%A7/10186908?fr=aladdin))

## 串口通讯

### 1. 串口外设

1. 串口通讯协议
   - 串口通讯(Serial Communication)是一种设备之间非常常用的串行通讯方式，因为它简单便捷，大部分电子设备都支持该通讯方式，电子工程师在调试设备时也经常使用该通讯方式输出调试信息。芯片被分为内核层和片上外设；STM32 HAL库则是在寄存器与用户代码之间的软件层。对于通讯协议，分为物理层和协议层，物理层规定通讯系统中具有机械、电子功能部分的特性，确保原始数据在物理媒体的传输。协议层主要规定通讯逻辑，统一收发双方的数据打包、解包标准。
   - 物理层 ：
     - 电平标准
     - RS-232信号线
   - 协议层
     - 波特率
     - 通讯起始和停止信号
     - 有效数据
     - 数据校验

2. USART

### 2. 多个串口使用

- 每一类STM32单片机上都有多个串口，每个串口独立工作，比如可以用串口2与要控制的模块连接，将收到的数据通过串口1发送到电脑或者另一块单片机，还有就是printf功能，他可以映射到任何一个串口上

```C
//重定义fputc函数，方便使用printf
 int fputc(int Data, FILE *f)
 {
     while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));       //USART_GetFlagStatus：得到发送状态位
                                                               //USART_FLAG_TXE:发送寄存器为空 1：为空；0：忙状态
     USART_SendData(USART1,Data);                              //发送一个字符

     return Data;                                              //返回一个值
 }
```

- 在我们使用printf函数的时候，首先必须重定义fputc函数，在这个函数中，实现数据的发送，然后在USART_SendData(USART1,Data);中选择需要的串口。一般选择串口1，所以这种情况下，使用printf()函数会打印到串口1.也可以使用串口2的printf(),配置和串口1是一样的
  1. 配置usart2的串口设置，使能管脚、串口2时钟
  2. 勾选usb micro lib
  3. 添加头文件 #include<stdarg.h> ,编写USART2的printf函数

```C
void USART2_printf (char *s, ...) // 形参 “ ... ” 为可变参数。
 {
     char buffer[BUFFER_LEN+1];  // BUFFER_LEN 缓冲区长度
     u8 i = 0;

     va_list arg_ptr;
     va_start(arg_ptr, s);
     vsnprintf(buffer, BUFFER_LEN+1, s, arg_ptr);
     while ((i < BUFFER_LEN) && buffer)
     {
             USART_SendData(USART2, (u8) buffer[i++]);
             while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
     }
     va_end(arg_ptr);
 }
```