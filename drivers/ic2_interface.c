/**
* @file i2c_interface.c
* @brief I2C functions description
* @note In a real implementation these functions would comfigure hardware registers
* @author [Ermakov Evgeniy]
* @date 10.05.2026
*/

#include "ic2_interface.h"

I2C_Error_t I2C_Init(const I2C_Ch_t i2c_ch, const I2C_Freq_t i2c_freq)
{
    (void)i2c_ch;
    (void)i2c_freq;
    return I2C_ERR_SUCCESS;
}

I2C_Error_t I2C_Start(const I2C_Ch_t i2c_ch, const BYTE i2c_addr, const I2C_Dir_t direction)
{
    (void)i2c_ch;
    (void)i2c_addr;
    (void)direction;
    return I2C_ERR_SUCCESS;
}

I2C_Error_t I2C_Stop(const I2C_Ch_t i2c_ch)
{
    (void)i2c_ch;
    return I2C_ERR_SUCCESS;
}

I2C_Error_t I2C_Read(const I2C_Ch_t i2c_ch, uint8_t* data_bytes, const uint16_t length)
{
    (void)i2c_ch;
    (void)data_bytes;
    (void)length;
    return I2C_ERR_SUCCESS;
}

I2C_Error_t I2C_Write(const I2C_Ch_t i2c_ch, const uint8_t* data_bytes, const uint16_t length)
{
    (void)i2c_ch;
    (void)data_bytes;
    (void)length;
    return I2C_ERR_SUCCESS;
}