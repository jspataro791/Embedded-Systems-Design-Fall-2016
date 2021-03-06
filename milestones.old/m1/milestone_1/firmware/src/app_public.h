/* 
 * File:   app_public.h
 * Author: john
 *
 * Created on September 6, 2016, 4:10 PM
 */

#ifndef APP_PUBLIC_H
#define	APP_PUBLIC_H

#include "FreeRTOS.h"
#include "queue.h"
#include "system_definitions.h"

#ifdef	__cplusplus
extern "C" {
#endif

// TIMER Defines
#define QLENGTH 50
    
// Names to print
#define PRINTNAMES "JohnSpataro DannyDutton AndrewBryant BenjaminSingleton "
    
// Applications states
typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
	APP_STATE_SERVICE_TASKS,
    APP_STATE_IDLE,

	/* TODO: Define states used by the application state machine. */

} APP_STATES;

// Application data
typedef struct
{
    /* The application's current state */
    APP_STATES state;
    
    DRV_HANDLE handleUSART0; // USART driver handle
	int tx_count; // transmit byte
    
    unsigned int timerCount; // count of number of times timer has fired
    
    unsigned int timeEllapsed; // count of number of milliseconds that has ellapsed

    // handle for the msg queue
    QueueHandle_t appQHandle; 

} APP_DATA;

APP_DATA appData; // appdata instance

    // TIMER QUEUE STUFF

    // Inits the queue for this timing system
    QueueHandle_t appInitTimerMQ();

    // Sends current time to queue
    int appSendTimerValToMQ(QueueHandle_t q, unsigned int milliElapsed);
    
    #ifdef	__cplusplus
}
#endif

#endif	/* APP_PUBLIC_H */

