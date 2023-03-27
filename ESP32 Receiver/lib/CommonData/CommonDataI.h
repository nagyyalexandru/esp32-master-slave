/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonDataI.h
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
#ifndef CommonDataI_h
#define CommonDataI_h

#include "CommonDataE.h"
#include "ESP_MESSAGES_E.h"

struct_message CommonData__IncommingData;

static QueueHandle_t CommonData__Queues[CommonData_enMaxIDs];

const int CommonData__Sizes[CommonData_enMaxIDs] =
    {
     sizeof(CommonData__IncommingData)
    };

static int *CommonData__Addresses[CommonData_enMaxIDs];

/* functions for events */
void CommonData__Events_IncommingData(CommonData_enIDs);

static void (*CommonData__Events[CommonData_enMaxIDs])(CommonData_enIDs) =
    {
        &CommonData__Events_IncommingData
        };
#endif

