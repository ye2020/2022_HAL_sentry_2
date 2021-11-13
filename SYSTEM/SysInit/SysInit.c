/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       SysInit.c/h
  * @brief      初始化
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#include "SysInit.h"


/************************* Task ************************/
#include "Task_Chassis.h"

/* ************************freertos******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
	
/* ************************ Hardward ******************** */	
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart2.h"


/* ************************ CONTROL ******************** */	
#include "CAN_1_Receive.h"
#include "RemoteControl.h"


extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;



void System_init(void)
{
	/* 遥控初始化 */
		remote_control_init();
	/*  can滤波配置初始化 */
		CAN1_filter_config();


}

