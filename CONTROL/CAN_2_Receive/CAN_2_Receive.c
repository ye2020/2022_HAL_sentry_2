/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			can_2_receive.c/h
 *
 * @brief 	can2�˲�����ʼ���Լ�������̨��can2����
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

#include "CAN_2_Receive.h"
#include "SysInit.h"

extern CAN_HandleTypeDef hcan2;
extern CAN_HandleTypeDef hcan1;                     // ���



/**
	* @brief		can2�˲�������
	* @param		none
	*	@retval		none
  */

void CAN2_filter_config(void)
{
    CAN_FilterTypeDef CAN2_FIilter_InitStruct;

    CAN2_FIilter_InitStruct.FilterActivation = ENABLE;									//�����˲���
    CAN2_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //����ģʽ
    CAN2_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32λ����
    CAN2_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterBank = 14;
		CAN2_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN2_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//ָ����������
	
    HAL_CAN_ConfigFilter(&hcan2, &CAN2_FIilter_InitStruct);							//����ָ������CAN���չ�����
    HAL_CAN_Start(&hcan2);																							//����can2
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);	//�����ж�

}


 void CAN2_chassis_receive(CAN_HandleTypeDef *hcan)
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
					break;
				}
			 default:
        {
            break;
        }
			
		}
	}

}		
