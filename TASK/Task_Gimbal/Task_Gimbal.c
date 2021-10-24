/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       fire_task.c/h
  * @brief     	云台任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#include "Task_Gimbal.h"
#include "SysInit.h"


void GIMBAL_TASK(void const * argument)
{
	 vTaskDelay(GIMBAL_TASK_INIT_TIME);

	
	while(1)
	{
		
		
		vTaskDelay(GIMBAL_CONTROL_TIME_MS); //系统延时

	}
	

}
