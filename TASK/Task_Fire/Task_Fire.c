/**
  *****************************��ݸ��ѧԺACEʵ���� *****************************
  * @file       fire_task.c/h
  * @brief      �������
  * @note       �ϲ��汾
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************��ݸ��ѧԺACEʵ���� *****************************
	*/
	
#include "Task_Fire.h"
#include "SysInit.h"


void Fire_Task(void *pvParameters)
{
	    //����ʱ��
   vTaskDelay(FIRE_TASK_INIT_TIME);
	
	while(1)
	{
		
				        vTaskDelay(FIRE_CONTROL_TIME_MS); 

	}

}
