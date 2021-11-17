/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			gimbal.c/h
 *
 * @brief 		云台初始化设置
 *
 * @note  		
 * @history
 *
 @verbatim
 ==============================================================================


==============================================================================
 @endverbatim
 *****************************东莞理工学院ACE实验室 *****************************
 */
 
#include "gimbal_app.h"
#include "SysInit.h"
#include "main.h"


osThreadId GIMBALTASKHandle;


/**
  * @brief     云台初始化
  * @param[in]  
  * @retval     void
*/

void gimbal_app_init(void)
{


  osThreadDef(GIMBALTASK, GIMBAL_TASK, osPriorityRealtime, 0, 200);
  GIMBALTASKHandle = osThreadCreate(osThread(GIMBALTASK), NULL);

}
