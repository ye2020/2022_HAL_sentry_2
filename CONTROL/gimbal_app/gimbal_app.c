/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			gimbal.c/h
 *
 * @brief 		��̨��ʼ������
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
 
#include "gimbal_app.h"
#include "SysInit.h"
#include "main.h"


osThreadId GIMBALTASKHandle;


/**
  * @brief     ��̨��ʼ��
  * @param[in]  
  * @retval     void
*/

void gimbal_app_init(void)
{


  osThreadDef(GIMBALTASK, GIMBAL_TASK, osPriorityRealtime, 0, 200);
  GIMBALTASKHandle = osThreadCreate(osThread(GIMBALTASK), NULL);

}
