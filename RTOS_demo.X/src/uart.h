
#ifndef UART_H
#define	UART_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    extern void uart_init(void);
    extern void uart_buildBuffer(uint8_t ch);
    extern uint8_t* uart_getBufferHandle(void);
    extern void uart_flush(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

