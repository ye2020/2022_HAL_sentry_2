/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       fire_task.c/h
  * @brief     	云台任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#include "Task_Gimbal.h"
#include "SysInit.h"

/**************** 变量 *******************/ 

//申明主云台变量
gimbal_control_t gimbal_control;



/**************** 函数声明 *******************/ 

static void Gimbal_init(gimbal_control_t *Gimbal_data_init_f);                  // 云台数据初始化
static void gimbal_controlwork(gimbal_control_t *gimbal_task_control);          // 云台主要控制函数
static void Gimbal_remote_mode_choose(gimbal_control_t *fir_gimbal_choose);     // 云台状态选择
static void gimbal_task_off();



void GIMBAL_TASK(void const * argument)
{
	 vTaskDelay(GIMBAL_TASK_INIT_TIME);
    
    // 云台数据初始化 
    Gimbal_init(&gimbal_control);

	while(1)
	{
		/* 心跳任务 */
		LEDE2 = 0;
		
    // 云台主要控制函数
    gimbal_controlwork(&gimbal_control);

		vTaskDelay(GIMBAL_CONTROL_TIME_MS); //系统延时

	}
	

}


/**
  * @brief          云台数据初始化
  * @param[in]      none
  * @retval         none
  * @attention
  */

static void Gimbal_init(gimbal_control_t *Gimbal_data_init_f)
{
    {
      /*--------------------获取指针--------------------*/
          //获取遥控器指针(数据)
        Gimbal_data_init_f->gimbal_RC = get_remote_control_point();
          //获取云台电机指针
        Gimbal_data_init_f->yaw_c.yaw_motor_measure = Get_Yaw_Gimbal_Motor_Measure_Point();
        Gimbal_data_init_f->pitch_c.pitch_motor_measure = Get_Pitch_Gimbal_Motor_Measure_Point();
          //获取自瞄指针
//        Gimbal_data_init_f->auto_c = Get_Auto_Control_Point();
          // 获取火控指针
//        Gimbal_data_init_f->Fire_task_control = get_Fire_control_point();
    }

       /*--------------------检查遥控器数值是否正确--------------------*/
    RC_data_is_error();


      /*--------------------滤波初始化--------------------*/
    {
        //pitch轴低通滤波
        first_order_filter_init(&Gimbal_data_init_f->pitch_c.LowFilt_Pitch_Data, Gimbal_Pitch_Fir_Ord_Low_Fil_Param);
        //初始化P轴滑动滤波器
        Sliding_Mean_Filter_Init(&Gimbal_data_init_f->pitch_c.Slidmean_Pitch_Data);
    }

#if (PITCH_PID_MODE == 1)	
              //Pitch上升的pid参数初始化
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_p_pid, GIMBAL_UP_P_PITCH_P, GIMBAL_UP_P_PITCH_I, GIMBAL_UP_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_s_pid, GIMBAL_UP_S_PITCH_P, GIMBAL_UP_S_PITCH_I, GIMBAL_UP_S_PITCH_D, 0, 0);
        //Pitch下降的pid参数初始化
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_p_pid, GIMBAL_DOWN_P_PITCH_P, GIMBAL_DOWN_P_PITCH_I, GIMBAL_DOWN_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_s_pid, GIMBAL_DOWN_S_PITCH_P, GIMBAL_DOWN_S_PITCH_I, GIMBAL_DOWN_S_PITCH_D, 0, 0);
				
				//自瞄：Pitch的上升pid参数初始化
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_auto_p_pid, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_UP_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_up_auto_s_pid, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_UP_S_PITCH_I, 0, 0);
			
        //自瞄：Pitch的下降pid参数初始化
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_auto_p_pid, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_DOWN_P_PITCH_D, 0, 0);
        pid_init(&Gimbal_data_init_f->pitch_c.pitch_down_auto_s_pid, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_DOWN_S_PITCH_D, 0, 0);



#elif (PITCH_PID_MODE == 2)	
			
        //Pitch pid参数初始化
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_p_pid, GIMBAL_P_PITCH_P, GIMBAL_P_PITCH_I, GIMBAL_P_PITCH_D, 2000, 0);
		Gimbal_data_init_f->pitch_c.pitch_p_pid.maximum = 180.0f;   //180.0f
		Gimbal_data_init_f->pitch_c.pitch_p_pid.minimum = -200.0f;  //-250.0f
		Gimbal_data_init_f->pitch_c.pitch_p_pid.stepIn = 10.0f;
		Gimbal_data_init_f->pitch_c.pitch_p_pid.errorabsmin = 1;
		Gimbal_data_init_f->pitch_c.pitch_p_pid.errorabsmax = 8;
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_s_pid, GIMBAL_S_PITCH_P, GIMBAL_S_PITCH_I, GIMBAL_S_PITCH_D, 0, 0);
			
			//自瞄：Pitch的pid参数初始化
    pid_init(&Gimbal_data_init_f->pitch_c.pitch_auto_p_pid, GIMBAL_AUTO_INDUSTRY_P_PITCH_P, GIMBAL_AUTO_INDUSTRY_P_PITCH_I, GIMBAL_AUTO_INDUSTRY_P_PITCH_D, 2000, 0);
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.maximum = 180.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.minimum = -250.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.stepIn = 7.0f;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.errorabsmin = 10;
		Gimbal_data_init_f->pitch_c.pitch_auto_p_pid.errorabsmax = 30;
		pid_init(&Gimbal_data_init_f->pitch_c.pitch_auto_s_pid, GIMBAL_AUTO_INDUSTRY_S_PITCH_P, GIMBAL_AUTO_INDUSTRY_S_PITCH_I, GIMBAL_AUTO_INDUSTRY_S_PITCH_D, 0, 0);

#endif	
  /*--------------------设置开机状态--------------------*/
    gimbal_task_off();

}


/**
  * @brief          云台主要状态控制函数
  * @param[in]      none
  * @retval         none
  * @attention
  */
 static void gimbal_controlwork(gimbal_control_t *gimbal_task_control)
 {
        // 检查遥控器数值是否正确
        RC_data_is_error();

        //通过串口三接收并保存MiniPC发来的数据

        //发送敌人颜色，p轴角度，射速给视觉


        //云台模式选择
        Gimbal_remote_mode_choose(gimbal_task_control);

 }


/**
  * @brief          云台行为选择
  * @param[in]      none
  * @retval         none
  * @attention
  */
static void Gimbal_remote_mode_choose(gimbal_control_t *fir_gimbal_choose)
{
    Gimbal_behaviour_mode_set(fir_gimbal_choose);
}



/**
  * @brief          云台全部关闭
  * @param[in]      none
  * @retval         none
  * @attention      0: 状态接切换
  *                 1: 初次进入状态
  *                 2: 清除初始化标志位
  */
static void gimbal_task_off()
{
      //控制量
    gimbal_control.pitch_c.output = 0;
    gimbal_control.yaw_c.output = 0;
//    gimbal_control.Fire_task_control->GDA_output = 0;
//    gimbal_control.Fire_task_control->GDB_output = 0;

    // 自瞄控制量
//    gimbal_control.auto_c->auto_pitch_angle = 0.0f;
//    gimbal_control.auto_c->auto_yaw_angle = 0.0f;
//    gimbal_control.auto_c->pitch_control_data = 0.0f;
//    gimbal_control.auto_c->yaw_control_data = 0.0f;
//    gimbal_control.pitch_c.Auto_record_location = 0.0f;

      gimbal_control.gimbal_behaviour = GIMBAL_STOP;
      Gimbal_Stop(&gimbal_control);
}

