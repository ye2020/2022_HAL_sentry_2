#ifndef __CHASSIS_APP_H__
#define __CHASSIS_APP_H__

#include "main.h"	
	
extern void chassis_app_init(void);
void Chassis_CAN_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204);
void Chassis_CAN2_Send_Msg(int16_t ESC_201, int16_t ESC_202, int16_t ESC_203, int16_t ESC_204);
	


#endif
