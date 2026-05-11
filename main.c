/**
* @file main.c
* @brief  Файл исходного кода main с примером использования дравйвера контроллера
* @author [Ermakov Evgeniy]
* @date 10.05.2026
*/

#include "main.h"
#include "system_init.h"
#include "rgbw_driver.h"



int main (void){

    /*Настройка тактирования МК - заглушка для примера*/
    SystemClock_Config();

    /*Инициализация I2C интерфейса - 1 модуль(канал), частота 400 кГц*/
    if(I2C_Init(I2C_CH0, I2C_FREQ_400_KHZ) != I2C_ERR_SUCCESS)
    {
        while(1); // В случае ошибки уходим в цикл
    }
    
    /*Инициализация RGBW контроллера*/
    if(RGBW_Init(I2C_CH0) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }

    /*Пример включения отдельного канала*/
    if(RGBW_SetLed(I2C_CH0, RGBW_CH_D4, CH_ON) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }
    
    /*Пример установки канала на половину яркости*/
    if(RGBW_SetBrightness(I2C_CH0, RGBW_CH_D4, HALF_BRIGHTNESS) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }
   
     /*Пример установки цвета RGB - 255, 128, 0 - Оранжевый*/
    if(RGBW_Set_RGB_Color(I2C_CH0, FULL_BRIGHTNESS, HALF_BRIGHTNESS, OFF_BRIGHTNESS) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }

    /*Пример выключения всех каналов*/
    if(RGBW_SetAllLed(I2C_CH0, CH_OFF) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }

    /*Пример включения всех каналов*/
    if(RGBW_SetAllLed(I2C_CH0, CH_ON) != RGBW_ERR_SUCCESS)
    {
        while(1);
    }

    while(1)
    {
        
    }

    return 0;
}
