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

	
void Chassis_Task(void const * argument)
	{
	    //����һ��ʱ��
    vTaskDelay(CHASSIS_TASK_INIT_TIME);	
		
		while(1)
		{
			
			//�������
		vTaskDelay(CHASSIS_CONTROL_TIME);

		}
		
	}


	