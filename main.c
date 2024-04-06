/*******************************************************************************
 *				 _ _                                             _ _
				|   |                                           (_ _)
				|   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
				|   |       |   |   |   | |    _ _     _ _    | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
				|_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
								(C)2022 Lumi
 * Copyright (c) 2022
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: main.c
 *
 * Description: B2 den xanh sáng
 *
 *
 * Last Changed By:  $Author: trungnt $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $April 24, 2022
 *
 *
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define BTN_PRESS							0
// Define Logic GPIO_PIN

#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0

// Define GPIO PIN
#define LED_GPIO_PORT						GPIOA
#define LED_GPIO_PIN						GPIO_Pin_10
#define LED_PIN5							10
//#define LED_GPIO_PORT						GPIOA
//#define LED_GPIO_PIN						GPIO_Pin_3
//#define LED_PIN5							3
#define LEDControl_SetClock					RCC_AHB1Periph_GPIOA


#define BUZZER_GPIO_PORT					GPIOC
#define BUZZER_GPIO_PIN						GPIO_Pin_9
#define BUZZERControl_SetClock				RCC_AHB1Periph_GPIOC

#define BUTTON_GPIO_PORT					GPIOA
#define BUTTON_GPIO_PIN						GPIO_Pin_4
#define BUTTONControl_SetClock				RCC_AHB1Periph_GPIOB

#define BUTTON_GPIO_PORT2					GPIOB
#define BUTTON_GPIO_PIN2					GPIO_Pin_0
#define BUTTONControl_SetClock2				RCC_AHB1Periph_GPIOB

#define DELAY_3_SECONDS 3000
#define PRESS_THRESHOLD_LED_ON 				300000
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static void buzzer_Init(void);
static void button_Init(void);
static void Led_init(void) {
	// Khai bao bien thuoc kieu struct
	GPIO_InitTypeDef GPIO_InitStructure;

	// Cap xung clock hoat dong cho port A
	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);

	// chon chan su dung chuc nang dieu khien led

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;

	//Chon chan dieu khien led che do output

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	// Toc do xu ly

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// PUSH PULL

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	// trang thai ban dau tren chan la Pull down

	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	// khoi tao cac gia tri

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

}

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
void delay();
void delay1();
/******************************************************************************/
static void ledControlSetStatus(GPIO_TypeDef* GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
 if (Status == GPIO_PIN_SET)
 {
  GPIOx->BSRRL |= 1 << GPIO_PIN;
 }
 if (Status == GPIO_PIN_RESET)
 {
  GPIOx->BSRRH |= 1 << GPIO_PIN;
 }
}



//static void buzzerControlSetStatus(GPIO_TypeDef* GPIOx, uint8_t GPIO_PIN, uint8_t Status)
//{
// if (Status == GPIO_PIN_SET)
// {
//  GPIOx->BSRRL |= 1 << GPIO_PIN;
// }
// if (Status == GPIO_PIN_RESET)
// {
//  GPIOx->BSRRH |= 1 << GPIO_PIN;
// }
//}

static uint8_t buttonReadStatus(GPIO_TypeDef* GPIOx, uint32_t GPIO_PIN)
{
 uint32_t Read_Pin;

 Read_Pin = (GPIOx->IDR) >> GPIO_PIN;
 Read_Pin = Read_Pin & 0x01;

 return Read_Pin;
}



int main(void) {

	buzzer_Init();
	Led_init();
	button_Init();
	int count = 0;



	while (1)
	 {

		if(buttonReadStatus(BUTTON_GPIO_PORT, 4)==0)
		{
					delay();
					while(buttonReadStatus(BUTTON_GPIO_PORT, 4)==0){
						ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 1);
					}
		}
		if(buttonReadStatus(BUTTON_GPIO_PORT2, 0)==0)
				{
							delay();
							while(buttonReadStatus(BUTTON_GPIO_PORT2, 0)==0){
								ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 0);
							}
				}
	 }





//		if(buttonReadStatus(BUTTON_GPIO_PORT, 4)==0)
//				{
//					button_press_count ++;
//					if(button_press_count >= PRESS_THRESHOLD_LED_ON)
//					{
//						ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 1);
//						button_press_count = 0;
//						//ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 1);
//					}
//				}
//	 }
//	  while (buttonReadStatus(BUTTON_GPIO_PORT, 4) == 0) {
//		 // buzzerControlSetStatus(BUZZER_GPIO_PORT, 9, 1);
	//ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 1);
//
//		  //ledControlSetStatus(LED_GPIO_PORT2, LED_PIN3, 1);
//	  }
//	  ledControlSetStatus(LED_GPIO_PORT, LED_PIN5, 0);
//	  //ledControlSetStatus(LED_GPIO_PORT2, LED_PIN3, 0);
//	 // buzzerControlSetStatus(BUZZER_GPIO_PORT, 9, 0);
//	 }

	return 0;
}

/**
 * @func   delay
 * @brief  use when you want to delay
 * @param  None
 * @retval None
 */
void delay() {
	for (u32 i = 0; i < 5000000; i++);
}
void delay1()
{
	for (u32 i = 0; i < 100000; i++);
}


/**
 * @func   buzzer_Init
 * @brief  Initialize GPIO for buzzer
 * @param  None
 * @retval None
 */
static void buzzer_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(BUZZERControl_SetClock, ENABLE);


	GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;


	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;


	GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);

}

/**
 * @func   button_Init
 * @brief  Initialize GPIO for button
 * @param  None
 * @retval None
 */
static void button_Init(void) {

	GPIO_InitTypeDef GPIO_InitStructure;



	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock|BUTTONControl_SetClock2, ENABLE);


	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;


	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;


	GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN2;
	GPIO_Init(BUTTON_GPIO_PORT2, &GPIO_InitStructure);

}


/**
 * @func   buzzerControlSetStatus
 * @brief  control status buzzer
 * @param  Port, pin
 * @retval None
 */

