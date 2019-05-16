/*
* @author Evan Reeves
* @ date 2019-05-14
*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

uint32_t idx;
GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
  /* Initialize HAL Library. */
  HAL_Init();
  
  GPIO_Init();
  
	while(1) {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    HAL_Delay(500);
	}
}

void GPIO_Init(void)
{
  
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
