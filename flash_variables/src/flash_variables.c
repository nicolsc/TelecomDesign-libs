/******************************************************************************
 * @file
 * @brief Flash Variable demonstration application for the TDxxxx RF modules.
 * @author Telecom Design S.A.
 * @version 1.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Telecom Design S.A., http://www.telecomdesign.fr</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Telecom Design SA has no
 * obligation to support this Software. Telecom Design SA is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Telecom Design SA will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

#include <efm32.h>

#include <em_gpio.h>

#include <td_sigfox.h>
#include <td_core.h>
#include <td_uart.h>
#include <td_printf.h>
#include <td_flash.h>
#include <td_watchdog.h>

/* This file declare all "dynamic" library data. It should be last included file
 * Standard size value can be override before including this file
 */

#define TD_SENSOR_USE_CODE 0
#define TD_GEOLOC_USE_CODE 0
#define FLASH_VARIABLES_VERSION 1
#define TD_SIGFOX_PROXY_REMOVE_CODE
#include <td_config.h>

/*******************************************************************************
 ******************************  VARIABLE  ************************************
 ******************************************************************************/
/** Test value 1 */
static uint32_t value1;

/** Test value 2 */
static uint32_t value2;

/*******************************************************************************
 **************************   PUBLIC FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   User setup function.
 ******************************************************************************/
void TD_USER_Setup(void)
{
	// Initialize the UART console
	init_printf(TD_UART_Init(9600, true, false),
		TD_UART_Putc,
		TD_UART_Start,
		TD_UART_Stop);

	tfp_printf("BOOT\r\n");

	// Declare value1
	if (!TD_FLASH_DeclareVariable((uint8_t *) &value1, sizeof (uint32_t), 0)) {
		tfp_printf("Value1 not found in Flash, set default\r\n");
		value1 = 42;
	} else {
		tfp_printf("Value1 found in Flash: %d\r\n", value1);
	}

	// Declare value2
	if (!TD_FLASH_DeclareVariable((uint8_t *) &value2, sizeof (uint32_t), 0)) {
		tfp_printf("Value2 not found in Flash, set default\r\n");
		value2 = 43;
	} else {
		tfp_printf("Value2 found in Flash: %d\r\n", value2);
	}

	// Change variable values
	value1++;
	value2 += 2;

#if 1
	// Write to Flash
	TD_FLASH_WriteVariables();
#endif

	// Reset all flash variables
	if (value1 == 60) {
		tfp_printf("Delete all variables\r\n");
		TD_FLASH_DeleteVariables();
	}

	// Reboot automatically
	NVIC_SystemReset();
}

/***************************************************************************//**
 * @brief
 *   User loop function.
 ******************************************************************************/
void TD_USER_Loop(void)
{
}
