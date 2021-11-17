/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       SysInit.c/h
  * @brief      初始化
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
#ifndef SYSINIT_H
#define SYSINIT_H

/*  系统头文件 */
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



/* ************************  分割线  ******************** */	

#define CHASSIS_APP 0
#define GIMBAL_APP  15


//LED端口定义
#define LEDE0 PEout(0)  //遥控
#define LEDE1 PEout(1)  //底盘
#define LEDE2 PEout(2)	//云台	
#define LEDE3 PEout(3)  //火控	
#define LEDE4 PEout(4)	//安检
#define LEDB7 PBout(7)  //工作指示灯

	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
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

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入


/************电机 传动比*减速比 ***************/
#define YAW_RATIO      (5*19)         //Yaw轴
#define PITCH_RATIO		 (1.5*19)       //Pitch轴
#define CHASSIS_RATIO  (1*19)					//底盘电机减速比
#define Sec_YAW_RATIO  (3*1)          //副Yaw轴

/* 底盘电机移动速度设定 */ 
#define M3508_MAX_OUTPUT_CURRENT  5000   //m3508电机最大电流输出  
#define M2006_MAX_OUTPUT_CURRENT  9500   //m2006电机最大电流输出

#define MAX_MOTOR_CAN_INPUT    2000.0f   //3508最大电流输入
#define MAX_MOTOR_CAN_OUTPUT   16000.0f  //3508最大电流输出

/*************减速电机启动电流补偿（快速启动）**********/
#define GEAR_MOTOR_START_CURRENT   300
#define GEAR_MOTOR_REDUCE_CURRENT  1.21


void System_init(void);


#endif









