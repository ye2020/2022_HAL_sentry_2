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
	
#include "SysInit.h"

/************ 声明 **************/

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

	/*  can滤波配置初始化 */
		CAN1_filter_config();
	/*  串口二环形队列初始化 */
		bsp_usart2_init();

	/*  底盘云台选择 */
		task_init();

}

/**
  * @brief      拨码开关数值检测   
  * @param[in]  none
  * @retval     none
  * @attention  
  */
static  uint16_t  DIP_Switch(void)
{
	uint16_t value;
	
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12) == 1)  value |= 0x01;			//最0位置1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13) == 1)  value |= 0x02;			//最1位置1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14) == 1)  value |= 0x04;			//最3位置1
	else																					value |= 0x00;
	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15) == 1)  value |= 0x08;			//最4位置1
	else																					value |= 0x00;
	
	return value;
}


/**
  * @brief      选择初始化 chassis_app \ gimbal_app   
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
		/*  底盘初始化 */
		chassis_app_init();
	}
	
	else if (app == GIMBAL_APP)
	{
		/* 云台初始化 */
		gimbal_app_init();

	}

}

//生成[min,max]范围的随机数
int RNG_Get_RandomRange(int min,int max)
{
	uint32_t random;
	HAL_RNG_GenerateRandomNumber(&hrng,&random);
	
	return random%(max-min+1) +min;
}
