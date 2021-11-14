/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       chassis_task.c/h
  * @brief      完成底盘控制任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
#ifndef TASK_CHASSIS_H
#define TASK_CHASSIS_H

/*OS控制任务周期以及启动时间*/
#define CHASSIS_TASK_INIT_TIME 5
#define CHASSIS_CONTROL_TIME   2




extern  void Chassis_Task(void const * argument);

#endif





