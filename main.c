#include "stm32c0xx_hal.h"

#define LED_PIN GPIO_PIN_1
#define POT_PIN GPIO_PIN_2

#define PORT GPIOA

static void InitializeLED();
static void InitializePot();
void InitializeADC();
int Read_Potentiometer();

ADC_HandleTypeDef adc;


typedef struct{
  int id;
  int value;
  int status;
}Message;

int main(){

  HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  InitializeLED();
  InitializePot();
  InitializeADC();


  while(1){
    Read_Potentiometer();
    HAL_Delay(500);
  }
  return 0;
}

static void InitializeLED(){
  GPIO_InitTypeDef led = {0};

  led.Pin = LED_PIN;
  led.Mode = GPIO_MODE_OUTPUT_PP;
  led.Pull = GPIO_NOPULL;
  led.Speed = GPIO_SPEED_FREQ_LOW;  

  
  HAL_GPIO_Init(PORT, &led);
}

static void InitializePot(){
  GPIO_InitTypeDef pot = {0};

  pot.Pin = POT_PIN;
  pot.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(PORT, &pot);
}

void InitializeADC()
{
    ADC_ChannelConfTypeDef sConfig = {0};

    adc.Instance = ADC1;
    adc.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV1;
    adc.Init.Resolution            = ADC_RESOLUTION_12B;
    adc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    adc.Init.ScanConvMode          = ADC_SCAN_DISABLE;
    adc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    adc.Init.LowPowerAutoWait      = DISABLE;
    adc.Init.ContinuousConvMode    = DISABLE;
    acd.Init.NbrOfConversion       = 1;
    adc.Init.DiscontinuousConvMode = DISABLE;
    adc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    HAL_ADC_Init(&adc);

    sConfig.Channel      = ADC_CHANNEL_2;
    //sConfig.Rank         = ADC_REGULAR_RANK_1;
    //sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
    HAL_ADC_ConfigChannel(&adc, &sConfig);
}

int Read_Potentiometer()
{
    HAL_ADC_Start(&adc);
    HAL_ADC_PollForConversion(&adc, 10);
    int value = HAL_ADC_GetValue(&adc);
    HAL_ADC_Stop(&adc);
    printf("Ovo je vrijednost potenciometra: %d\n", value);
    return value;
}




