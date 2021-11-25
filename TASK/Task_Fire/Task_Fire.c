/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       fire_task.c/h
  * @brief      火控任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#include "Task_Fire.h"
#include "SysInit.h"
/* extern  fifo_rx_def fifo_usart2_rx;
static fifo_rx_def *pfifo_upper_computer = &fifo_usart2_rx;
	 uint8_t buff_read[128];
	 uint8_t buff_tx[128] = {0x01,0x02,0x03,0x04}; */


void Fire_Task(void *pvParameters)
{
	    //加载时间
   vTaskDelay(FIRE_TASK_INIT_TIME);
	
	while(1)
	{
		/*  心跳任务 */
		LEDE3 = 0;
		

/* 	usart2_dma_send(buff_read, usart2_read (buff_read , 128));
 */		
		vTaskDelay(FIRE_CONTROL_TIME_MS); 

	}

}
