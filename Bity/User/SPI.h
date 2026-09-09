#ifndef __SPI
#define __SPI

#define SPIPort GPIOC
#define SPIMISO GPIO_Pin_7
#define SPIMOSI GPIO_Pin_6
#define SPISCL GPIO_Pin_5

//ScreenSPI
#define ScreenSPIDC GPIO_Pin_4//@PC
#define ScreenSPICS GPIO_Pin_2//@PC
#define ScreenSPIRST GPIO_Pin_3//@PC

//FlashSPI
#define FlashSPICS GPIO_Pin_0//@PD
#define FlashSPIRST GPIO_Pin_1//@PC
#define FlashSPIWP GPIO_Pin_0//@PC

void SPIPeriphInit(void);
void SPISendByte(uint8_t Byte);

void ScreenSPISendCommand(uint8_t Command);
void ScreenSPISendData(uint8_t Data8);
void ScreenSPISendData16(uint16_t Data16);
void ScreenSPISendData16WithCommand(uint16_t Data16);
void ScreenSPISendData16sWithCommand(uint16_t Data16, uint16_t Times);

#endif