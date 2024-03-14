#  *STM32*   : `HAL` 库 `GPIO_WritePin` 点亮LED灯
---
## 一、 `CubeMX`  配置步骤
---

  __我们这个文档主要是讲述如何利用蓝桥杯提供的 ` STM32G431RBT6 `  进行我们的基本操作的实现，下面是我们的详细讲述：__  
>1.	先打开 **CubeMX**  进行型号的选择:
		![CubeMX_MCU](Pictures\Cube_MCU.png"CubeMX_MCU")

>	我们这里选择 `STM32G431RBT6` 版本，这里是我们蓝桥杯的标准MCU


>2. MCU的 **基本引脚** 设置:
>
>	  这一步需要根据比赛或者自己的板子原理图查看需要设置哪几个端口为LED要用到的GPIO_OUTPUT，这块板子要用到的是PC8~PC15与PD2（锁存器）的端口
>	 

>![CubeMX_MCU](Pictures\LED.png "CubeMX_LED")

>	  我们在这里先来设置我们的 高速时钟(HSE) 是打开的状态，选择晶振（Crystal）
>
>![CubeMX_HSE](Pictures\High_Speed_Clock.png "HSE")
>
>	接下来设置 Debug 为: `serial wire` 


>![CubeMX_Debug](Pictures\Debug.png"CubeMX_MCU")

>	接下来我们调整时钟设置，调整参数均已经标注好:
> 

>![CubeMX_Debug](Pictures\Clock_Conf.png"CubeMX_MCU")
>
>	接下来是工程名称和编译器的设置:

>![CubeMX_Debug](Pictures\Project.png"CubeMX_MCU")
>
>	勾选下面的这项：

>![CubeMX_Debug](Pictures\generate_h.png"CubeMX_MCU")
>

---

## 二、ARM-Keil的代码编写与配置：

>	首先，在工程目录下新建一个dsp文件夹存放我们自己写的代码文件（.h/.c）文件
>	

>```c
>// 定义LED.h头文件
>#ifndef _LED_H_
>#define _LED_H_
>void showLEDS(unsigned char show);
>#endif 
>```
>

>```c
>//定义LED.c函数
># include "led.h"
># include <main.h>
>void showLEDS(unsigned char show)
>{
>		HAL_GPIO_WritePin(GPIOC , GPIO_PIN_All, GPIO_PIN_SET);
>		HAL_GPIO_WritePin(GPIOC , show << 8, GPIO_PIN_RESET);
>		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_2, GPIO_PIN_SET);
>		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_2, GPIO_PIN_RESET);
>
>}
>
>```

 **这里我要强调一个很重要的事情**  就是我们的自己写的库文件和头文件不能跟大写字母，不然会找不到我们的文件，并且要在调试的时候把 `dsp` 文件夹添加到工程文件的 `#include path` 当中，不然keil会报错，找不到你写的路径。

>```c
>// main.c文件要添加你自己写的led.h头文件
>/* USER CODE END Header */
>/* Includes ----------------------------------------------------------->-------*/
>#include "main.h"
>#include "gpio.h"
>
>/* Private includes --------------------------------------------------->-------*/
>/* USER CODE BEGIN Includes */
>#include "led.h"
>/* USER CODE END Includes */
>
>```
>

>```c
>// 在GPIO端口的初始化不要忘记（由于在高电平下熄灭，所以传入0x00进行熄灭）
> MX_GPIO_Init();
>/* USER CODE BEGIN 2 */
>		showLEDS(0x00);
> /* USER CODE END 2 */
>/* USER CODE BEGIN WHILE */
> while (1)
>  {
>    /* USER CODE END WHILE */
>			showLEDS(0x01);
>			HAL_Delay(500);
>			showLEDS(0x02);
>			HAL_Delay(500);
>			showLEDS(0x04);
>			HAL_Delay(500);
>   /* USER CODE BEGIN 3 */
>  }
> /* USER CODE END 3 */
>
>```
>
***至此，我们已经可以实现在 `STM32G431RBT6` MCU的跑马灯效果了***