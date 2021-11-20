/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			can_1_receive.c/h
 *
 * @brief 		包括遥控器初始化，遥控器数据获取，遥控器通讯协议的解析
 *
 * @note  		遥控器数据接收采用串口加DMA的模式
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

static CAN_TxHeaderTypeDef Txmessage;				//发送的信息

/*--------------------变量-----------------------*/
//申明底盘电机变量 static
motor_measure_t motor_chassis[4];
//申明拨弹电机变量
static motor_measure_t motor_fire;
//申明pitch轴电机变量
static motor_measure_t motor_pitch;

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
    CAN1_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//指定接收邮箱
    HAL_CAN_ConfigFilter(&hcan1, &CAN1_FIilter_InitStruct);							//根据指定配置CAN接收过滤器
    HAL_CAN_Start(&hcan1);																							//开启can1
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);	//启动中断

}


/**
	* @brief		can1发送函数
	* @param		传入参数： ESC_201~ESC_204 -> 代表同一电调上4个不同ID的电机
	*	@retval		none
  */

void CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
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
        CAN1_chassis_receive(hcan)	;               



}


/*************************************can1接收处理函数*************************************/

static void CAN1_chassis_receive(CAN_HandleTypeDef *hcan)
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

			 default:
        {
            break;
        }
			
		}
	}


}
