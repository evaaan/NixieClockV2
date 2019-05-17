/*
* @author Evan Reeves
* @ date 2019-05-14
*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

uint16_t idx;
volatile time clock;

GPIO_InitTypeDef GPIO_InitStruct;

int main(void) {
  /* Initialize HAL Library. */
  HAL_Init();
  
  /* Initialize GPIOs */
  GPIO_Init();
  
  clock.hours = 0;
  clock.minutes = 0;
  clock.seconds = 0;
  
	while(1) {
    update();
    HAL_Delay(1000);
    inc_seconds();
	}
}

/* Update Nixie Tubes */
void update(void) {
  uint16_t sec, sec_ones, sec_tens;
  sec = int2bcd(clock.seconds);
  sec_ones = sec & 0x0F;
  sec_tens = (sec & 0xF0) >> 4;
  
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, sec_tens & 0x01);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, sec_tens & 0x02);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, sec_tens & 0x04);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, sec_tens & 0x08);
}

/* Convert integer (0 to 0x63) to binary-coded decimal (0x00 to 0x99)*/
uint16_t int2bcd(uint16_t val) {
  return ((val / 10) << 4) | (val % 10);
}

/* Time update methods */
void inc_seconds(void) {
  if (clock.seconds == 59) {
    clock.seconds = 0;
    inc_minutes();
  } else {
    clock.seconds += 1;
  }
}

void inc_minutes(void) {
  if (clock.minutes == 59) {
    clock.minutes = 0;
    inc_hours();
  } else {
    clock.minutes += 1;
  }
}

void inc_hours(void) {
  if (clock.hours == 12) {
    clock.hours = 1;
  } else {
    clock.hours += 1;
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
