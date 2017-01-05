/***********************************************************************************
Copyright (c) Nordic Semiconductor ASA
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  3. Neither the name of Nordic Semiconductor ASA nor the names of other
  contributors to this software may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************************************************/

/**@file
 *
 * @defgroup bsp Board Support Package
 * @{
 * @ingroup app_common
 *
 * @brief BSP module.
 * @details This module provides a layer of abstraction from the board.
 *          It allows the user to indicate certain states on LEDs in a simple way.
 *          Module functionality can be modified by additional defines:
 *          - BSP_SIMPLE reduces functionality of this module to enable 
 *            and read state of the buttons
 *          - BSP_UART_SUPPORT enables support for UART
 */

#ifndef BSP_H__
#define BSP_H__

#include <stdint.h>
#include <stdbool.h>
#include "boards.h"

/* BSP_UART_SUPPORT
 * This define enable uart support module.
 */
#ifdef BSP_UART_SUPPORT
#include "app_uart.h"
#endif // BSP_UART_SUPPORT

#define BUTTON_ERASE_BONDING BSP_BUTTON_0_MASK
#define BUTTON_ERASE_ALL     BSP_BUTTON_1_MASK
#define BUTTON_ADVERTISE     BSP_BUTTON_0_MASK
#define BUTTON_CLEAR_EVT     BSP_BUTTON_1_MASK
#define BUTTON_CAPSLOCK      BSP_BUTTON_2_MASK
#define BSP_BUTTONS_ALL      0xFFFFFFFF
#define BSP_BUTTONS_NONE     0

#if LEDS_NUMBER > 0
/**@def BSP_APP_TIMERS_NUMBER
 * Number of @ref app_timer instances required by BSP with LED support
 */
#define BSP_APP_TIMERS_NUMBER 2
#endif // LEDS_NUMBER > 0

/**@brief Types of BSP initialization
 */
#define BSP_INIT_NONE    0        /**< This define specifies the type of initialization without support for LEDs and buttons @ref bsp_init.*/
#define BSP_INIT_LED     (1 << 0) /**< This bit enables LEDs during initialization (@ref bsp_init).*/
#define BSP_INIT_BUTTONS (1 << 1) /**< This bit enables buttons during initialization (@ref bsp_init).*/
#define BSP_INIT_UART    (1 << 2) /**< This bit enables UART during initialization (@ref bsp_init).*/

#define BSP_INDICATIONS_LIST {                    \
        "BSP_INDICATE_IDLE\n\r",                  \
        "BSP_INDICATE_SCANNING\n\r",              \
        "BSP_INDICATE_ADVERTISING\n\r",           \
        "BSP_INDICATE_ADVERTISING_WHITELIST\n\r", \
        "BSP_INDICATE_ADVERTISING_SLOW\n\r",      \
        "BSP_INDICATE_ADVERTISING_DIRECTED\n\r",  \
        "BSP_INDICATE_BONDING\n\r",               \
        "BSP_INDICATE_CONNECTED\n\r",             \
        "BSP_INDICATE_SENT_OK\n\r",               \
        "BSP_INDICATE_SEND_ERROR\n\r",            \
        "BSP_INDICATE_RCV_OK\n\r",                \
        "BSP_INDICATE_RCV_ERROR\n\r",             \
        "BSP_INDICATE_FATAL_ERROR\n\r",           \
        "BSP_INDICATE_ALERT_0\n\r",               \
        "BSP_INDICATE_ALERT_1\n\r",               \
        "BSP_INDICATE_ALERT_2\n\r",               \
        "BSP_INDICATE_ALERT_3\n\r",               \
        "BSP_INDICATE_ALERT_OFF\n\r",             \
        "BSP_INDICATE_USER_STATE_OFF\n\r",        \
        "BSP_INDICATE_USER_STATE_0\n\r",          \
        "BSP_INDICATE_USER_STATE_1\n\r",          \
        "BSP_INDICATE_USER_STATE_2\n\r",          \
        "BSP_INDICATE_USER_STATE_3\n\r",          \
        "BSP_INDICATE_USER_STATE_ON\n\r"          \
} /**< See @ref examples_bsp_states for a list of how these states are indicated for the PCA10028 board and the PCA10031 dongle.*/


/**@brief BSP indication states.
 *
 * @details See @ref examples_bsp_states for a list of how these states are indicated for the PCA10028 board and the PCA10031 dongle.
 */
