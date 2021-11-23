#ifndef TASK_FIRE_H
#define TASK_FIRE_H


/*OS控制任务周期以及启动时间*/
#define FIRE_TASK_INIT_TIME  5
#define FIRE_CONTROL_TIME_MS 2


/*发弹模式*/
typedef enum
{
    FIRE,          //发射
    AUTO_FIRE,     //自动发射
    STOP_FIRE,     //停止发射
    BACK,          //退弹
    FIRE_ERROR,

} Fire_WorkStatus_e;


/*摩擦轮模式*/
typedef enum
{
    LOW_SPEED,
    HIGH_SPEED,
    STOP_SHOOT,
    SHOOT_ERROR,

} Shoot_WorkStatus_e;


extern  void Fire_Task(void *pvParameters);

#endif
