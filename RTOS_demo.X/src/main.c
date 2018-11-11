
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE

#include "FreeRTOS.h"
#include "croutine.h"
#include "task.h"

#include "../mcc_generated_files/system.h"
#include "../mcc_generated_files/pin_manager.h"

//RTOS tasks include
#include "app.h"
#include "taskBlinky.h"

/*****************************************************************************

    Private Macros

 *****************************************************************************/
/* Only one co-routine is created so the index is not significant. */
#define crfFLASH_INDEX             (0)
#define crf_HEART_BEAT_PRIORITY    (0)

/* The number of flash co-routines to create. */
#define mainNUM_FLASH_COROUTINES   (1)

/*****************************************************************************

    Private functions prototype

 *****************************************************************************/
static void taskHeartbeat_Init(unsigned portBASE_TYPE uxPriority);
static void taskHeartbeat_Execute(void);
static void prvMainCoRoutine(CoRoutineHandle_t xHandle, unsigned portBASE_TYPE uxIndex);


// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
int main( void )
{
    // initialize the device
    SYSTEM_Initialize();
    
    //=========================================================================
    //    Board initialization
    //=========================================================================
    

    //=========================================================================
    //    Set application's initial state
    //=========================================================================
    
    //=========================================================================
    //    Application Task initialization
    //=========================================================================
    taskBlinky_init();
    taskHeartbeat_Init(mainNUM_FLASH_COROUTINES);

    //=========================================================================
    //    FreeRTOS scheduler
    //=========================================================================
    vTaskStartScheduler();

    /* If all is well then this line will never be reached.  If it is reached
    then it is likely that there was insufficient (FreeRTOS) heap memory space
    to create the idle task.  This may have been trapped by the malloc() failed
    hook function, if one is configured.
    */
    
    while (1)
    {
        // Add your application code
    }
    
    return -1;
}


/*****************************************************************************

    FreeRTOS Task implementation: Co-routine running heart beat

 *****************************************************************************/
static void prvMainCoRoutine(CoRoutineHandle_t xHandle, unsigned portBASE_TYPE uxIndex)
{
    /* Co-routines MUST start with a call to crSTART. */
    crSTART(xHandle);

    for (;;)
    {
        crDELAY(xHandle, Time_MillisecondsToTicks(1000));

        taskHeartbeat_Execute();
    }

    /* Co-routines MUST end with a call to crEND. */
    crEND();
}

// *****************************************************************************
// Private functions implementation
// *****************************************************************************

static void taskHeartbeat_Init(unsigned portBASE_TYPE uxNumberToCreate)
{
    xCoRoutineCreate(prvMainCoRoutine, crf_HEART_BEAT_PRIORITY, crfFLASH_INDEX);
}

/*
    Process the heartbeat. This is done in the main event loop (as
    opposed to an interrupt) so we can see if the App has locked up.
*/
static void taskHeartbeat_Execute(void)
{
    portENTER_CRITICAL();
    {
        IO_RB15_Toggle();        //Toggle signal
    }
    portEXIT_CRITICAL();
}

/*******************************************************************************
 End of File
*/

