/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			chassis.c/h
 *
 * @brief 		���̳�ʼ������
 *
 * @note  		
 * @history
 *
 @verbatim
 ==============================================================================


==============================================================================
 @endverbatim
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 */

#include "SysInit.h"
#include "main.h"
#include "chassis_app.h"

osThreadId ChassisTaskHandle;

/**
  * @brief      ���̳�ʼ��
  * @param[in]  
  * @retval     void
*/

void chassis_app_init(void)
{
	



	
	/*  ������������ */
  osThreadDef(ChassisTask, Chassis_Task, osPriorityRealtime, 0, 200);
  ChassisTaskHandle = osThreadCreate(osThread(ChassisTask), NULL);

}
