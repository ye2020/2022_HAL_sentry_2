/**
  *****************************��ݸ��ѧԺACEʵ���� *****************************
  * @file       fire_task.c/h
  * @brief     	��̨����
  * @note       �ϲ��汾
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************��ݸ��ѧԺACEʵ���� *****************************
	*/
	
#include "Task_Gimbal.h"
#include "SysInit.h"


void GIMBAL_TASK(void const * argument)
{
	 vTaskDelay(GIMBAL_TASK_INIT_TIME);

	
	while(1)
	{
		
		
		vTaskDelay(GIMBAL_CONTROL_TIME_MS); //ϵͳ��ʱ

	}
	

}
