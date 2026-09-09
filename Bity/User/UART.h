#ifndef __UART
#define __UART

void USART1_Init(void);

void USART1_SendByte(uint8_t data);
void USART1_SendBytes(uint8_t *data, uint16_t len);

#endif
