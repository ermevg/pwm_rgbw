/**
* @file system_init.h
* @author [Ermakov Evgeniy]
* @date 10.05.2026
*/

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include "main.h"

/**
* @brief Функция заглушка для линковщика -т.к она вызывается из стартап файла.
*/
void SystemInit(void);

/**
* @brief Функция заглушка - настройка тактирования МК.
*/
void SystemClock_Config(void);


#endif