
/**
* @file rgbw_driver.c
* @brief  Реализаций функций для работы драйвера
* @author [Ermakov Evgeniy]
* @date 10.05.2026
*/

#include "rgbw_driver.h"

/**
* @brief Вспомогательная cтатическая функция для передачи данных в регистры контроллера
* @param i2c_ch Используемый модуль I2C.
* @param reg Адресс регистра.
* @param data Данные.
* @return RGBW_Error_t Статус инициализации.
*/
static RGBW_Error_t RGBW_write_reg(I2C_Ch_t i2c_ch, uint8_t reg, uint8_t data)
{
    uint8_t data_buf[2] = {reg, data};

    if(I2C_Start(i2c_ch, RGBW_SLAVE_ADDR, I2C_DIR_WRITE) != I2C_ERR_SUCCESS)
    {
        return RGBW_ERR_I2C;
    }
    if(I2C_Write(i2c_ch, data_buf, DATA_LENGTH) != I2C_ERR_SUCCESS)
    {
        return RGBW_ERR_I2C;
    }
    if(I2C_Stop(i2c_ch) != I2C_ERR_SUCCESS)
    {
        return RGBW_ERR_I2C;
    }

    return RGBW_ERR_SUCCESS;
}

/**
* @brief Вспомогательная cтатическая функция для управления ШИМ регистрами
* @param i2c_ch Используемый модуль I2C.
* @param reg Адресс регистра.
* @param data Данные.
* @return RGBW_Error_t Статус выполнения.
*/
static RGBW_Error_t RGBW_write_pwm(I2C_Ch_t i2c_ch, uint8_t reg, uint8_t data)
{
    RGBW_Error_t status;

    status = RGBW_write_reg(i2c_ch, reg, data);
    if(status != RGBW_ERR_SUCCESS) return status;
    return RGBW_write_reg(i2c_ch, REG_PWM_UPD, UPD_CMD);
}

RGBW_Error_t RGBW_Init(I2C_Ch_t i2c_ch)
{
    
    RGBW_Error_t status;
    status = RGBW_write_reg(i2c_ch, REG_RESET, RESET_CMD);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    status = RGBW_write_reg(i2c_ch, REG_SHUTDOWN, SHUTDOWN_NORMAL);
    if(status != RGBW_ERR_SUCCESS) return status;

    status = RGBW_write_reg(i2c_ch, REG_LED_CTRL_1, LED_DIS);
    if(status != RGBW_ERR_SUCCESS) return status;

    status = RGBW_write_reg(i2c_ch, REG_LED_CTRL_2, LED_DIS);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    status = RGBW_write_reg(i2c_ch, REG_LED_CTRL_3, LED_DIS);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    status = RGBW_write_reg(i2c_ch, REG_LED_CTRL_4, LED_DIS);
    if(status != RGBW_ERR_SUCCESS) return status;

    status = RGBW_write_reg(i2c_ch, REG_PWM_UPD, UPD_CMD);
    if(status != RGBW_ERR_SUCCESS) return status;

    return status;
}

RGBW_Error_t RGBW_SetBrightness(I2C_Ch_t i2c_ch, RGBW_Ch_t channel, uint8_t brightness)
{
    if(channel > RGBW_CH_D4)
    {
        return RGBW_ERR_PARAM;
    }

    uint8_t reg = REG_PWM_1 + (uint8_t)channel;
    return RGBW_write_pwm(i2c_ch, reg, brightness);
}

RGBW_Error_t RGBW_SetLed(I2C_Ch_t i2c_ch, RGBW_Ch_t channel, bool state)
{
    if(channel > RGBW_CH_D4)
    {
        return RGBW_ERR_PARAM;
    }
    uint8_t reg = REG_LED_CTRL_1 + (uint8_t)channel;
    uint8_t data = state ? LED_EN : LED_DIS;
    RGBW_Error_t status;
    
    status = RGBW_write_reg(i2c_ch, reg, data);
    if(status != RGBW_ERR_SUCCESS) return status;

    return RGBW_write_reg(i2c_ch, REG_PWM_UPD, UPD_CMD);
}

RGBW_Error_t RGBW_SetAllLed(I2C_Ch_t i2c_ch, bool state)
{
    uint8_t data = state ? EN_ALL_LEDS : SHUTDOWN_ALL_LEDS;
    return RGBW_write_reg(i2c_ch, REG_GLOBAL_CTRL, data);
}

RGBW_Error_t RGBW_Set_RGB_Color(I2C_Ch_t i2c_ch, uint8_t red, uint8_t green, uint8_t blue)
{
    RGBW_Error_t status;

    status = RGBW_SetBrightness(i2c_ch, RGBW_CH_D1, red);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    status = RGBW_SetBrightness(i2c_ch, RGBW_CH_D2, green);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    status = RGBW_SetBrightness(i2c_ch, RGBW_CH_D3, blue);
    if(status != RGBW_ERR_SUCCESS) return status;
    
    return status;
}