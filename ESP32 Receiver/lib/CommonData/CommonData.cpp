/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonData.cpp
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

#include "CommonDataI.h"
#include <Arduino.h>
// #define CD__DEBUG

void CommonData_Setup()
{
  for (int i = 0; i < CommonData_enMaxIDs; i++)
  {
    CommonData__Queues[i] = xQueueCreate(3, CommonData__Sizes[i]);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    if (CommonData__Queues[i] == NULL)
    {
      Serial.print("Error creating the queue ");
      Serial.println(i);
    }
  }
  CommonData__Addresses[CommonData_enIncommingData] = (int *)&CommonData__IncommingData;
}

void CommonData_ReadQueues()
{
  for (int i = 0; i < CommonData_enMaxIDs; i++)
  {
    if (xQueueReceive(CommonData__Queues[i], (void *)CommonData__Addresses[i], 0) == pdTRUE)
    {
      CommonData__Events[i]((CommonData_enIDs)i);
    }
  }
}

void CommonData_Get(CommonData_enIDs ID, void *const pvBuffer)
{
  if ((pvBuffer != NULL) && (CommonData__Addresses[ID] != NULL))
  {
    memcpy(pvBuffer, CommonData__Addresses[ID], CommonData__Sizes[ID]);
  }
}

void CommonData_Set(CommonData_enIDs ID, const void *const pvItemToQueue)
{
  if ((pvItemToQueue != NULL) && (CommonData__Queues[ID] != NULL))
  {
    (void)xQueueSend(CommonData__Queues[ID], pvItemToQueue, 10);
  }
}

/* functions for events */
void CommonData__Events_IncommingData(CommonData_enIDs ID)
{

}