/**
******************************************************************************
* @file       gimbal_behaviour.c/h
* @brief      云台状态机。
******************************************************************************
*/


#include "gimbal_behaviour.h"
#include "SysInit.h"


/**************** 变量 *******************/ 

// 云台遥控状态表
gimbal_behaviour_e gimbal_remote_control_Table[3][3] = 
{           /*右上*/                     /* 右下 */                          /* 右中 */
  /*左上*/  {GIMBAL_AUTOCONTROL,         GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_HIGH_SPEED   },
  /*左下*/  {GIMBAL_STANDBY,             GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_STOP_SHOOT   },
  /*左中*/  {GIMBAL_AUTOATTACK,          GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_LOW_SPEED    }
};           

//static
float Gimbal_ch2 = 0.0f, Gimbal_ch3 = 0.0f; // 云台电机受控量 ( ch2为ywa轴控制量，ch3为pitch轴)
static Shoot_WorkStatus_e Friction_wheel_mode = STOP_SHOOT; // 火控射速控制量
static Fire_WorkStatus_e Fire_mode = STOP_FIRE;            // 火控开火模式控制量

/**************** 函数声明 *******************/ 





/**
  * @brief         云台状态选择
  * @param[in]      fir_gimbal_behaviour_f
  * @retval         none
  * @attention
  */
void Gimbal_behaviour_mode_set(gimbal_control_t *fir_gimbal_behaviour_f)
{



}

/**
  * @brief          云台无力
  * @param[in]      gimbal_stop_f
  * @retval         none
  * @attention
  */
void Gimbal_Stop(gimbal_control_t *gimbal_stop_f)
{
    //控制量
    gimbal_stop_f->pitch_c.output = 0;
    gimbal_stop_f->yaw_c.output = 0;

    //自瞄控制量
//    gimbal_stop_f->auto_c->pitch_control_data = 0;
//    gimbal_stop_f->auto_c->yaw_control_data = 0;
	
	Friction_wheel_mode = STOP_SHOOT;  

    Gimbal_ch3 = 0.0f;
    Gimbal_ch2 = 0.0f;

}
