/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       gimbal_task.c/h
  * @brief      云台任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
	
#ifndef TASK_GIMBAL_H
#define TASK_GIMBAL_H





/*OS控制任务周期以及启动时间*/
#define GIMBAL_TASK_INIT_TIME 	5
#define GIMBAL_CONTROL_TIME_MS  2

extern  void GIMBAL_TASK(void const * argument);

#endif
