#ifndef SharedDataI_h
#define SharedDataI_h

#include "SharedDataE.h"

int SharedData__Time;

static QueueHandle_t SharedData__Queues[SharedData_enMaxIDs];

const int SharedData__Sizes[SharedData_enMaxIDs] =
    {
     //sizeof(stLightsData)
     sizeof(int)
    };

static int *SharedData__Addresses[SharedData_enMaxIDs];

/* functions for events */
void SharedData__Events_Time(SharedData_enIDs);

static void (*SharedData__Events[SharedData_enMaxIDs])(SharedData_enIDs) =
    {
        //&SharedData__Events_LightsData
        &SharedData__Events_Time
        };
#endif

