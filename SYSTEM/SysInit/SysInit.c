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

/************ ���� **************/

static  uint16_t  DIP_Switch(void);
static void task_init(void);


extern RNG_HandleTypeDef hrng;





/*****************************/

	
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
extern RNG_HandleTypeDef hrng;


void System_init(void)
{

	/*  can�˲����ó�ʼ�� */
		CAN1_filter_config();
	/*  ���ڶ����ζ��г�ʼ�� */
		bsp_usart2_init();

	/*  ������̨ѡ�� */
		task_init();

}

/**
  * @brief      ���뿪����ֵ���   
  * @param[in]  none
  * @retval     none
  * @attention  
  */
static  uint16_t  DIP_Switch(void)
{
	uint16_t value;
	
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12) == 1)  value |= 0x01;			//��0λ��1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13) == 1)  value |= 0x02;			//��1λ��1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14) == 1)  value |= 0x04;			//��3λ��1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15) == 1)  value |= 0x08;			//��4λ��1
	else																					value |= 0x00;
	
	return value;
}


/**
  * @brief      ѡ���ʼ�� chassis_app \ gimbal_app   
  * @param[in]  none
  * @retval     none
  * @attention  
  */
void task_init(void)
{
	uint8_t app = 0;
//	app = DIP_Switch();
		app = CHASSIS_APP;
	
	if(app == CHASSIS_APP)
	{
		/*  ���̳�ʼ�� */
		chassis_app_init();
	}
	
	else if (app == GIMBAL_APP)
	{
		/* ��̨��ʼ�� */
		gimbal_app_init();

	}

}

//����[min,max]��Χ�������
int RNG_Get_RandomRange(int min,int max)
{
	uint32_t random;
	HAL_RNG_GenerateRandomNumber(&hrng,&random);
	
	return random%(max-min+1) +min;
}
