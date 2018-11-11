#include <stdint.h>

#define BUF_SIZE    20

static uint8_t _buf[BUF_SIZE];    //buffer to hold string
static uint8_t index = 0;       //buffer index

void uart_init(void)
{
    index = 0;
}

void uart_buildBuffer(uint8_t ch)
{
    _buf[index] = ch;
    index++;
    
    //prevent buffer overrun
    if(index >= BUF_SIZE)
        index = 0;
    else
        _buf[index] = 0;  //zero-terminate the current buffer
}

uint8_t* uart_getBufferHandle(void)
{
    return &_buf[0];
}

void uart_flush(void)
{
    index = 0;
}