/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       chassis_task.c/h
  * @brief      完成底盘控制任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#include "Task_Chassis.h"
#include "SysInit.h"


extern  fifo_rx_def fifo_usart2_rx;
static fifo_rx_def *pfifo_upper_computer = &fifo_usart2_rx;
static	 uint8_t buff_read[128];


void Chassis_Task(void const * argument)
	{
	    //空闲一段时间
    vTaskDelay(CHASSIS_TASK_INIT_TIME);	
		
		while(1)
		{
			LEDE1 = 0;
			
//			fifo_read_buff(pfifo_upper_computer,buff_read,20);
			
			CAN_Send_Msg(1000,0,0,0);
			//检测周期
		vTaskDelay(CHASSIS_CONTROL_TIME);
		
		}                                                                                                                            
		
	}



	