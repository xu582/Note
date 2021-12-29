# DAC

## [正点原子 DAC](https://www.bilibili.com/video/BV1Lx411Z7Qa?p=47&spm_id_from=pageDriver)

### 数模转换原理

- STM32的DAC模块（数字/模拟转换模块）是12位数字输入，电压输出型的DAC。DAC可以配置为8位或12位模式，也可以与DMA控制器配合使用。DAC工作在12位模式时，数据可以设置成左对齐或右对齐。DAC模块有2个输出通道，每个通道都有单独的转换器。在双DAC模式下，2个通道可以独立地进行转换，也可以同时进行转换并同步地的更新2个通道的输出。DAC可以通过引脚输入参考电压VREF+以获得跟精确的转换结果。

### STM32的DAC模块主要特点

1. 2个DAC转换器：每个转换器对应1个输出通道
2. 8位或者12位单调输出
3. 12位模式下数据左对齐或者右对齐
4. 同步更新功能
5. 噪声波形生成
6. 三角波形生成
7. 双DAC通道同时或者分别转换
8. 每个通道都有DMA功能

- VDDA和VSSA为DAC模块模拟部分的供电。Vref+则是DAC模块的参考电压。DAC_OUTx就是DAC的输出通道（对应PA4或者PA5引脚）

### DAC转换

- 不能直接对寄存器DAC_DORx写入数据，任何输出到DAC通道x的数据都必须写入DAC_DHRx寄存器（数据实际写入DAC_DHR8Rx、DAC_DHR12Lx、DAC_DHR12Rx、DAC_DHR8RD、DAC_DHR12LD、或者DAC_DHR12RD寄存器）
- 如果没有选中硬件触发（寄存器DAC_CR1的TENx位置‘0’），存入寄存器DAC_DHRx的数据会在一个APB1时钟周期后自动传至寄存器DAC_DORx。如果选中硬件触发（寄存器DAC_CR1的TENx位置‘1’），数据传输在触发发生以后3个APB1时钟周期后完成。
- 一旦数据从DAC_DHRx寄存器装入DAC_DORx寄存器，在经过时间t之后，输出有效，这段时间的长短依电源电压和模拟输出负载的不同会有所变化。