typedef enum
{
    BSP_INDICATE_FIRST = 0,
    BSP_INDICATE_IDLE  = BSP_INDICATE_FIRST, /**< See \ref BSP_INDICATE_IDLE.*/
    BSP_INDICATE_SCANNING,                   /**< See \ref BSP_INDICATE_SCANNING.*/
    BSP_INDICATE_ADVERTISING,                /**< See \ref BSP_INDICATE_ADVERTISING.*/
    BSP_INDICATE_ADVERTISING_WHITELIST,      /**< See \ref BSP_INDICATE_ADVERTISING_WHITELIST.*/
    BSP_INDICATE_ADVERTISING_SLOW,           /**< See \ref BSP_INDICATE_ADVERTISING_SLOW.*/
    BSP_INDICATE_ADVERTISING_DIRECTED,       /**< See \ref BSP_INDICATE_ADVERTISING_DIRECTED.*/
    BSP_INDICATE_BONDING,                    /**< See \ref BSP_INDICATE_BONDING.*/
    BSP_INDICATE_CONNECTED,                  /**< See \ref BSP_INDICATE_CONNECTED.*/
    BSP_INDICATE_SENT_OK,                    /**< See \ref BSP_INDICATE_SENT_OK.*/
    BSP_INDICATE_SEND_ERROR,                 /**< See \ref BSP_INDICATE_SEND_ERROR.*/
    BSP_INDICATE_RCV_OK,                     /**< See \ref BSP_INDICATE_RCV_OK.*/
    BSP_INDICATE_RCV_ERROR,                  /**< See \ref BSP_INDICATE_RCV_ERROR.*/
    BSP_INDICATE_FATAL_ERROR,                /**< See \ref BSP_INDICATE_FATAL_ERROR.*/
    BSP_INDICATE_ALERT_0,                    /**< See \ref BSP_INDICATE_ALERT_0.*/
    BSP_INDICATE_ALERT_1,                    /**< See \ref BSP_INDICATE_ALERT_1.*/
    BSP_INDICATE_ALERT_2,                    /**< See \ref BSP_INDICATE_ALERT_2.*/
    BSP_INDICATE_ALERT_3,                    /**< See \ref BSP_INDICATE_ALERT_3.*/
    BSP_INDICATE_ALERT_OFF,                  /**< See \ref BSP_INDICATE_ALERT_OFF.*/
    BSP_INDICATE_USER_STATE_OFF,             /**< See \ref BSP_INDICATE_USER_STATE_OFF.*/
    BSP_INDICATE_USER_STATE_0,               /**< See \ref BSP_INDICATE_USER_STATE_0.*/
    BSP_INDICATE_USER_STATE_1,               /**< See \ref BSP_INDICATE_USER_STATE_1.*/
    BSP_INDICATE_USER_STATE_2,               /**< See \ref BSP_INDICATE_USER_STATE_2.*/
    BSP_INDICATE_USER_STATE_3,               /**< See \ref BSP_INDICATE_USER_STATE_3.*/
    BSP_INDICATE_USER_STATE_ON,              /**< See \ref BSP_INDICATE_USER_STATE_ON.*/
    BSP_INDICATE_LAST = BSP_INDICATE_USER_STATE_ON
} bsp_indication_t;

/**@brief BSP events.
 *
 * @note Events from BSP_EVENT_KEY_0 to BSP_EVENT_KEY_LAST are by default assigned to buttons.
 */
typedef enum
{
    BSP_EVENT_NOTHING = 0,                  /**< This will unassign button from event. */
    BSP_EVENT_CLEAR_BONDING_DATA,
    BSP_EVENT_CLEAR_ALERT,
    BSP_EVENT_DISCONNECT,
    BSP_EVENT_ADVERTISING_START,
    BSP_EVENT_ADVERTISING_STOP,
    BSP_EVENT_BOND,
    BSP_EVENT_RESET,
    BSP_EVENT_SLEEP,
    BSP_EVENT_WAKEUP,
    BSP_EVENT_DFU,
    BSP_EVENT_KEY_0,                        /**< This event is by default assigned to BSP_BUTTON_0 (only if this button is present). */
    BSP_EVENT_KEY_1,                        /**< This event is by default assigned to BSP_BUTTON_1 (only if this button is present). */
    BSP_EVENT_KEY_2,                        /**< This event is by default assigned to BSP_BUTTON_2 (only if this button is present). */
    BSP_EVENT_KEY_3,                        /**< This event is by default assigned to BSP_BUTTON_3 (only if this button is present). */
    BSP_EVENT_KEY_4,                        /**< This event is by default assigned to BSP_BUTTON_4 (only if this button is present). */
    BSP_EVENT_KEY_5,                        /**< This event is by default assigned to BSP_BUTTON_5 (only if this button is present). */
    BSP_EVENT_KEY_6,                        /**< This event is by default assigned to BSP_BUTTON_6 (only if this button is present). */
    BSP_EVENT_KEY_7,                        /**< This event is by default assigned to BSP_BUTTON_7 (only if this button is present). */
    BSP_EVENT_KEY_LAST = BSP_EVENT_KEY_7,
} bsp_event_t;

