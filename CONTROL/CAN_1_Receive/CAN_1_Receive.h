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

#ifndef CAN_1_RECEIVE_H__
#define CAN_1_RECEIVE_H__


#include "main.h"



//rm���ͳһ���ݽṹ��
typedef struct
{
    uint16_t position;
    int16_t speed;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_position;


    int16_t angle;
    int16_t speed_filt;
    int16_t first_Flag;
    int32_t yaw_angle;
    int32_t pitch_angle;
    int32_t actual_Position;  //��ʵλ��
} motor_measure_t;




static void CAN1_chassis_receive(CAN_HandleTypeDef *hcan);
void CAN1_filter_config(void);
void CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
extern const motor_measure_t *get_Chassis_Motor_Measure_Point(uint8_t i);


#endif

