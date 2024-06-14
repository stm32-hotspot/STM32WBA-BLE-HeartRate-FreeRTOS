/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ll_sys_if.c
  * @author  MCD Application Team
  * @brief   Source file for initiating system
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "app_common.h"
#include "main.h"
#include "ll_intf.h"
#include "ll_sys.h"
#include "ll_sys_if.h"
#include "cmsis_os2.h"
#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
#include "temp_measurement.h"
#endif /* (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1) */

/* Private defines -----------------------------------------------------------*/

/* LINK_LAYER_TASK related defines */
#define LINK_LAYER_TASK_STACK_SIZE              (512 * 4)
#define LINK_LAYER_TASK_PRIO                    (osPriorityNormal)

/* LINK_LAYER_TEMP_MEAS_TASK related defines */
#define LINK_LAYER_TEMP_MEAS_TASK_STACK_SIZE    (128 * 4)
#define LINK_LAYER_TEMP_MEAS_TASK_PRIO          (osPriorityNormal)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private constants ---------------------------------------------------------*/
/* USER CODE BEGIN PC */

/* USER CODE END PC */

/* Private variables ---------------------------------------------------------*/
/* LINK_LAYER_TEMP_MEAS_TASK related resources */
osSemaphoreId_t         LinkLayerMeasSemaphore;
osThreadId_t            LinkLayerMeasThread;

/* LINK_LAYER_TASK related resources */
osSemaphoreId_t         LinkLayerSemaphore;
osThreadId_t            LinkLayerThread;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Global variables ----------------------------------------------------------*/

/* LINK_LAYER_TASK related resources */
osMutexId_t             LinkLayerMutex;

/* USER CODE BEGIN GV */

/* USER CODE END GV */

/* Private functions prototypes-----------------------------------------------*/
#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
static void ll_sys_bg_temperature_measurement_init(void);
#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Functions Definition ------------------------------------------------------*/

/**
 * @brief  Link Layer Task for FreeRTOS
 * @param  void *argument
 * @retval None
 */
static void LinkLayerSys_Task_Entry(void *argument)
{
  UNUSED( argument );

  for(;;)
  {
    osSemaphoreAcquire(LinkLayerSemaphore, osWaitForever);
    osMutexAcquire(LinkLayerMutex, osWaitForever);
    ll_sys_bg_process();
    osMutexRelease(LinkLayerMutex);
    osThreadYield();
  }
}

/**
  * @brief  Link Layer background process initialization
  * @param  None
  * @retval None
  */
void ll_sys_bg_process_init(void)
{
  /* Tasks creation */
  const osSemaphoreAttr_t LinkLayerSemaphore_attributes = {
    .name = "LinkLayerSemaphore"
  };
  LinkLayerSemaphore = osSemaphoreNew(1U, 0U, &LinkLayerSemaphore_attributes);
  if (LinkLayerSemaphore == NULL)
  {
    Error_Handler();
  }
  const osMutexAttr_t LinkLayerMutex_attributes = {
    .name = "LinkLayer Mutex"
  };
  LinkLayerMutex = osMutexNew(&LinkLayerMutex_attributes);
  if (LinkLayerMutex == NULL)
  {
    Error_Handler();
  }
  const osThreadAttr_t LinkLayerTask_attributes = {
    .name = "Link Layer Task",
    .priority = (osPriority_t) LINK_LAYER_TASK_PRIO,
    .stack_size = LINK_LAYER_TASK_STACK_SIZE
  };
  LinkLayerThread = osThreadNew(LinkLayerSys_Task_Entry, NULL, &LinkLayerTask_attributes);
  if (LinkLayerThread == NULL)
  {
    Error_Handler();
  }
}

/**
  * @brief  Link Layer background process next iteration scheduling
  * @param  None
  * @retval None
  */
void ll_sys_schedule_bg_process(void)
{
  osSemaphoreRelease(LinkLayerSemaphore);
}

/**
  * @brief  Link Layer background process next iteration scheduling from ISR
  * @param  None
  * @retval None
  */
