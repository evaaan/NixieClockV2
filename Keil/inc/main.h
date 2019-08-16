/*
* @author Evan Reeves
*/

#include "stm32f4xx_hal.h"

typedef struct {
  uint16_t hours;
  uint16_t minutes;
  uint16_t seconds;
}time;

void GPIO_Init(void);
HAL_StatusTypeDef RTC_Init(void);
void LSE_RTC_Init(void);
void main_loop(void);
void dev_loop(void);
void listen(void);
void ConfigureADC(void);
void EXTI_Init(void);
static void SystemClock_Config(void);


GPIO_PinState gpio_state(uint8_t);
void brightness_control(void);
void update_display(void);
void HAL_IncTick(void);
uint8_t int2bcd(uint8_t);

void inc_seconds(void);
void inc_minutes(void);
void inc_hours(void);

void set_seconds(uint8_t);
void set_minutes(uint8_t);
void set_hours(uint8_t);
void set_anniv(void);
void reset_clock(void);

uint8_t sec_pressed(void);
uint8_t min_pressed(void);
uint8_t hour_pressed(void);
uint8_t anniv_pressed(void);

