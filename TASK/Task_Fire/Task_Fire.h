#ifndef TASK_FIRE_H
#define TASK_FIRE_H


/*OS�������������Լ�����ʱ��*/
#define FIRE_TASK_INIT_TIME  5
#define FIRE_CONTROL_TIME_MS 2


/*����ģʽ*/
typedef enum
{
    FIRE,          //����
    AUTO_FIRE,     //�Զ�����
    STOP_FIRE,     //ֹͣ����
    BACK,          //�˵�
    FIRE_ERROR,

} Fire_WorkStatus_e;


/*Ħ����ģʽ*/
typedef enum
{
    LOW_SPEED,
    HIGH_SPEED,
    STOP_SHOOT,
    SHOOT_ERROR,

} Shoot_WorkStatus_e;


extern  void Fire_Task(void *pvParameters);

#endif
