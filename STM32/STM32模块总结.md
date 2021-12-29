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

### 3. ESP8266模块

1. ESP8266简介
   - ESP8266是串口型WiFi，速度比较低，不能用来传输图像或者视频这些大容量的数据，主要应用于数据量传输比较少的场合，比如温湿度信息，一些传感器的开关等。(参考[https://doc.embedfire.com/products/link/zh/latest/module/wifi/esp8266.html?highlight=esp8266](https://doc.embedfire.com/products/link/zh/latest/module/wifi/esp8266.html?highlight=esp8266))

2. ESP8266的AT指令
   - AT指令是应用于终端设备与PC应用之间的连接与通信的指令，说白了，AT指令就是大家定义好的，能表达特殊意义的字符串，每条AT命令中只能包含一条AT指令，就比如说A发送：“吃饭了”，B就会回复：“好的”

3. AP/STA模式
   - AP: 即无线接入点，是无线网络的中心节点，我们常使用的路由器就是一个AP。ESP8266可以工作在AP模式，设置为AP模式、开启热点之后就可以用手机来连接ESP8266
   - STA: 每一个连接到无线网络的终端都可以理解为一个STA。ESP8266也可以工作在STA模式，配置为STA模式之后就可以连接路由器的WiFi

4. TCP/UDP/透传
   1. TCP，是一种面向连接的，提供可靠交付服务和全双工通信的，基于字节流的端到端的传输层通信协议
      - TCP在传输数据之前必须建立连接，数据传输结束后要释放连接
      - 每一条TCP连接只能有2个端点，故TCP不提供广播或多播服务
      - TCP提供可靠交付，通过TCP连接传输的数据，无差错、不丢失、不重复、并且安序到达
      - TCP是面向字节流的，虽然应用进程和TCP的交互是一次一个数据块(大小不等)，但TCP把应用程序交下来的数据看成是一连串的无结构的字节流。TCP并不知道到所传输的字节流的含义

   2. UDP，是一种无连接的，尽最大努力交付的，基于报文的端到端的传输层通信协议
      - UDP，在发送数据之前不需要建立连接
      - UDP不保证可靠交付，主机不需要位置复杂的连接状态
      - UDP是面向报文的。UDP对应用层交下来的报文，既不合并，也不拆分，而是保留这些报文的的边界，即应用层交给UDP多长的报文，UDP就照样发送，即一次发送一个报文。在接收端，UDP一次交付一个完整的报文
      - UDP没有拥塞控制，网络出现的拥塞不会使源主机的发送速率降低
      - UDP支持一对一、一对多、多对一和多对多的交互通信
      - UDP的首部开销小，只有8个字节，比TCP的20个字节的首部要短

   3. 透传，即透明传输，是指在传输中不管传输的内容是什么，只关心传输时的源地址和目标地址，对数据内容不做任何改变
   4. 固件，固件是写入存储器中的程序，在单片机就是写到Flash中的程序

5. 连接方式
6. ESP8266 AT测试
7. WIFI透传
8. 向电脑网络助手上传DHT11温湿度
9. 手机APP控制

### 4. HC05模块

[https://doc.embedfire.com/module/module_tutorial/zh/latest/Module_Manual/port_class/hc05.html](https://doc.embedfire.com/module/module_tutorial/zh/latest/Module_Manual/port_class/hc05.html)

1. 简介
   - 采用蓝牙2.0协议，可与任何版本的蓝牙兼容通讯， 包括与具有蓝牙功能的电脑、蓝牙主机、手机、PDA、PSP等终端配对，可实现串口透传功能。 驱动HC05模块时只需要使用TTL电平标准的串口即可(5V/3.3V电压均可)，支持的波特率范围为4800~1382400，非常适合用于单片机系统扩展蓝牙特性。(参考[https://doc.embedfire.com/products/link/zh/latest/module/bluetooth/hc05.html](https://doc.embedfire.com/products/link/zh/latest/module/bluetooth/hc05.html))

### 5. GPS模块

[https://doc.embedfire.com/module/module_tutorial/zh/latest/Module_Manual/port_class/gps.html](https://doc.embedfire.com/module/module_tutorial/zh/latest/Module_Manual/port_class/gps.html)

[https://doc.embedfire.com/products/link/zh/latest/module/gps/beidou_atgm332d.html?highlight=gps。](https://doc.embedfire.com/products/link/zh/latest/module/gps/beidou_atgm332d.html?highlight=gps。)

## SPI通讯类模块

1. 协议
   - SPI协议是由摩托罗拉公司提出的通讯协议(Serial Peripheral Interface)，即串行外围设备接口， 是一种高速全双工的通信总线。它被广泛地使用在ADC、LCD等设备与MCU间，要求通讯速率较高的场合。
   - 物理层(3条总线及片选)
     1. SS(Slave Select)
     2. SCK
     3. MOSI
     4. MISO
   - 与 I2C 的类似，SPI 协议定义了通讯的起始和停止信号、数据有效性、时钟同步等环节
     - 这是一个主机的通讯时序。NSS、SCK、MOSI 信号都由主机控制产生，而 MISO 的信号由从机产生， 主机通过该信号线读取从机的数据。MOSI 与 MISO 的信号只在 NSS 为低电平的时候才有效， 在 SCK 的每个时钟周期 MOSI 和 MISO 传输一位数据

2. STM32的SPI特性及架构
   - 与 I2C 外设一样，STM32 芯片也集成了专门用于 SPI 协议通讯的外设
   - STM32的SPI外设可用作通讯的主机及从机，支持最高的SCK时钟频率为fpclk/2 (STM32F103型号的芯片默认f:sub:pclk1为72MHz，fpclk2为36MHz)， 完全支持SPI协议的4种模式，数据帧长度可设置为8位或16位，可设置数据MSB先行或LSB先行。 它还支持双线全双工(前面小节说明的都是这种模式)、双线单向以及单线模式。其中双线单向模式可以同时使用MOSI及MISO数据线向一个方向传输数据，可以加快一倍的传输速度。而单线模式则可以减少硬件接线，当然这样速率会受到影响

3. 软件SPI与硬件SPI区别
   - 软件SPI需要用IO口模拟时序，这个模拟过程全部由CPU完成，为了能稳定的存入数据，可能插入软件延时，这个时间在读取数据量小的情况下不明显， 但是基本上你在读取过程中其他非中断、非异常程序是无法得到执行的
   - 硬件SPI数据存储过程是不需要CPU参与的，程序中配置好SPI的访问时序，开启中断，CPU就可以在中断函数中搬移数据，省下了软件模拟IO的存取时间