/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			can_2_receive.c/h
 *
 * @brief 	can2滤波器初始化以及底盘云台，can2接收
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

#include "CAN_2_Receive.h"
#include "SysInit.h"

extern CAN_HandleTypeDef hcan2;
extern CAN_HandleTypeDef hcan1;                     // 句柄



/**
	* @brief		can2滤波器配置
	* @param		none
	*	@retval		none
  */

void CAN2_filter_config(void)
{
    CAN_FilterTypeDef CAN2_FIilter_InitStruct;

    CAN2_FIilter_InitStruct.FilterActivation = ENABLE;									//开启滤波器
    CAN2_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //掩码模式
    CAN2_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32位工作
    CAN2_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterBank = 14;
		CAN2_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN2_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//指定接收邮箱
	
    HAL_CAN_ConfigFilter(&hcan2, &CAN2_FIilter_InitStruct);							//根据指定配置CAN接收过滤器
    HAL_CAN_Start(&hcan2);																							//开启can2
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);	//启动中断

}


 void CAN2_chassis_receive(CAN_HandleTypeDef *hcan)
{
  	CAN_RxHeaderTypeDef	rx_message;															//接收信息结构体

   	uint8_t Rx_Data[8];																					//接收的信息缓存的数组
	
	  if(  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_message, Rx_Data) == HAL_OK)	//读取接收的信息
	{	
    switch (rx_message.StdId)
		{	
                    /*底盘电机*/
        case 0x201:
        {
					break;
				}
			 default:
        {
            break;
        }
			
		}
	}

}		
