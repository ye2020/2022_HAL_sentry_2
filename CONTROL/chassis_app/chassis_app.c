/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			chassis.c/h
 *
 * @brief 		底盘初始化设置
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

#include "SysInit.h"
#include "main.h"
#include "chassis_app.h"

osThreadId ChassisTaskHandle;

/**
  * @brief      底盘初始化
  * @param[in]  
  * @retval     void
*/

void chassis_app_init(void)
{
	



	
	/*  创建底盘任务 */
  osThreadDef(ChassisTask, Chassis_Task, osPriorityRealtime, 0, 200);
  ChassisTaskHandle = osThreadCreate(osThread(ChassisTask), NULL);

}
