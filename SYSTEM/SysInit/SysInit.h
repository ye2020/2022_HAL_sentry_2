/**
  *****************************��ݸ��ѧԺACEʵ���� *****************************
  * @file       SysInit.c/h
  * @brief      ��ʼ��
  * @note       �ϲ��汾
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************��ݸ��ѧԺACEʵ���� *****************************
	*/
#ifndef SYSINIT_H
#define SYSINIT_H

/*  ϵͳͷ�ļ� */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdint.h"

/************************* Task ************************/
#include "Task_Chassis.h"
#include "Task_Gimbal.h"

/* ************************freertos******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
	
/* ************************ Hardward ******************** */	
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_usart2.h"
#include "fifo_buff.h"


/* ************************ CONTROL ******************** */	
#include "CAN_1_Receive.h"
#include "RemoteControl.h"
#include "chassis_app.h"
#include "gimbal_app.h"
/* ************************ ALGORITHM ******************** */	

#include "pid.h"
#include "rmmotor.h"
#include "maths.h"
#include "filter.h"



/* ************************  �ָ���  ******************** */	

#define CHASSIS_APP 0
#define GIMBAL_APP  15


//LED�˿ڶ���
#define LEDE0 PEout(0)  //ң��
#define LEDE1 PEout(1)  //����
#define LEDE2 PEout(2)	//��̨	
#define LEDE3 PEout(3)  //���	
#define LEDE4 PEout(4)	//����
#define LEDB7 PBout(7)  //����ָʾ��

	 
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     


#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //����

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //����


/************��� ������*���ٱ� ***************/
#define YAW_RATIO      (5*19)         //Yaw��
#define PITCH_RATIO		 (1.5*19)       //Pitch��
#define CHASSIS_RATIO  (1*19)					//���̵�����ٱ�
#define Sec_YAW_RATIO  (3*1)          //��Yaw��

/* ���̵���ƶ��ٶ��趨 */ 
#define M3508_MAX_OUTPUT_CURRENT  5000   //m3508������������  
#define M2006_MAX_OUTPUT_CURRENT  9500   //m2006������������

#define MAX_MOTOR_CAN_INPUT    2000.0f   //3508����������
#define MAX_MOTOR_CAN_OUTPUT   16000.0f  //3508���������

/*************���ٵ��������������������������**********/
#define GEAR_MOTOR_START_CURRENT   300
#define GEAR_MOTOR_REDUCE_CURRENT  1.21


void System_init(void);


#endif









