/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			can_1_receive.c/h
 *
 * @brief 	滤波器初始化以及底盘云台，can1接收
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


#include "CAN_1_Receive.h"
#include "main.h"
#include "SysInit.h"

extern CAN_HandleTypeDef hcan1;                     // 句柄

//void (*CAN1_receive_callback)(CAN_HandleTypeDef *);


/*--------------------变量-----------------------*/
//申明底盘电机变量 static
motor_measure_t motor_chassis[4];
//申明拨弹电机变量
static motor_measure_t motor_fire;
//申明pitch轴电机变量
 motor_measure_t motor_pitch;

//电机数据读取
#define get_motor_M3508(ptr, rx_message)                                                  \
    {                                                                                     \
        (ptr)->position = (uint16_t)((rx_message)->Data[0] << 8 | (rx_message)->Data[1]); \
        (ptr)->speed = (uint16_t)((rx_message)->Data[2] << 8 | (rx_message)->Data[3]);    \
    }


//返回底盘电机变量地址，通过指针方式获取原始数据
const motor_measure_t *get_Chassis_Motor_Measure_Point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];  //(i & 0x03)
}



/**
	* @brief		滤波器配置
	* @param		none
	*	@retval		none
  */

void CAN1_filter_config(void)
{
    CAN_FilterTypeDef CAN1_FIilter_InitStruct;

    CAN1_FIilter_InitStruct.FilterActivation = ENABLE;									//开启滤波器
    CAN1_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //掩码模式
    CAN1_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32位工作
    CAN1_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN1_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN1_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN1_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN1_FIilter_InitStruct.FilterBank = 0;
		CAN1_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN1_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//指定接收邮箱
    HAL_CAN_ConfigFilter(&hcan1, &CAN1_FIilter_InitStruct);							//根据指定配置CAN接收过滤器
    HAL_CAN_Start(&hcan1);																							//开启can1
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);	//启动中断

}


/**
	* @brief		HAl库can1的回调函数
	* @param		传入参数： CAN的句柄
	* @retval   none
  */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
/*     CAN_RxHeaderTypeDef	Rxmessage;	
 */    
    if(hcan == &hcan1)
				CAN1_chassis_receive(hcan);
		if(hcan == &hcan2)
				CAN2_chassis_receive(hcan);
//			if(CAN1_receive_callback != NULL)
//					CAN1_receive_callback(hcan)	;               
		
	

}


/*************************************can1接收处理函数*************************************/

 void CAN1_chassis_receive(CAN_HandleTypeDef *hcan)
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
					motor_chassis[0].position 		 = (uint16_t)(Rx_Data[0] << 8) + Rx_Data[1];
					motor_chassis[0].speed   			 = (uint16_t)(Rx_Data[2] << 8) + Rx_Data[3];
					motor_chassis[0].given_current = (uint16_t)(Rx_Data[4] << 8 | Rx_Data[5]);
					motor_chassis[0].temperate		 =	Rx_Data[6];
					
//					Motor_Actual_Position(&motor_chassis[1],CHASSIS_RATIO,8192);

            break;
        }
				
				case 0x01:
				{
					
					motor_pitch.position = ((uint16_t)(Rx_Data[6] << 24) | (uint16_t)(Rx_Data[5] << 16) | (uint16_t)(Rx_Data[4] << 8) | (uint16_t)(Rx_Data[3] ));
					
				if(motor_pitch.position>=0&&motor_pitch.position<=150)
					{
						motor_pitch.position +=884;
					}
				else
						motor_pitch.position -= 140;
            motor_pitch.actual_Position = motor_pitch.position;   //实际值减去中间值
            motor_pitch.pitch_angle = -(motor_pitch.actual_Position * 360 / 1024 / PITCH_GR - Pitch_Middle_Angle);
            break;
				
				}
			 default:
        {
            break;
        }
			
		}
	}


}
