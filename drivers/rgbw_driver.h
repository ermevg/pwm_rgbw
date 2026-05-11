/**
* @file rgbw_driver.h
* @brief Описание функций и необходимых параметров для работы драйвера контроллера RGBW
* @author [Ermakov Evgeniy]
* @date 10.05.2026
*/

#ifndef RGBW_DRIVER_H
#define RGBW_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "ic2_interface.h"

/**
 * @brief Адрес ведомого устройства, поскольку в задании не указано к чему подключены пины AD
 * считаю что они к земле подтянуты и AD = 00.
 * @note 7 бит адреса: 0111100 = 0x3C.
 */
#define RGBW_SLAVE_ADDR (0x3CU)

/**
 * @brief Адреса регистров контроллера RGBW.
 */
#define REG_SHUTDOWN    (0x00U)
#define REG_PWM_1       (0x05U)
#define REG_PWM_2       (0x06U)
#define REG_PWM_3       (0x07U)
#define REG_PWM_4       (0x08U)
#define REG_PWM_UPD     (0x25U)
#define REG_LED_CTRL_1  (0x2AU)
#define REG_LED_CTRL_2  (0x2BU)
#define REG_LED_CTRL_3  (0x2CU)
#define REG_LED_CTRL_4  (0x2DU)
#define REG_GLOBAL_CTRL (0x4AU)
#define REG_FREQ_SET    (0x4BU)
#define REG_RESET       (0x4FU)

/**
 * @brief Битовые маски управления и команд.
 */
#define SHUTDOWN_SOFTWARE (0x00U)
#define SHUTDOWN_NORMAL   (0x01U)
#define SHUTDOWN_ALL_LEDS (0x01U)
#define EN_ALL_LEDS       (0x00U)
#define LED_EN            (0x01U)
#define LED_DIS           (0x00U)
#define RESET_CMD         (0x00U)
#define LED_FREQ_3KHZ     (0x00U)
#define LED_FREQ_22KHZ    (0x01U)
#define UPD_CMD           (0x00U)

/**
 * @brief Количество байт данных для передачи.
 */
#define DATA_LENGTH (2U)

/**
 * @brief Уровни яркости каналов
 */
#define OFF_BRIGHTNESS (0U)
#define HALF_BRIGHTNESS (128U)
#define FULL_BRIGHTNESS (255U)

/**
 * @brief Вкл/Выкл канал
 */
#define CH_ON  (true)
#define CH_OFF (false)

/**
 * @brief Перечисление ошибок драйвера - сделал по аналогии с I2C.
 */
typedef enum
{
    RGBW_ERR_SUCCESS  = (0U),
    RGBW_ERR_I2C      = (1U),
    RGBW_ERR_PARAM    = (2U)
} RGBW_Error_t;

/**
 * @brief Перечисление каналов R, G, B, W.
 */
typedef enum
{
    RGBW_CH_D1  = (0U),
    RGBW_CH_D2  = (1U),
    RGBW_CH_D3  = (2U),
    RGBW_CH_D4  = (3U)
} RGBW_Ch_t;

/**
* @brief Инициализация RGBW контроллера (вход в рабочий режим, и отключение светодиодов).
* @param i2c_ch Используемый модуль I2C.
* @return RGBW_Error_t Статус инициализации.
*/
RGBW_Error_t RGBW_Init(I2C_Ch_t i2c_ch);

/**
* @brief Индивидуальная настройка яркости каналов D1, D2, D3, D4.
* @param i2c_ch Используемый модуль I2C.
* @param channel Настраиваемый канал (D1, D2, D3, D4).
* @param brightness Значение яркости (0-255).
* @return RGBW_Error_t Статус инициализации.
*/
RGBW_Error_t RGBW_SetBrightness(I2C_Ch_t i2c_ch, RGBW_Ch_t channel, uint8_t brightness);

/**
* @brief Включение выключение каждого канала по отдельности
* @param i2c_ch Используемый модуль I2C.
* @param channel Настраиваемый канал (D1, D2, D3, D4).
* @param state Состояние канала (ВКЛ/ВЫКЛ).
* @return RGBW_Error_t Статус инициализации.
*/
RGBW_Error_t RGBW_SetLed(I2C_Ch_t i2c_ch, RGBW_Ch_t channel, bool state);

/**
* @brief Включение выключение всех каналов одновременно
* @param i2c_ch Используемый модуль I2C.
* @param state Состояние каналов (ВКЛ/ВЫКЛ).
* @return RGBW_Error_t Статус инициализации.
*/
RGBW_Error_t RGBW_SetAllLed(I2C_Ch_t i2c_ch, bool state);

/**
* @brief Установка цвета для каждого канала D1, D2, D3.
* @param i2c_ch Используемый модуль I2C.
* @param red Яркость канала D1.
* @param green Яркость канала D2.
* @param blue Яркость канала D3.
* @return RGBW_Error_t Статус инициализации.
*/
RGBW_Error_t RGBW_Set_RGB_Color(I2C_Ch_t i2c_ch, uint8_t red, uint8_t green, uint8_t blue);

#endif