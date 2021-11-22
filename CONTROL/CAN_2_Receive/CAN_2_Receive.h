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

#ifndef CAN_2_RECEIVE_H__
#define CAN_2_RECEIVE_H__

#include "main.h"
#include "CAN_1_Receive.h"

extern void CAN2_filter_config(void);
void CAN2_chassis_receive(CAN_HandleTypeDef *hcan);



#endif
