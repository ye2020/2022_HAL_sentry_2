/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			can_1_receive.c/h
 *
 * @brief 		����ң������ʼ����ң�������ݻ�ȡ��ң����ͨѶЭ��Ľ���
 *
 * @note  		ң�������ݽ��ղ��ô��ڼ�DMA��ģʽ
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

static CAN_TxHeaderTypeDef Txmessage;				//���͵���Ϣ

/*--------------------����-----------------------*/
//�������̵������ static
motor_measure_t motor_chassis[4];
//���������������
static motor_measure_t motor_fire;
//����pitch��������
static motor_measure_t motor_pitch;

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
    CAN1_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//ָ����������
    HAL_CAN_ConfigFilter(&hcan1, &CAN1_FIilter_InitStruct);							//����ָ������CAN���չ�����
    HAL_CAN_Start(&hcan1);																							//����can1
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);	//�����ж�

}


/**
	* @brief		can1���ͺ���
	* @param		��������� ESC_201~ESC_204 -> ����ͬһ�����4����ͬID�ĵ��
	*	@retval		none
  */

void CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
{
    uint32_t send_mail_box;							//��������
    uint8_t Data[8];										//�������ݵ�����

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

    HAL_CAN_AddTxMessage(&hcan1, &Txmessage, Data, &send_mail_box);			//��һ������ͨ�� CAN ���߷���
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
        CAN1_chassis_receive(hcan)	;               



}


/*************************************can1���մ�����*************************************/

static void CAN1_chassis_receive(CAN_HandleTypeDef *hcan)
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

			 default:
        {
            break;
        }
			
		}
	}


}