void ll_sys_schedule_bg_process_isr(void)
{
  osSemaphoreRelease(LinkLayerSemaphore);
}

/**
  * @brief  Link Layer configuration phase before application startup.
  * @param  None
  * @retval None
  */
void ll_sys_config_params(void)
{
  uint16_t freq_value = 0;
  uint32_t linklayer_slp_clk_src = LL_RCC_RADIOSLEEPSOURCE_NONE;

  /* Configure link layer behavior for low ISR use and next event scheduling method:
   * - SW low ISR is used.
   * - Next event is scheduled from ISR.
   */
  ll_intf_config_ll_ctx_params(USE_RADIO_LOW_ISR, NEXT_EVENT_SCHEDULING_FROM_ISR);

  linklayer_slp_clk_src = LL_RCC_RADIO_GetSleepTimerClockSource();
  switch(linklayer_slp_clk_src)
  {
    case LL_RCC_RADIOSLEEPSOURCE_LSE:
      linklayer_slp_clk_src = RTC_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_LSI:
      linklayer_slp_clk_src = RCO_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_HSE_DIV1000:
      linklayer_slp_clk_src = CRYSTAL_OSCILLATOR_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_NONE:
      /* No Link Layer sleep clock source selected */
      assert_param(0);
      break;
  }
  ll_intf_le_select_slp_clk_src((uint8_t)linklayer_slp_clk_src, &freq_value);

#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
  /* Initialize link layer temperature measurement background task */
  ll_sys_bg_temperature_measurement_init();

  /* Link layer IP uses temperature based calibration instead of periodic one */
  ll_intf_set_temperature_sensor_state();
#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */

  /* Link Layer power table */
  ll_intf_select_tx_power_table(CFG_RF_TX_POWER_TABLE_ID);
}

#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
/**
 * @brief  Link Layer Temperature Measurement Task for FreeRTOS
 * @param
 * @retval None
 */
 static void LinkLayerTempMeasure_Task_Entry( void *argument )
{
  UNUSED( argument );

  for(;;)
  {
    osSemaphoreAcquire(LinkLayerMeasSemaphore, osWaitForever);
    osMutexAcquire(LinkLayerMutex, osWaitForever);
    TEMPMEAS_RequestTemperatureMeasurement();
    osMutexRelease(LinkLayerMutex);
    osThreadYield();
  }
}

/**
  * @brief  Link Layer temperature request background process initialization
  * @param  None
  * @retval None
  */
void ll_sys_bg_temperature_measurement_init(void)
{

  const osSemaphoreAttr_t LinkLayerMeasSemaphore_attributes = {
    .name = "LinkLayerMeasSemaphore"
  };
  LinkLayerMeasSemaphore = osSemaphoreNew(1U, 0U, &LinkLayerMeasSemaphore_attributes);
  if (LinkLayerMeasSemaphore == NULL)
  {
    Error_Handler();
  }

  const osThreadAttr_t LinkLayerMeasTask_attributes = {
    .name = "LinkLayer Temp Measurement Task",
    .priority = (osPriority_t) LINK_LAYER_TEMP_MEAS_TASK_PRIO,
    .stack_size = LINK_LAYER_TEMP_MEAS_TASK_STACK_SIZE
  };
  LinkLayerMeasThread = osThreadNew(LinkLayerTempMeasure_Task_Entry, NULL, &LinkLayerMeasTask_attributes);
  if (LinkLayerMeasThread == NULL)
  {
    Error_Handler();
  }
}

/**
  * @brief  Request backroud task processing for temperature measurement
  * @param  None
  * @retval None
  */
void ll_sys_bg_temperature_measurement(void)
{
  static uint8_t initial_temperature_acquisition = 0;

  if(initial_temperature_acquisition == 0)
  {
    TEMPMEAS_RequestTemperatureMeasurement();
    initial_temperature_acquisition = 1;
  }
  else
  {
    osSemaphoreRelease(LinkLayerMeasSemaphore);
  }
}

#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */
