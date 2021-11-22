/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			can_1_receive.c/h
 *
 * @brief 	�˲�����ʼ���Լ�������̨��can1����
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


#include "CAN_1_Receive.h"
#include "main.h"
#include "SysInit.h"

extern CAN_HandleTypeDef hcan1;                     // ���

//void (*CAN1_receive_callback)(CAN_HandleTypeDef *);


/*--------------------����-----------------------*/
//�������̵������ static
motor_measure_t motor_chassis[4];
//���������������
static motor_measure_t motor_fire;
//����pitch��������
 motor_measure_t motor_pitch;

//������ݶ�ȡ
#define get_motor_M3508(ptr, rx_message)                                                  \
    {                                                                                     \
        (ptr)->position = (uint16_t)((rx_message)->Data[0] << 8 | (rx_message)->Data[1]); \
        (ptr)->speed = (uint16_t)((rx_message)->Data[2] << 8 | (rx_message)->Data[3]);    \
    }


//���ص��̵��������ַ��ͨ��ָ�뷽ʽ��ȡԭʼ����
const motor_measure_t *get_Chassis_Motor_Measure_Point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];  //(i & 0x03)
}



/**
	* @brief		�˲�������
	* @param		none
	*	@retval		none
  */

void CAN1_filter_config(void)
{
    CAN_FilterTypeDef CAN1_FIilter_InitStruct;

    CAN1_FIilter_InitStruct.FilterActivation = ENABLE;									//�����˲���
    CAN1_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //����ģʽ
    CAN1_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32λ����
    CAN1_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN1_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN1_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN1_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN1_FIilter_InitStruct.FilterBank = 0;
		CAN1_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN1_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//ָ����������
    HAL_CAN_ConfigFilter(&hcan1, &CAN1_FIilter_InitStruct);							//����ָ������CAN���չ�����
    HAL_CAN_Start(&hcan1);																							//����can1
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);	//�����ж�

}


/**
	* @brief		HAl��can1�Ļص�����
	* @param		��������� CAN�ľ��
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


/*************************************can1���մ�����*************************************/

 void CAN1_chassis_receive(CAN_HandleTypeDef *hcan)
{
  	CAN_RxHeaderTypeDef	rx_message;															//������Ϣ�ṹ��

   	uint8_t Rx_Data[8];																					//���յ���Ϣ���������
		
  if(  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_message, Rx_Data) == HAL_OK)	//��ȡ���յ���Ϣ
	{	
    switch (rx_message.StdId)
		{	
                    /*���̵��*/
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
            motor_pitch.actual_Position = motor_pitch.position;   //ʵ��ֵ��ȥ�м�ֵ
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
