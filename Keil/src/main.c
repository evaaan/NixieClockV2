/*
* @author Evan Reeves
* @ date 2019-05-14
*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

uint16_t idx;
GPIO_InitTypeDef GPIO_InitStruct;

int main(void) {
  /* Initialize HAL Library. */
  HAL_Init();
  
  GPIO_Init();
  
	while(1) {
    // HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_10);
    // HAL_Delay(1000);
    
    for (idx = 0; idx < 10; idx++) {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, idx & 0x01);
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, idx & 0x02);
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, idx & 0x04);
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, idx & 0x08);
      HAL_Delay(1000);
    }
	}
}

void GPIO_Init(void) {
  /* SN74141 A OUTPUT - PD8 */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  /* SN74141 B OUTPUT - PD9 */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  
  /* SN74141 C OUTPUT - PD10 */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  
  /* SN74141 D OUTPUT - PD11 */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
