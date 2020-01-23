/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/**
  ******************************************************************************
  * @file    Multi/Examples/MotionControl/IHM01A1_ExampleFor1Motor/Src/main.c
  * @author  IPC Rennes
  * @version V1.10.0
  * @date    March 16th, 2018
  * @brief   This example shows how to use 1 IHM01A1 expansion board
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

static volatile uint16_t gLastError;

L6474_Init_t gL6474InitParams =
{
   160,                               /// Acceleration rate in step/s2. Range: (0..+inf).
   160,                               /// Deceleration rate in step/s2. Range: (0..+inf).
   1600,                              /// Maximum speed in step/s. Range: (30..10000].
   800,                               ///Minimum speed in step/s. Range: [30..10000).
   250,                               ///Torque regulation current in mA. (TVAL register) Range: 31.25mA to 4000mA.
   750,                               ///Overcurrent threshold (OCD_TH register). Range: 375mA to 6000mA.
   L6474_CONFIG_OC_SD_ENABLE,         ///Overcurrent shutwdown (OC_SD field of CONFIG register).
   L6474_CONFIG_EN_TQREG_TVAL_USED,   /// Torque regulation method (EN_TQREG field of CONFIG register).
   L6474_STEP_SEL_1_16,               /// Step selection (STEP_SEL field of STEP_MODE register).
   L6474_SYNC_SEL_1_2,                /// Sync selection (SYNC_SEL field of STEP_MODE register).
   L6474_FAST_STEP_12us,              /// Fall time value (T_FAST field of T_FAST register). Range: 2us to 32us.
   L6474_TOFF_FAST_8us,               /// Maximum fast decay time (T_OFF field of T_FAST register). Range: 2us to 32us.
   3,                                 /// Minimum ON time in us (TON_MIN register). Range: 0.5us to 64us.
   21,                                /// Minimum OFF time in us (TOFF_MIN register). Range: 0.5us to 64us.
   L6474_CONFIG_TOFF_044us,           /// Target Swicthing Period (field TOFF of CONFIG register).
   L6474_CONFIG_SR_320V_us,           /// Slew rate (POW_SR field of CONFIG register).
   L6474_CONFIG_INT_16MHZ,            /// Clock setting (OSC_CLK_SEL field of CONFIG register).
   (L6474_ALARM_EN_OVERCURRENT      |
    L6474_ALARM_EN_THERMAL_SHUTDOWN |
    L6474_ALARM_EN_THERMAL_WARNING  |
    L6474_ALARM_EN_UNDERVOLTAGE     |
    L6474_ALARM_EN_SW_TURN_ON       |
    L6474_ALARM_EN_WRONG_NPERF_CMD)    /// Alarm (ALARM_EN register).
};

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);

static void MyFlagInterruptHandler(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  int32_t pos;
  uint16_t mySpeed;
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  //----- Init of the Motor control library
  /* Set the L6474 library to use 1 device */
    BSP_MotorControl_SetNbDevices(BSP_MOTOR_CONTROL_BOARD_ID_L6474, 1);
    /* When BSP_MotorControl_Init is called with NULL pointer,                  */
    /* the L6474 registers and parameters are set with the predefined values from file   */
    /* l6474_target_config.h, otherwise the registers are set using the   */
    /* L6474_Init_t pointer structure                */
    /* The first call to BSP_MotorControl_Init initializes the first device     */
    /* whose Id is 0.                                                           */
    /* The nth call to BSP_MotorControl_Init initializes the nth device         */
    /* whose Id is n-1.                                                         */
    /* Uncomment the call to BSP_MotorControl_Init below to initialize the      */
    /* device with the structure gL6474InitParams declared in the the main.c file */
    /* and comment the subsequent call having the NULL pointer                   */
    //BSP_MotorControl_Init(BSP_MOTOR_CONTROL_BOARD_ID_L6474, &gL6474InitParams);
    BSP_MotorControl_Init(BSP_MOTOR_CONTROL_BOARD_ID_L6474, NULL);

    /* Attach the function MyFlagInterruptHandler (defined below) to the flag interrupt */
    BSP_MotorControl_AttachFlagInterrupt(MyFlagInterruptHandler);

    /* Attach the function Error_Handler (defined below) to the error Handler*/
    BSP_MotorControl_AttachErrorHandler(Error_Handler);

    //----- Move of 16000 steps in the FW direction
    /* Move device 0 of 16000 steps in the FORWARD direction*/
    BSP_MotorControl_Move(0, FORWARD, 16000);

    /* Wait for the motor of device 0 ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Move of 16000 steps in the BW direction

    /* Move device 0 of 16000 steps in the BACKWARD direction*/
    BSP_MotorControl_Move(0, BACKWARD, 16000);

    /* Wait for the motor of device 0 ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Get current position of device 0*/
    pos = BSP_MotorControl_GetPosition(0);

    /* Set the current position of device 0 to be the Home position */
    BSP_MotorControl_SetHome(0, pos);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Go to position -6400

    /* Request device 0 to go to position -6400 */
    BSP_MotorControl_GoTo(0,-6400);

    /* Wait for the motor ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Get current position of device 0*/
    pos = BSP_MotorControl_GetPosition(0);

    if (pos != -6400)
    {
      Error_Handler(11);
    }

    /* Set the current position of device 0 to be the Mark position */
    BSP_MotorControl_SetMark(0, pos);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Go Home

    /* Request device 0 to go to Home */
    BSP_MotorControl_GoHome(0);
    BSP_MotorControl_WaitWhileActive(0);

    /* Get current position of device 0 */
    pos = BSP_MotorControl_GetPosition(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Go to position 6400

    /* Request device 0 to go to position 6400 */
    BSP_MotorControl_GoTo(0,6400);

    /* Wait for the motor of device 0 ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Get current position of device 0*/
    pos = BSP_MotorControl_GetPosition(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Go Mark which was set previously after go to -6400

    /* Request device 0 to go to Mark position */
    BSP_MotorControl_GoMark(0);

    /* Wait for the motor of device 0 ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Get current position of device 0 */
    pos = BSP_MotorControl_GetPosition(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Run the motor BACKWARD

    /* Request device 0 to run BACKWARD */
     BSP_MotorControl_Run(0,BACKWARD);
     HAL_Delay(5000);

     /* Get current speed of device 0 */
     mySpeed = BSP_MotorControl_GetCurrentSpeed(0);

  //----- Increase the speed while running

    /* Increase speed of device 0 to 2400 step/s */
    BSP_MotorControl_SetMaxSpeed(0,2400);
    HAL_Delay(5000);

     /* Get current speed of device 0 */
     mySpeed = BSP_MotorControl_GetCurrentSpeed(0);

  //----- Decrease the speed while running

    /* Decrease speed of device 0 to 1200 step/s */
    BSP_MotorControl_SetMaxSpeed(0,1200);
    HAL_Delay(5000);

    /* Get current speed */
    mySpeed = BSP_MotorControl_GetCurrentSpeed(0);

  //----- Increase acceleration while running

    /* Increase acceleration of device 0 to 480 step/s^2 */
    BSP_MotorControl_SetAcceleration(0,480);
    HAL_Delay(5000);

    /* Increase speed of device 0 to 2400 step/s */
    BSP_MotorControl_SetMaxSpeed(0,2400);
    HAL_Delay(5000);

    /* Get current speed of device 0 */
    mySpeed = BSP_MotorControl_GetCurrentSpeed(0);

    if (mySpeed != 2400)
    {
      Error_Handler(10);
    }
  //----- Increase deceleration while running

    /* Increase deceleration of device 0 to 480 step/s^2 */
    BSP_MotorControl_SetDeceleration(0,480);
    HAL_Delay(5000);

    /* Decrease speed of device 0 to 1200 step/s */
    BSP_MotorControl_SetMaxSpeed(0,1200);
    HAL_Delay(5000);

    /* Get current speed */
    mySpeed = BSP_MotorControl_GetCurrentSpeed(0);

  //----- Soft stopped required while running

    /* Request soft stop of device 0 */
    BSP_MotorControl_SoftStop(0);

    /* Wait for the motor of device 0 ends moving */
    BSP_MotorControl_WaitWhileActive(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Run stopped by hardstop

    /* Request device 0 to run in FORWARD direction */
    BSP_MotorControl_Run(0,FORWARD);
    HAL_Delay(5000);

    /* Request device 0 to immediatly stop */
    BSP_MotorControl_HardStop(0);
    BSP_MotorControl_WaitWhileActive(0);

    /* Request device 0 to disable bridge */
    BSP_MotorControl_CmdDisable(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- GOTO stopped by softstop

   /* Request device 0 to go to position 20000  */
    BSP_MotorControl_GoTo(0,20000);
    HAL_Delay(5000);

    /* Request device 0 to perform a soft stop */
    BSP_MotorControl_SoftStop(0);
    BSP_MotorControl_WaitWhileActive(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

    //----- Read inexistent register to test MyFlagInterruptHandler

    /* Try to read an inexistent register */
    /* the flag interrupt should be raised */
    /* and the MyFlagInterruptHandler function called */
    BSP_MotorControl_CmdGetParam(0,0x1F);
    HAL_Delay(500);

  //----- Change step mode to full step mode

    /* Select full step mode for device 0 */
     BSP_MotorControl_SelectStepMode(0,STEP_MODE_FULL);

    /* Set speed and acceleration to be consistent with full step mode */
     BSP_MotorControl_SetMaxSpeed(0,100);
     BSP_MotorControl_SetMinSpeed(0,50);
     BSP_MotorControl_SetAcceleration(0,10);
     BSP_MotorControl_SetDeceleration(0,10);

    /* Request device 0 to go position 200 */
     BSP_MotorControl_GoTo(0,200);

    /* Wait for the motor of device 0 ends moving */
     BSP_MotorControl_WaitWhileActive(0);

    /* Get current position */
    pos =  BSP_MotorControl_GetPosition(0);

    /* Wait for 2 seconds */
    HAL_Delay(2000);

  //----- Restore 1/16 microstepping mode

    /* Reset device 0 to 1/16 microstepping mode */
    BSP_MotorControl_SelectStepMode(0,STEP_MODE_1_16);

    /* Update speed, acceleration, deceleration for 1/16 microstepping mode*/
    BSP_MotorControl_SetMaxSpeed(0,1600);
    BSP_MotorControl_SetMinSpeed(0,800);
    BSP_MotorControl_SetAcceleration(0,160);
    BSP_MotorControl_SetDeceleration(0,160);

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  /* Request device 0 to go position -6400 */
	      BSP_MotorControl_GoTo(0,-6400);

	      /* Wait for the motor of device 0 ends moving */
	      BSP_MotorControl_WaitWhileActive(0);

	      /* Request device 0 to go position 6400 */
	      BSP_MotorControl_GoTo(0,6400);

	      /* Wait for the motor of device 0 ends moving */
	      BSP_MotorControl_WaitWhileActive(0);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler(0);
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler(0);
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  heth.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
  heth.Init.MACAddr[0] =   0x00;
  heth.Init.MACAddr[1] =   0x80;
  heth.Init.MACAddr[2] =   0xE1;
  heth.Init.MACAddr[3] =   0x00;
  heth.Init.MACAddr[4] =   0x00;
  heth.Init.MACAddr[5] =   0x00;
  heth.Init.RxMode = ETH_RXPOLLING_MODE;
  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;

  /* USER CODE BEGIN MACADDRESS */
    
  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler(0);
  }
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler(0);
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler(0);
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is the User handler for the flag interrupt
  * @param  None
  * @retval None
  */
void MyFlagInterruptHandler(void)
{
  /* Get the value of the status register via the L6474 command GET_STATUS */
  uint16_t statusRegister = BSP_MotorControl_CmdGetStatus(0);

  /* Check HIZ flag: if set, power brigdes are disabled */
  if ((statusRegister & L6474_STATUS_HIZ) == L6474_STATUS_HIZ)
  {
    // HIZ state
    // Action to be customized
  }

  /* Check direction bit */
  if ((statusRegister & L6474_STATUS_DIR) == L6474_STATUS_DIR)
  {
    // Forward direction is set
    // Action to be customized
  }
  else
  {
    // Backward direction is set
    // Action to be customized
  }

  /* Check NOTPERF_CMD flag: if set, the command received by SPI can't be performed */
  /* This often occures when a command is sent to the L6474 */
  /* while it is in HIZ state */
  if ((statusRegister & L6474_STATUS_NOTPERF_CMD) == L6474_STATUS_NOTPERF_CMD)
  {
      // Command received by SPI can't be performed
     // Action to be customized
  }

  /* Check WRONG_CMD flag: if set, the command does not exist */
  if ((statusRegister & L6474_STATUS_WRONG_CMD) == L6474_STATUS_WRONG_CMD)
  {
     //command received by SPI does not exist
     // Action to be customized
  }

  /* Check UVLO flag: if not set, there is an undervoltage lock-out */
  if ((statusRegister & L6474_STATUS_UVLO) == 0)
  {
     //undervoltage lock-out
     // Action to be customized
  }

  /* Check TH_WRN flag: if not set, the thermal warning threshold is reached */
  if ((statusRegister & L6474_STATUS_TH_WRN) == 0)
  {
    //thermal warning threshold is reached
    // Action to be customized
  }

  /* Check TH_SHD flag: if not set, the thermal shut down threshold is reached */
  if ((statusRegister & L6474_STATUS_TH_SD) == 0)
  {
    //thermal shut down threshold is reached
    // Action to be customized
  }

  /* Check OCD  flag: if not set, there is an overcurrent detection */
  if ((statusRegister & L6474_STATUS_OCD) == 0)
  {
    //overcurrent detection
    // Action to be customized
  }

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  error number of the error
  * @retval None
  */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(uint16_t error)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
	gLastError = error;

	while(1);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
