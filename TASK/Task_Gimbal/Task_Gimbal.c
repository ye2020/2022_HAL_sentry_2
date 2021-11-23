/**
  *****************************��ݸ��ѧԺACEʵ���� *****************************
  * @file       fire_task.c/h
  * @brief     	��̨����
  * @note       �ϲ��汾
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************��ݸ��ѧԺACEʵ���� *****************************
	*/
	
#include "Task_Gimbal.h"
#include "SysInit.h"

/**************** ���� *******************/ 

//��������̨����
gimbal_control_t gimbal_control;



/**************** �������� *******************/ 

static void Gimbal_init(gimbal_control_t *Gimbal_data_init_f);                  // ��̨���ݳ�ʼ��
static void gimbal_controlwork(gimbal_control_t *gimbal_task_control);          // ��̨��Ҫ���ƺ���
static void Gimbal_remote_mode_choose(gimbal_control_t *fir_gimbal_choose);     // ��̨״̬ѡ��
static void gimbal_task_off();



void GIMBAL_TASK(void const * argument)
{
	 vTaskDelay(GIMBAL_TASK_INIT_TIME);
    
    // ��̨���ݳ�ʼ�� 
    Gimbal_init(&gimbal_control);

	while(1)
	{
		/* �������� */
		LEDE2 = 0;
		
    // ��̨��Ҫ���ƺ���
    gimbal_controlwork(&gimbal_control);

		vTaskDelay(GIMBAL_CONTROL_TIME_MS); //ϵͳ��ʱ

	}
	

}


/**
  * @brief          ��̨���ݳ�ʼ��
  * @param[in]      none
  * @retval         none
  * @attention
  */

static void Gimbal_init(gimbal_control_t *Gimbal_data_init_f)
{
    {
      /*--------------------��ȡָ��--------------------*/
          //��ȡң����ָ��(����)
        Gimbal_data_init_f->gimbal_RC = get_remote_control_point();
          //��ȡ��̨���ָ��
        Gimbal_data_init_f->yaw_c.yaw_motor_measure = Get_Yaw_Gimbal_Motor_Measure_Point();
        Gimbal_data_init_f->pitch_c.pitch_motor_measure = Get_Pitch_Gimbal_Motor_Measure_Point();
          //��ȡ����ָ��
//        Gimbal_data_init_f->auto_c = Get_Auto_Control_Point();
          // ��ȡ���ָ��
//        Gimbal_data_init_f->Fire_task_control = get_Fire_control_point();
    }

       /*--------------------���ң������ֵ�Ƿ���ȷ--------------------*/
    RC_data_is_error();


      /*--------------------�˲���ʼ��--------------------*/
    {
        //pitch���ͨ�˲�
        first_order_filter_init(&Gimbal_data_init_f->pitch_c.LowFilt_Pitch_Data, Gimbal_Pitch_Fir_Ord_Low_Fil_Param);
        //��ʼ��P�Ử���˲���
        Sliding_Mean_Filter_Init(&Gimbal_data_init_f->pitch_c.Slidmean_Pitch_Data);
    }

#if (PITCH_PID_MODE == 1)	
              //Pitch������pid������ʼ��
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_p_pid, GIMBAL_UP_P_PITCH_P, GIMBAL_UP_P_PITCH_I, GIMBAL_UP_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_s_pid, GIMBAL_UP_S_PITCH_P, GIMBAL_UP_S_PITCH_I, GIMBAL_UP_S_PITCH_D, 0, 0);
        //Pitch�½���pid������ʼ��
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_p_pid, GIMBAL_DOWN_P_PITCH_P, GIMBAL_DOWN_P_PITCH_I, GIMBAL_DOWN_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_s_pid, GIMBAL_DOWN_S_PITCH_P, GIMBAL_DOWN_S_PITCH_I, GIMBAL_DOWN_S_PITCH_D, 0, 0);
				
				//���飺Pitch������pid������ʼ��
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_auto_p_pid, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_auto_s_pid, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_I, 0, 0);
			
        //���飺Pitch���½�pid������ʼ��
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_auto_p_pid, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_auto_s_pid, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_D, 0, 0);



#elif (PITCH_PID_MODE == 2)	
			
        //Pitch pid������ʼ��
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_p_pid, GIMBAL_P_PITCH_P, GIMBAL_P_PITCH_I, GIMBAL_P_PITCH_D, 2000, 0);
		Gimbal_data_init_f->pitch_c.pitch_p_pid.maximum = 180.0f;   //180.0f
		Gimbal_data_init_f->pitch_c.pitch_p_pid.minimum = -200.0f;  //-250.0f
		Gimbal_data_init_f->pitch_c.pitch_p_pid.stepIn = 10.0f;
		Gimbal_data_init_f->pitch_c.pitch_p_pid.errorabsmin = 1;
		Gimbal_data_init_f->pitch_c.pitch_p_pid.errorabsmax = 8;
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_s_pid, GIMBAL_S_PITCH_P, GIMBAL_S_PITCH_I, GIMBAL_S_PITCH_D, 0, 0);
			
			//���飺Pitch��pid������ʼ��
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_auto_p_pid, GIMBAL_AUTO_INDUSTRY_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_P_PITCH_D, 2000, 0);
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.maximum = 180.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.minimum = -250.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.stepIn = 7.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.errorabsmin = 10;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.errorabsmax = 30;
		pid_init(&Gimbal_data_init_f->pitch_c.pitch_auto_s_pid, GIMBAL_AUTO_INDUSTRY_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_S_PITCH_D, 0, 0);

#endif	
  /*--------------------���ÿ���״̬--------------------*/
    gimbal_task_off();

}


/**
  * @brief          ��̨��Ҫ״̬���ƺ���
  * @param[in]      none
  * @retval         none
  * @attention
  */
 static void gimbal_controlwork(gimbal_control_t *gimbal_task_control)
 {
        // ���ң������ֵ�Ƿ���ȷ
        RC_data_is_error();

        //ͨ�����������ղ�����MiniPC����������

        //���͵�����ɫ��p��Ƕȣ����ٸ��Ӿ�


        //��̨ģʽѡ��
        Gimbal_remote_mode_choose(gimbal_task_control);

 }


/**
  * @brief          ��̨��Ϊѡ��
  * @param[in]      none
  * @retval         none
  * @attention
  */
static void Gimbal_remote_mode_choose(gimbal_control_t *fir_gimbal_choose)
{
    Gimbal_behaviour_mode_set(fir_gimbal_choose);
}



/**
  * @brief          ��̨ȫ���ر�
  * @param[in]      none
  * @retval         none
  * @attention      0: ״̬���л�
  *                 1: ���ν���״̬
  *                 2: �����ʼ����־λ
  */
static void gimbal_task_off()
{
      //������
    gimbal_control.pitch_c.output = 0;
    gimbal_control.yaw_c.output = 0;
//    gimbal_control.Fire_task_control->GDA_output = 0;
//    gimbal_control.Fire_task_control->GDB_output = 0;

    // ���������
//    gimbal_control.auto_c->auto_pitch_angle = 0.0f;
//    gimbal_control.auto_c->auto_yaw_angle = 0.0f;
//    gimbal_control.auto_c->pitch_control_data = 0.0f;
//    gimbal_control.auto_c->yaw_control_data = 0.0f;
//    gimbal_control.pitch_c.Auto_record_location = 0.0f;

      gimbal_control.gimbal_behaviour = GIMBAL_STOP;
      Gimbal_Stop(&gimbal_control);
}