/**@brief BSP module event callback function type.
 *
 * @details Upon an event in the BSP module, this callback function will be called to notify
 *          the application about the event.
 *
 * @param[in]   bsp_event_t BSP event type.
 */
typedef void (* bsp_event_callback_t)(bsp_event_t);

/**@brief       Function for initializing BSP.
 *
 * @details     Initialize the board support package to allow state indication and button
 *              reaction. Default events are assigned to buttons.
 * @note        Before calling this function, you must initiate the following required modules:
 *              - @ref app_timer for LED support
 *              - @ref app_gpiote for button support
 *              - @ref app_uart for UART support
 *
 * @param[in]   type               Type of peripherals used.
 * @param[in]   ticks_per_100ms    Number of RTC ticks for 100 ms.
 * @param[in]   callback           Function to be called when button press/event is detected.
 *
 * @retval      NRF_SUCCESS               BSP module was successfully initialized.
 * @retval      NRF_ERROR_INVALID_STATE   Application timer module has not been initialized.
 * @retval      NRF_ERROR_NO_MEM          Maximum number of timers has already been reached.
 * @retval      NRF_ERROR_INVALID_PARAM   GPIOTE has too many users.
 * @retval      NRF_ERROR_INVALID_STATE   Button or GPIOTE not initialized.
 */
uint32_t bsp_init(uint32_t type, uint32_t ticks_per_100ms, bsp_event_callback_t callback);

/**@brief       Function for getting buttons states.
 *
 * @details     This function allows to get the state of all buttons.
 *
 * @param[in]   p_buttons_state          This variable will store buttons state. Button 0 state is
 *                                       represented by bit 0 (1=pressed), Button 1 state by bit 1, and so on.
 *
 * @retval      NRF_SUCCESS              Buttons state was successfully read.
 */
uint32_t bsp_buttons_state_get(uint32_t * p_buttons_state);

/**@brief       Function for checking buttons states.
 *
 * @details     This function for checking if the button is pressed.
 *
 * @param[in]   button                   Button ID to check.
 * @param[in]   p_state                  This variable will store the information whether the specified button is pressed(true) or not.
 *
 * @retval      NRF_SUCCESS              Button state was successfully read.
 * @retval      NRF_ERROR_INVALID_PARAM  Invalid button ID.
 */
uint32_t bsp_button_is_pressed(uint32_t button, bool * p_state);

/**@brief       Function for assigning specific event to button.
 *
 * @details     This function allows redefinition of standard events assigned to buttons.
 *              To unassign events, provide the event @ ref BSP_EVENT_NOTHING.
 *
 * @param[in]   button                   Button ID to be redefined.
 * @param[in]   event                    Event to be assigned to button.
 *
 * @retval      NRF_SUCCESS              Event was successfully assigned to button.
 * @retval      NRF_ERROR_INVALID_PARAM  Invalid button ID.
 */
uint32_t bsp_event_to_button_assign(uint32_t button, bsp_event_t event);

/**@brief       Function for configuring indicators to required state.
 *
 * @details     This function indicates the required state by means of LEDs (if enabled).
 *
 * @note        Alerts are indicated independently.
 *
 * @param[in]   indicate   State to be indicated.
 *
 * @retval      NRF_SUCCESS               State was successfully indicated.
 * @retval      NRF_ERROR_NO_MEM          Internal timer operations queue was full.
 * @retval      NRF_ERROR_INVALID_STATE   Application timer module has not been initialized,
 *                                        or internal timer has not been created.
 */
uint32_t bsp_indication_set(bsp_indication_t indicate);

/**@brief       Function for configuring indicators to required state.
 *
 * @details     This function indicates the required state by means of LEDs (if enabled)
 *              and UART (if enabled).
 *
 * @note        Alerts are indicated independently.
 *
 * @param[in]   indicate   State to be indicated.
 * @param[in]   p_text     Text to be output on UART.
 *
 * @retval      NRF_SUCCESS               State was successfully indicated.
 * @retval      NRF_ERROR_NO_MEM          Internal timer operations queue was full.
 * @retval      NRF_ERROR_INVALID_STATE   Application timer module has not been initialized, or timer
 *                                        has not been created.
 */
uint32_t bsp_indication_text_set(bsp_indication_t indicate, const char * p_text);

/**@brief       Function for enabling specified buttons (others are disabled).
 *
 * @details     This function enables the specified buttons and configures them to be scanned.
 *              All other buttons are disabled (inactive).
 *
 * @param[in]   buttons  Buttons to be enabled, encoded as bits
 *                       (bit 0 = button 0, bit 1 = button 1, etc).
 *
 * @retval      NRF_SUCCESS Successfully enabled.
 */
uint32_t bsp_buttons_enable(uint32_t buttons);

#endif // BSP_H__

/** @} */
