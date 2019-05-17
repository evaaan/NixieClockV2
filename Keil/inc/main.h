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
void inc_seconds(void);
void inc_minutes(void);
void inc_hours(void);
void update(void);
uint16_t int2bcd(uint16_t);
