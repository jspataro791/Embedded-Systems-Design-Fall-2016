

#ifndef SERIALFSM_H    /* Guard against multiple inclusion */
#define SERIALFSM_H

#include "system_definitions.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WAITING_START, WAITING_DATA, WAITING_END,
} state_type;


typedef struct {
    state_type state;

    unsigned char dataBytesReceived;

    unsigned char temporaryBytes[SERIAL_DATA_BYTES_PER_MESSAGE];


} SERIAL_DATA;


SERIAL_DATA serialData;


void runSerialFrame(unsigned char c);

#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */