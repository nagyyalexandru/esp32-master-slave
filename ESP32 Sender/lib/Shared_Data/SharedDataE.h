#ifndef SharedDataE_h
#define SharedDataE_h

#include <Arduino.h>

enum SharedData_enIDs
{
  SharedData_enTime = 0,
  SharedData_enMaxIDs
};

void SharedData_Setup();
void SharedData_ReadQueues();
void SharedData_Get(SharedData_enIDs, void *const pvBuffer); // id ce memorie acceseaza
void SharedData_Set(SharedData_enIDs, const void *const);
#endif