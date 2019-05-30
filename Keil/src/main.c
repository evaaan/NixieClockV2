/*
* @author Evan Reeves
* @ date 2019-05-14
*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "math.h"

uint16_t idx;
uint16_t delay, delay_start, delay_inc, delay_end; 
uint16_t delay_inc;
uint16_t delay_end;
uint32_t total_delay;
uint32_t g_ADCValue = 0;
uint32_t g_MeasurementNumber;

extern uint32_t tick;
float freq;
float delay_f;
volatile time clock;

GPIO_InitTypeDef GPIO_InitStruct;
ADC_HandleTypeDef g_AdcHandle;

int main(void) {
  /* Initialize HAL Library. */
  HAL_Init();
  
  /* Initialize GPIOs */
  GPIO_Init();
  
  /* Initialize system clock and ADC */
  SystemClock_Config();
  ConfigureADC();
  HAL_ADC_Start(&g_AdcHandle);
  
  clock.hours = 0;
  clock.minutes = 0;
  clock.seconds = 0;
  freq = 3;
  delay_inc = 0;
  delay_start = 1000;
  delay_end = 1000;
  
  delay = delay_start;
  
	while(1) {
    HAL_Delay(delay_start);
    update_display();
    inc_seconds();
    
    /*
    HAL_Delay(g_ADCValue);
    if (HAL_ADC_PollForConversion(&g_AdcHandle, 1000000) == HAL_OK) {
      g_ADCValue = HAL_ADC_GetValue(&g_AdcHandle);
      g_MeasurementNumber++;
    }
    */
   
	}
}

/* Update Nixie Tubes */
void update_display(void) {
  uint16_t sec, sec_ones, sec_tens, output;
  sec = int2bcd(clock.seconds);
  sec_ones = sec & 0x0F;
  sec_tens = (sec & 0xF0) >> 4;
  
  output = sec_ones;
  
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, output & 0x01);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, output & 0x02);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, output & 0x04);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, output & 0x08);
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
  
  /* SN74141 B OUTPUT - PA8 */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  
  /* SN74141 C OUTPUT - PB8 */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  
  /* SN74141 D OUTPUT - PC8 */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void SystemClock_Config(void)
{
  /* Based on example from https://visualgdb.com/tutorials/arm/stm32/adc/ */
  
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 288;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 6;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  SystemCoreClockUpdate();
  
  if (HAL_GetREVID() == 0x1001)
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
}
 
void ConfigureADC(void)
{
  /* Based on example from https://visualgdb.com/tutorials/arm/stm32/adc/ */
  
  GPIO_InitTypeDef gpioInit;
  
  __GPIOC_CLK_ENABLE();
  __ADC1_CLK_ENABLE();
  
  gpioInit.Pin = GPIO_PIN_1;
  gpioInit.Mode = GPIO_MODE_ANALOG;
  gpioInit.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &gpioInit);
  
  HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADC_IRQn);
  
  ADC_ChannelConfTypeDef adcChannel;
  
  g_AdcHandle.Instance = ADC1;
  
  g_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  g_AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  g_AdcHandle.Init.ScanConvMode = DISABLE;
  g_AdcHandle.Init.ContinuousConvMode = ENABLE;
  g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  g_AdcHandle.Init.NbrOfDiscConversion = 0;
  g_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  g_AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  g_AdcHandle.Init.NbrOfConversion = 1;
  g_AdcHandle.Init.DMAContinuousRequests = ENABLE;
  g_AdcHandle.Init.EOCSelection = DISABLE;
  
  HAL_ADC_Init(&g_AdcHandle);
  
  adcChannel.Channel = ADC_CHANNEL_11;
  adcChannel.Rank = 1;
  adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  adcChannel.Offset = 0;
  
  if (HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel) != HAL_OK)
  {
    asm("bkpt 255");
  }
}
