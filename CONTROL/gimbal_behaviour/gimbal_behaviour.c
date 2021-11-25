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
  /*����*/  {GIMBAL_AUTOCONTROL,         GIMBAL_PATROl,             GIMBAL_REMOTECONTROL_HIGH_SPEED   },
  /*����*/  {GIMBAL_STANDBY,             GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_STOP_SHOOT   },
  /*����*/  {GIMBAL_AUTOATTACK,          GIMBAL_STANDBY,            GIMBAL_REMOTECONTROL_LOW_SPEED    }
};           


//static
float Gimbal_ch2 = 0.0f, Gimbal_ch3 = 0.0f; // ��̨����ܿ��� ( ch2Ϊywa���������ch3Ϊpitch��)
static Shoot_WorkStatus_e Friction_wheel_mode = STOP_SHOOT; // ������ٿ�����
static Fire_WorkStatus_e Fire_mode = STOP_FIRE;            // ��ؿ���ģʽ������

/**************** �������� *******************/ 

static void Gimbal_AutoControl(gimbal_control_t *gimbal_autocontrol_f);           //  ����ģʽ(����+Ѳ��)
static void Gimbal_Patrol(gimbal_control_t *gimbal_Patro_f);                      //  ��̨Ѳ��
static void Gimbal_RemoteControl(gimbal_control_t *gimbal_remotecontrol_f);       //  ��̨ң��ģʽ



/**
  * @brief         ��̨״̬ѡ��
  * @param[in]      fir_gimbal_behaviour_f
  * @retval         none
  * @attention
  */
void Gimbal_behaviour_mode_set(gimbal_control_t *fir_gimbal_behaviour_f)
{
    const char rc_sw1_lift    = (fir_gimbal_behaviour_f ->gimbal_RC ->rc.s[1] - 1);           // ң�ز���ֵ��1
		const char rc_sw2_right 	= (fir_gimbal_behaviour_f ->gimbal_RC ->rc.s[0] - 1);           
    fir_gimbal_behaviour_f->gimbal_behaviour = gimbal_remote_control_Table[rc_sw1_lift][rc_sw2_right];

    switch (fir_gimbal_behaviour_f->gimbal_behaviour)
    {
      /*  ����ģʽ */
      case GIMBAL_AUTOCONTROL:
      {
        Gimbal_AutoControl(fir_gimbal_behaviour_f);
        break;
      }
      /*  ��ʼ�� */
      case GIMBAL_STANDBY:
      {
        Remote_reload();                                           //ҡ��������
        Gimbal_Stop(fir_gimbal_behaviour_f);                       //ֹͣ
        break;
      }
      /* ����ģʽ */
      case GIMBAL_AUTOATTACK:
      {
        Gimbal_AutoControl(fir_gimbal_behaviour_f);
        Friction_wheel_mode = STOP_SHOOT;
			  Fire_mode = STOP_FIRE;
        break;
      }
      /*  �ֿص����� */
      case GIMBAL_REMOTECONTROL_LOW_SPEED:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //״̬����Ϊ�ֶ�
        Friction_wheel_mode = LOW_SPEED;
        break;
      }
      /*  �ֿ�ͣ�� */
      case GIMBAL_REMOTECONTROL_STOP_SHOOT:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //״̬����Ϊ�ֶ�
        Friction_wheel_mode = STOP_SHOOT;
        break;
      }
      /*  �ֿظ����� */
      case GIMBAL_REMOTECONTROL_HIGH_SPEED:
      {
        fir_gimbal_behaviour_f->gimbal_behaviour = GIMBAL_REMOTECONTROL; //״̬����Ϊ�ֶ�
        Friction_wheel_mode = HIGH_SPEED;
        break;
      }
      /*  ��̨���� */
      case GIMBAL_STOP:
      {
        Remote_reload();       //ҡ��������
        Gimbal_Stop(fir_gimbal_behaviour_f);
        break;
      }
      /* ң��ģʽ */
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


/**
  * @brief          ����ģʽ(����+Ѳ��)
  * @param[in]      gimbal_autocontrol_f
  * @retval         none
  * @attention
  */
static void Gimbal_AutoControl(gimbal_control_t *gimbal_autocontrol_f)
{


}

/**
  * @brief          ��̨Ѳ��
  * @param[in]      *gimbal_Patro_f
  * @retval         none
  */
 static void Gimbal_Patrol(gimbal_control_t *gimbal_Patro_f)
{


}

/**
  * @brief          ��̨ң��ģʽ
  * @param[in]      gimbal_remotecontrol_f
  * @retval         none
  * @attention
  */
static void Gimbal_RemoteControl(gimbal_control_t *gimbal_remotecontrol_f)
{


}
