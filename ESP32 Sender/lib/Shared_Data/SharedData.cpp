#include "SharedDataI.h"
#include <Arduino.h>

void SharedData_Setup()
{
  for (int i = 0; i < SharedData_enMaxIDs; i++)
  {
    SharedData__Queues[i] = xQueueCreate(3, SharedData__Sizes[i]);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    if (SharedData__Queues[i] == NULL)
    {
      Serial.print("Error creating the queue ");
      Serial.println(i);
    }
  }
  SharedData__Addresses[SharedData_enTime] = (int *)&SharedData__Time;
}

void SharedData_ReadQueues()
{
  for (int i = 0; i < SharedData_enMaxIDs; i++)
  {
    if (xQueueReceive(SharedData__Queues[i], (void *)SharedData__Addresses[i], 0) == pdTRUE)
    {
      SharedData__Events[i]((SharedData_enIDs)i);
    }
  }
}

void SharedData_Get(SharedData_enIDs ID, void *const pvBuffer)
{
  if ((pvBuffer != NULL) && (SharedData__Addresses[ID] != NULL))
  {
    memcpy(pvBuffer, SharedData__Addresses[ID], SharedData__Sizes[ID]);
  }
}

void SharedData_Set(SharedData_enIDs ID, const void *const pvItemToQueue)
{
  if ((pvItemToQueue != NULL) && (SharedData__Queues[ID] != NULL))
  {
    (void)xQueueSend(SharedData__Queues[ID], pvItemToQueue, 10);
  }
}

/* functions for events */
void SharedData__Events_Time(SharedData_enIDs ID)
 {

 }