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
  /*左上*/  {GIMBAL_AUTOCONTROL,         GIMBAL_PATROl,             GIMBAL_REMOTECONTROL_HIGH_SPEED   },
  /*左下*/  {GIMBAL_STANDBY,             GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_STOP_SHOOT   },
  /*左中*/  {GIMBAL_AUTOATTACK,          GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_LOW_SPEED    }
};           


//static
float Gimbal_ch2 = 0.0f, Gimbal_ch3 = 0.0f; // 云台电机受控量 ( ch2为ywa轴控制量，ch3为pitch轴)
static Shoot_WorkStatus_e Friction_wheel_mode = STOP_SHOOT; // 火控射速控制量
static Fire_WorkStatus_e Fire_mode = STOP_FIRE;            // 火控开火模式控制量

/**************** 函数声明 *******************/ 

static void Gimbal_AutoControl(gimbal_control_t *gimbal_autocontrol_f);           //  比赛模式(自瞄+巡逻)
static void Gimbal_Patrol(gimbal_control_t *gimbal_Patro_f);                      //  云台巡逻
static void Gimbal_RemoteControl(gimbal_control_t *gimbal_remotecontrol_f);       //  云台遥控模式



/**
  * @brief         云台状态选择
  * @param[in]      fir_gimbal_behaviour_f
  * @retval         none
  * @attention
  */
void Gimbal_behaviour_mode_set(gimbal_control_t *fir_gimbal_behaviour_f)
{
    const char rc_sw1_lift    = (fir_gimbal_behaviour_f ->gimbal_RC ->rc.s[1] - 1);           // 遥控拨杆值减1
		const char rc_sw2_right 	= (fir_gimbal_behaviour_f ->gimbal_RC ->rc.s[0] - 1);           
    fir_gimbal_behaviour_f->gimbal_behaviour = gimbal_remote_control_Table[rc_sw1_lift][rc_sw2_right];

    switch (fir_gimbal_behaviour_f->gimbal_behaviour)
    {
      /*  比赛模式 */
      case GIMBAL_AUTOCONTROL:
      {
        Gimbal_AutoControl(fir_gimbal_behaviour_f);
        break;
      }
      /*  初始化 */
      case GIMBAL_STANDBY:
      {
        Remote_reload();                                           //摇杆量清零
        Gimbal_Stop(fir_gimbal_behaviour_f);                       //停止
        break;
      }
      /* 自瞄模式 */
      case GIMBAL_AUTOATTACK:
      {
        Gimbal_AutoControl(fir_gimbal_behaviour_f);
        Friction_wheel_mode = STOP_SHOOT;
			  Fire_mode = STOP_FIRE;
        break;
      }
      /*  手控低射速 */
      case GIMBAL_REMOTECONTROL_LOW_SPEED:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //状态设置为手动
        Friction_wheel_mode = LOW_SPEED;
        break;
      }
      /*  手控停火 */
      case GIMBAL_REMOTECONTROL_STOP_SHOOT:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //状态设置为手动
        Friction_wheel_mode = STOP_SHOOT;
        break;
      }
      /*  手控高射速 */
      case GIMBAL_REMOTECONTROL_HIGH_SPEED:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //状态设置为手动
        Friction_wheel_mode = HIGH_SPEED;
        break;
      }
      /*  云台无力 */
      case GIMBAL_STOP:
      {
        Remote_reload();       //摇杆量清零
        Gimbal_Stop(fir_gimbal_behaviour_f);
        break;
      }
      /* 遥控模式 */
      case GIMBAL_REMOTECONTROL:
      {
        Gimbal_RemoteControl(fir_gimbal_behaviour_f);
        break;
      }

      case GIMBAL_PATROl:
      {
        Gimbal_Patrol(fir_gimbal_behaviour_f);
        break;
      }
    default:
      break;
    }

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


/**
  * @brief          比赛模式(自瞄+巡逻)
  * @param[in]      gimbal_autocontrol_f
  * @retval         none
  * @attention
  */
static void Gimbal_AutoControl(gimbal_control_t *gimbal_autocontrol_f)
{


}

/**
  * @brief          云台巡逻
  * @param[in]      *gimbal_Patro_f
  * @retval         none
  */
 static void Gimbal_Patrol(gimbal_control_t *gimbal_Patro_f)
{


}

/**
  * @brief          云台遥控模式
  * @param[in]      gimbal_remotecontrol_f
  * @retval         none
  * @attention
  */
static void Gimbal_RemoteControl(gimbal_control_t *gimbal_remotecontrol_f)
{


}
