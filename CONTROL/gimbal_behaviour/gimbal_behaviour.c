/**
******************************************************************************
* @file       gimbal_behaviour.c/h
* @brief      ��̨״̬����
******************************************************************************
*/


#include "gimbal_behaviour.h"
#include "SysInit.h"


/**************** ���� *******************/ 

// ��̨ң��״̬��
gimbal_behaviour_e gimbal_remote_control_Table[3][3] = 
{           /*����*/                     /* ���� */                          /* ���� */
  /*����*/  {GIMBAL_AUTOCONTROL,         GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_HIGH_SPEED   },
  /*����*/  {GIMBAL_STANDBY,             GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_STOP_SHOOT   },
  /*����*/  {GIMBAL_AUTOATTACK,          GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_LOW_SPEED    }
};           

//static
float Gimbal_ch2 = 0.0f, Gimbal_ch3 = 0.0f; // ��̨����ܿ��� ( ch2Ϊywa���������ch3Ϊpitch��)
static Shoot_WorkStatus_e Friction_wheel_mode = STOP_SHOOT; // ������ٿ�����
static Fire_WorkStatus_e Fire_mode = STOP_FIRE;            // ��ؿ���ģʽ������

/**************** �������� *******************/ 





/**
  * @brief         ��̨״̬ѡ��
  * @param[in]      fir_gimbal_behaviour_f
  * @retval         none
  * @attention
  */
void Gimbal_behaviour_mode_set(gimbal_control_t *fir_gimbal_behaviour_f)
{



}

/**
  * @brief          ��̨����
  * @param[in]      gimbal_stop_f
  * @retval         none
  * @attention
  */
void Gimbal_Stop(gimbal_control_t *gimbal_stop_f)
{
    //������
    gimbal_stop_f->pitch_c.output = 0;
    gimbal_stop_f->yaw_c.output = 0;

    //���������
//    gimbal_stop_f->auto_c->pitch_control_data = 0;
//    gimbal_stop_f->auto_c->yaw_control_data = 0;
	
	Friction_wheel_mode = STOP_SHOOT;  

    Gimbal_ch3 = 0.0f;
    Gimbal_ch2 = 0.0f;

}
