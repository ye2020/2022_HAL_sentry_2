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
	
#include "SysInit.h"


	
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;



void System_init(void)
{
	/* ң�س�ʼ�� */
		remote_control_init();
	/*  can�˲����ó�ʼ�� */
		CAN1_filter_config();


}

