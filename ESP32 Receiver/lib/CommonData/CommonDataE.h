/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonDataE.h
 *
 * Description  : This module is responsable of data used commonly in more than one
 *                module
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 10.06.2021    CatGyo  Initial revision
 */
#ifndef CommonDataE_h
#define CommonDataE_h

#include <Arduino.h>

enum CommonData_enIDs
{
  CommonData_enIncommingData = 0,
  CommonData_enMaxIDs
};

void CommonData_Setup();
void CommonData_ReadQueues();
void CommonData_Get(CommonData_enIDs, void *const pvBuffer); // id ce memorie acceseaza
void CommonData_Set(CommonData_enIDs, const void *const);
#endif