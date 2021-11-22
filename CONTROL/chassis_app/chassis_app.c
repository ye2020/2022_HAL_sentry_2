/**
 *****************************��ݸ��ѧԺACEʵ���� *****************************
 * @file 			chassis.c/h
 *
 * @brief 		���̳�ʼ������
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

#include "SysInit.h"
#include "main.h"
#include "chassis_app.h"

osThreadId ChassisTaskHandle;
static CAN_TxHeaderTypeDef Txmessage;				//���͵���Ϣ
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


/**
  * @brief      ���̳�ʼ��
  * @param[in]  
  * @retval     void
*/

void chassis_app_init(void)
{
	
		/* ң�س�ʼ�� */
	remote_control_init();
	
//	CAN1_receive_callback = CAN1_chassis_receive;

	
	/*  ������������ */
  osThreadDef(ChassisTask, Chassis_Task, osPriorityRealtime, 0, 200);
  ChassisTaskHandle = osThreadCreate(osThread(ChassisTask), NULL);

}



/**
	* @brief		can1���ͺ���
	* @param		��������� ESC_201~ESC_204 -> ����ͬһ�����4����ͬID�ĵ��
	*	@retval		none
  */


void Chassis_CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
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

void Chassis_CAN2_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204)
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

    HAL_CAN_AddTxMessage(&hcan2, &Txmessage, Data, &send_mail_box);			//��һ������ͨ�� CAN ���߷���
}

