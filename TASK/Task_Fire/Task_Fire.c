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


void Fire_Task(void *pvParameters)
{
	    //加载时间
   vTaskDelay(FIRE_TASK_INIT_TIME);
	
	while(1)
	{
		
				        vTaskDelay(FIRE_CONTROL_TIME_MS); 

	}

}
