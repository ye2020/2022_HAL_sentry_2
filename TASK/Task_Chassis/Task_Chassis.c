/**
  *****************************��ݸ��ѧԺACEʵ���� *****************************
  * @file       chassis_task.c/h
  * @brief      ��ɵ��̿�������
  * @note       �ϲ��汾
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************��ݸ��ѧԺACEʵ���� *****************************
	*/
	
#include "Task_Chassis.h"
#include "SysInit.h"


extern  fifo_rx_def fifo_usart2_rx;
static fifo_rx_def *pfifo_upper_computer = &fifo_usart2_rx;
static	 uint8_t buff_read[128];


void Chassis_Task(void const * argument)
	{
	    //����һ��ʱ��
    vTaskDelay(CHASSIS_TASK_INIT_TIME);	
		
		while(1)
		{
			LEDE1 = 0;
			
//			fifo_read_buff(pfifo_upper_computer,buff_read,20);
			
			CAN_Send_Msg(1000,0,0,0);
			//�������
		vTaskDelay(CHASSIS_CONTROL_TIME);
		
		}                                                                                                                            
		
	}



	