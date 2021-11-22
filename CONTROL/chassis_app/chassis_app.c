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
static CAN_TxHeaderTypeDef Txmessage;				//发送的信息
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


/**
  * @brief      底盘初始化
  * @param[in]  
  * @retval     void
*/

void chassis_app_init(void)
{
	
		/* 遥控初始化 */
	remote_control_init();
	
//	CAN1_receive_callback = CAN1_chassis_receive;

	
	/*  创建底盘任务 */
  osThreadDef(ChassisTask, Chassis_Task, osPriorityRealtime, 0, 200);
  ChassisTaskHandle = osThreadCreate(osThread(ChassisTask), NULL);

}



/**
	* @brief		can1发送函数
	* @param		传入参数： ESC_201~ESC_204 -> 代表同一电调上4个不同ID的电机
	*	@retval		none
  */


void Chassis_CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
{
    uint32_t send_mail_box;							//发送邮箱
    uint8_t Data[8];										//发送数据的数组

    Txmessage.StdId = 0x200;
    Txmessage.IDE = CAN_ID_STD;
    Txmessage.RTR = CAN_RTR_DATA;
    Txmessage.DLC = 8;

    Data[0] = (ESC_201 >> 8);
    Data[1] = ESC_201;
		Data[2] = (ESC_202>>8);
		Data[3] = ESC_202;
		Data[4] = (ESC_203>>8);
		Data[5] = ESC_203;
		Data[6] = (ESC_204>>8);
		Data[7] = ESC_204;

    HAL_CAN_AddTxMessage(&hcan1, &Txmessage, Data, &send_mail_box);			//将一段数据通过 CAN 总线发送
}

void Chassis_CAN2_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
{
    uint32_t send_mail_box;							//发送邮箱
    uint8_t Data[8];										//发送数据的数组

    Txmessage.StdId = 0x200;
    Txmessage.IDE = CAN_ID_STD;
    Txmessage.RTR = CAN_RTR_DATA;
    Txmessage.DLC = 8;

    Data[0] = (ESC_201 >> 8);
    Data[1] = ESC_201;
		Data[2] = (ESC_202>>8);
		Data[3] = ESC_202;
		Data[4] = (ESC_203>>8);
		Data[5] = ESC_203;
		Data[6] = (ESC_204>>8);
		Data[7] = ESC_204;

    HAL_CAN_AddTxMessage(&hcan2, &Txmessage, Data, &send_mail_box);			//将一段数据通过 CAN 总线发送
}

