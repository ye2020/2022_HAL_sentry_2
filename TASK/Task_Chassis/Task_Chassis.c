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

	
void Chassis_Task(void const * argument)
	{
	    //空闲一段时间
    vTaskDelay(CHASSIS_TASK_INIT_TIME);	
		
		while(1)
		{
			
			//检测周期
		vTaskDelay(CHASSIS_CONTROL_TIME);

		}
		
	}


	