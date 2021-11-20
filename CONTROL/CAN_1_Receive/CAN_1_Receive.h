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

#ifndef CAN_1_RECEIVE_H__
#define CAN_1_RECEIVE_H__


#include "main.h"



//rm电机统一数据结构体
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
    int32_t actual_Position;  //真实位置
} motor_measure_t;




static void CAN1_chassis_receive(CAN_HandleTypeDef *hcan);
void CAN1_filter_config(void);
void CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
extern const motor_measure_t *get_Chassis_Motor_Measure_Point(uint8_t i);


#endif

