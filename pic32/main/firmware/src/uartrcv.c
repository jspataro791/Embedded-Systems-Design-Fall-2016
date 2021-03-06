
/* This task simply initializes the UART0 receive message queue,
 *  it does not do anything otherwise, currently */

#include "uartrcv.h"
#include "serialfsm.h"

#define UART0_RCV_QUEUE_SIZE 100

/* define UART0 rcv message queue */
QueueHandle_t uart0RcvQueue;
char rcvTaskByteBuffer;

/* serial state setup*/
extern SERIAL_DATA serialData;

/* init */
void UARTRCV_Initialize( void ) {
    
    /* set GPIO status to this init */
    sendGPIOStatus(STAT_TASK_RX_INIT);
    
    /* initialized UART0 rcv message queue */
    uart0RcvQueue = xQueueCreate( UART0_RCV_QUEUE_SIZE, sizeof (char ) );
    
    /* halt if can't create msg queue, fatal */
    if(uart0RcvQueue == 0) {
        sendGPIOError(ERR_BAD_MQ_CREATE);
    }
    
    /* set serial finite state machine to wait for start byte */
    serialData.state = WAITING_START;

}

/* main task */
void UARTRCV_Tasks( void ) {
    
    /* set GPIO status to this task */
    sendGPIOStatus(STAT_TASK_RX);
    
    
    /* wait for something to enter the UART0 rcv message queue */
    int QRcvChk = xQueueReceive( uart0RcvQueue, &rcvTaskByteBuffer, portMAX_DELAY );
    
    
    /* if we have a good message queue receive */
    if ( QRcvChk == pdTRUE ) {
        
        /* set GPIO status to a good read */
        sendGPIOStatus(STAT_TASK_RX_GOOD);

        /* check byte by byte in serial fsm for complete frame */
        runSerialFrame( rcvTaskByteBuffer );

    }

}



/*******************************************************************************
 End of File
 */
