#include <ch32v00X.h>
#include "debug.h"
#include "SPI.h"
#include "Screen.h"
#include "Font.h"

//四色映射表
#define Color00 0XFFF7
#define Color01 0XD692
#define Color10 0X6B89
#define Color11 0X4207

/*----LCDPart----*/
void LCDInit(void){
    Delay_Init();

    SPIPeriphInit();

    GPIO_WriteBit(GPIOC, ScreenSPIRST, Bit_RESET);
    Delay_Ms(200);
    GPIO_WriteBit(GPIOC, ScreenSPIRST, Bit_SET);
    Delay_Ms(200);

    // 1. 软件复位
    ScreenSPISendCommand(0x01);
    Delay_Ms(120);

    // 2. 退出睡眠
    ScreenSPISendCommand(0x11);
    Delay_Ms(120);

    // 3. 设置颜色格式：RGB565
    ScreenSPISendCommand(0x3A);
    ScreenSPISendData(0x55);  // 0x55 = 16bit RGB565

    // 4. 屏幕方向设置
    ScreenSPISendCommand(0x36);
    //ScreenSPISendData(0x68);//正向
    ScreenSPISendData(0xA8);//反向

    //5. 清空屏幕
    LCDClear(0x0000);
    // 6. 开显示
    ScreenSPISendCommand(0x29);
}

void LCDSetLocation(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd){
    //单个点XS与XE相等即可
    XEnd -= 1;

    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(XStart >> 8));
    ScreenSPISendData((uint8_t)(XStart));
    ScreenSPISendData((uint8_t)(XEnd >> 8));
    ScreenSPISendData((uint8_t)(XEnd));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)(YStart >> 8));
    ScreenSPISendData((uint8_t)(YStart));
    ScreenSPISendData((uint8_t)(YEnd >> 8));
    ScreenSPISendData((uint8_t)(YEnd));
    
}

void LCDDrawPoint(uint16_t X, uint16_t Y, uint16_t Color){
    LCDSetLocation(X, Y + 24, X, Y + 24);
    ScreenSPISendData16WithCommand(Color);
}

void LCDClear(uint16_t BackgroundColor){
    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(0 >> 8));
    ScreenSPISendData((uint8_t)(0));
    ScreenSPISendData((uint8_t)((160 - 1) >> 8));
    ScreenSPISendData((uint8_t)(160 - 1));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)(24 >> 8));
    ScreenSPISendData((uint8_t)(24));
    ScreenSPISendData((uint8_t)((104) >> 8));
    ScreenSPISendData((uint8_t)(104));

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    for(uint64_t Bit = 0; Bit < 12800; Bit ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(BackgroundColor >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(BackgroundColor));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void LCDClearArea(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd, uint16_t BackgroundColor){
    uint64_t PixNum = (XEnd - XStart) * (YEnd - YStart);

    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(XStart >> 8));
    ScreenSPISendData((uint8_t)(XStart));
    ScreenSPISendData((uint8_t)((XEnd - 1) >> 8));
    ScreenSPISendData((uint8_t)(XEnd - 1));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)((YStart + 24) >> 8));
    ScreenSPISendData((uint8_t)(YStart + 24));
    ScreenSPISendData((uint8_t)((YEnd + 24) >> 8));
    ScreenSPISendData((uint8_t)(YEnd + 24));

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    for(uint64_t Bit = 0; Bit < PixNum; Bit ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(BackgroundColor >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(BackgroundColor));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void LCDDrawBitmap(const uint16_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H){
    YStart += 24;

    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(XStart >> 8));
    ScreenSPISendData((uint8_t)(XStart));
    ScreenSPISendData((uint8_t)((XStart + W - 1) >> 8));
    ScreenSPISendData((uint8_t)(XStart + W - 1));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)(YStart >> 8));
    ScreenSPISendData((uint8_t)(YStart));
    ScreenSPISendData((uint8_t)((YStart + H) >> 8));
    ScreenSPISendData((uint8_t)(YStart + H));

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    for(uint64_t Bit = 0; Bit < W*H; Bit ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(Bitmap[Bit] >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(Bitmap[Bit]));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }

    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

void LCDDrawMonoBitmap(const uint8_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H, uint16_t HighColor, uint16_t LowColor, uint8_t UseAlpha){
    for(uint16_t Page = 0; Page < H / 8; Page ++){
        for(uint16_t X = 0; X < W; X ++){
            for(int8_t Bit = 7; Bit >= 0; Bit --){
                if(UseAlpha){
                    if(((Bitmap[X + Page * W] >> Bit) & 0x01))LCDDrawPoint(XStart + X, YStart + Page * 8 + Bit, HighColor);
                }
                else{
                    if(((Bitmap[X + Page * W] >> Bit) & 0x01))LCDDrawPoint(XStart + X, YStart + Page * 8 + Bit, HighColor);
                    else LCDDrawPoint(XStart + X, YStart + Page * 8 + Bit, LowColor);
                }
            }
        }
    }
}

void LCDDrawMonoBitmapQuick(const uint8_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H, uint16_t HighColor, uint16_t LowColor){
    YStart += 24;

    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(XStart >> 8));
    ScreenSPISendData((uint8_t)(XStart));
    ScreenSPISendData((uint8_t)((XStart + W - 1) >> 8));
    ScreenSPISendData((uint8_t)(XStart + W - 1));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)(YStart >> 8));
    ScreenSPISendData((uint8_t)(YStart));
    ScreenSPISendData((uint8_t)((YStart + H) >> 8));
    ScreenSPISendData((uint8_t)(YStart + H));

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    
    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
    //Line:实际显示的行
    //Offset:实际显示的列
    for(uint16_t Line = 0; Line < H; Line ++){
        for(uint16_t Offset = 0; Offset < W; Offset ++){
            //((Line / 8) * W):在输入数组的偏移
            if((Bitmap[((Line / 8) * W) + Offset] & (0x01 << (Line % 8))) == 0){
                SPI_I2S_SendData(SPI1, (uint8_t)(LowColor >> 8));
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
                SPI_I2S_SendData(SPI1, (uint8_t)(LowColor));
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            }
            else{
                SPI_I2S_SendData(SPI1, (uint8_t)(HighColor >> 8));
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
                SPI_I2S_SendData(SPI1, (uint8_t)(HighColor));
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
                while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            }
        }
    }
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
}

/**
 * @brief 绘制地图瓷砖
 * 
 * @param Tile 瓷砖贴图数组
 * @param TileOffset 瓷砖序列数组
 * @param TileSize 瓷砖实际像素长（宽）
 * @param MapWidth 行瓷砖个数
 * @param MapHeight 列瓷砖个数
 * @param XOffset 屏幕起始X坐标
 * @param Yoffset 屏幕起始Y坐标
 */
void LCDDrawTile(const uint16_t *Tile, const uint8_t *TileOffset, uint8_t TileSize, uint8_t MapWidth, uint8_t MapHeight, uint8_t XOffset, uint8_t YOffset){  
    //遍历每一个图块序列
    for(uint16_t TileOffsetSeq = 0; TileOffsetSeq < (uint16_t)MapWidth * MapHeight; TileOffsetSeq ++){
        //确定每个图块绘制起点
        uint8_t X = XOffset + (TileOffsetSeq % MapWidth) * TileSize;
        uint8_t Y = YOffset + (TileOffsetSeq / MapWidth) * TileSize;

        //确定图块在Tile中的位置
        uint64_t TileStartSeq = TileOffset[TileOffsetSeq] * TileSize * TileSize;

        //设置图块范围
        LCDSetLocation(X, Y, X + TileSize, Y + TileSize);

        //填充图块
        GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
        GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

        SPI_I2S_SendData(SPI1, 0x2C);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

        GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);
        
        for(uint8_t TileSeq = 0; TileSeq < TileSize * TileSize; TileSeq ++){
            SPI_I2S_SendData(SPI1, (uint8_t)(Tile[TileStartSeq + TileSeq] >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(Tile[TileStartSeq + TileSeq]));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
        GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_SET);
    }
}
/**
 * @brief LCD绘制进度条
 * 
 */
void LCDDrawBar(uint16_t XStart, uint16_t YStart, uint16_t Len, float FullNum, float ShowNum, uint16_t BlankColor, uint16_t OutlineColor, uint16_t ShowbarColor){
    if(Len < 5)return;

    uint16_t ShowNumBarLen = (uint16_t)((ShowNum / FullNum) * (Len - 2) + 0.5f);

    ScreenSPISendCommand(0x2A);
    ScreenSPISendData((uint8_t)(XStart >> 8));
    ScreenSPISendData((uint8_t)(XStart));
    ScreenSPISendData((uint8_t)((XStart + Len - 1) >> 8));
    ScreenSPISendData((uint8_t)(XStart + Len - 1));

    ScreenSPISendCommand(0x2B);
    ScreenSPISendData((uint8_t)((YStart + 24) >> 8));
    ScreenSPISendData((uint8_t)(YStart + 24));
    ScreenSPISendData((uint8_t)((YStart + 29) >> 8));
    ScreenSPISendData((uint8_t)(YStart + 29));

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_RESET);
    GPIO_WriteBit(GPIOC, ScreenSPICS, Bit_RESET);

    SPI_I2S_SendData(SPI1, 0x2C);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);

    GPIO_WriteBit(GPIOC, ScreenSPIDC, Bit_SET);

    /*第一行*/
    for(uint16_t Bit = 0; Bit < Len; Bit ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }
    /*第二行*/
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    for(uint16_t Bit = 1; Bit < Len - 1; Bit ++){
        if(Bit <= ShowNumBarLen){
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
        else{
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
    }
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    /*第三行*/
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    for(uint16_t Bit = 1; Bit < Len - 1; Bit ++){
        if(Bit <= ShowNumBarLen){
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
        else{
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
    }
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    /*第四行*/
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    for(uint16_t Bit = 1; Bit < Len - 1; Bit ++){
        if(Bit <= ShowNumBarLen){
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(ShowbarColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
        else{
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor >> 8));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
            SPI_I2S_SendData(SPI1, (uint8_t)(BlankColor));
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
            while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        }
    }
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    /*第五行*/
    for(uint16_t Bit = 0; Bit < Len; Bit ++){
        SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor >> 8));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
        SPI_I2S_SendData(SPI1, (uint8_t)(OutlineColor));
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    }
}

void LCDDrawWords(uint16_t XStart, uint16_t YStart, uint8_t *Words, uint16_t WordsLen, uint16_t HighColor, uint16_t LowColor){
    uint8_t X = XStart;
    uint8_t Y = YStart;
    for(uint16_t Bit = 0; Bit < WordsLen; Bit ++){
        switch(Words[Bit]){
            case 'A':{LCDDrawMonoBitmapQuick(Font_Word_1, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'a':{LCDDrawMonoBitmapQuick(Font_Word_1, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'B':{LCDDrawMonoBitmapQuick(Font_Word_2, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'b':{LCDDrawMonoBitmapQuick(Font_Word_2, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'C':{LCDDrawMonoBitmapQuick(Font_Word_3, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'c':{LCDDrawMonoBitmapQuick(Font_Word_3, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'D':{LCDDrawMonoBitmapQuick(Font_Word_4, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'd':{LCDDrawMonoBitmapQuick(Font_Word_4, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'E':{LCDDrawMonoBitmapQuick(Font_Word_5, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'e':{LCDDrawMonoBitmapQuick(Font_Word_5, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'F':{LCDDrawMonoBitmapQuick(Font_Word_6, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'f':{LCDDrawMonoBitmapQuick(Font_Word_6, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'G':{LCDDrawMonoBitmapQuick(Font_Word_7, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'g':{LCDDrawMonoBitmapQuick(Font_Word_7, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'H':{LCDDrawMonoBitmapQuick(Font_Word_8, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'h':{LCDDrawMonoBitmapQuick(Font_Word_8, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'I':{LCDDrawMonoBitmapQuick(Font_Word_9, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'i':{LCDDrawMonoBitmapQuick(Font_Word_9, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'J':{LCDDrawMonoBitmapQuick(Font_Word_10, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'j':{LCDDrawMonoBitmapQuick(Font_Word_10, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'K':{LCDDrawMonoBitmapQuick(Font_Word_11, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'k':{LCDDrawMonoBitmapQuick(Font_Word_11, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'L':{LCDDrawMonoBitmapQuick(Font_Word_12, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'l':{LCDDrawMonoBitmapQuick(Font_Word_12, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'M':{LCDDrawMonoBitmapQuick(Font_Word_13, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'm':{LCDDrawMonoBitmapQuick(Font_Word_13, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'N':{LCDDrawMonoBitmapQuick(Font_Word_14, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'n':{LCDDrawMonoBitmapQuick(Font_Word_14, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'O':{LCDDrawMonoBitmapQuick(Font_Word_15, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'o':{LCDDrawMonoBitmapQuick(Font_Word_15, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'P':{LCDDrawMonoBitmapQuick(Font_Word_16, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'p':{LCDDrawMonoBitmapQuick(Font_Word_16, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'Q':{LCDDrawMonoBitmapQuick(Font_Word_17, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'q':{LCDDrawMonoBitmapQuick(Font_Word_17, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'R':{LCDDrawMonoBitmapQuick(Font_Word_18, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'r':{LCDDrawMonoBitmapQuick(Font_Word_18, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'S':{LCDDrawMonoBitmapQuick(Font_Word_19, X, Y, 3, 8, HighColor, LowColor); break;}
            case 's':{LCDDrawMonoBitmapQuick(Font_Word_19, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'T':{LCDDrawMonoBitmapQuick(Font_Word_20, X, Y, 3, 8, HighColor, LowColor); break;}
            case 't':{LCDDrawMonoBitmapQuick(Font_Word_20, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'U':{LCDDrawMonoBitmapQuick(Font_Word_21, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'u':{LCDDrawMonoBitmapQuick(Font_Word_21, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'V':{LCDDrawMonoBitmapQuick(Font_Word_22, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'v':{LCDDrawMonoBitmapQuick(Font_Word_22, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'W':{LCDDrawMonoBitmapQuick(Font_Word_23, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'w':{LCDDrawMonoBitmapQuick(Font_Word_23, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'X':{LCDDrawMonoBitmapQuick(Font_Word_24, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'x':{LCDDrawMonoBitmapQuick(Font_Word_24, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'Y':{LCDDrawMonoBitmapQuick(Font_Word_25, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'y':{LCDDrawMonoBitmapQuick(Font_Word_25, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'Z':{LCDDrawMonoBitmapQuick(Font_Word_26, X, Y, 3, 8, HighColor, LowColor); break;}
            case 'z':{LCDDrawMonoBitmapQuick(Font_Word_26, X, Y, 3, 8, HighColor, LowColor); break;}
            case '?':{LCDDrawMonoBitmapQuick(Font_Word_27, X, Y, 3, 8, HighColor, LowColor); break;}
            case '.':{LCDDrawMonoBitmapQuick(Font_Word_28, X, Y, 3, 8, HighColor, LowColor); break;}
            case ':':{LCDDrawMonoBitmapQuick(Font_Word_29, X, Y, 3, 8, HighColor, LowColor); break;}
            case '!':{LCDDrawMonoBitmapQuick(Font_Word_30, X, Y, 3, 8, HighColor, LowColor); break;}
            case '-':{LCDDrawMonoBitmapQuick(Font_Word_31, X, Y, 3, 8, HighColor, LowColor); break;}
            case '/':{LCDDrawMonoBitmapQuick(Font_Word_32, X, Y, 3, 8, HighColor, LowColor); break;}
            case '1':{LCDDrawMonoBitmapQuick(Font_Word_33, X, Y, 3, 8, HighColor, LowColor); break;}
            case '2':{LCDDrawMonoBitmapQuick(Font_Word_34, X, Y, 3, 8, HighColor, LowColor); break;}
            case '3':{LCDDrawMonoBitmapQuick(Font_Word_35, X, Y, 3, 8, HighColor, LowColor); break;}
            case '4':{LCDDrawMonoBitmapQuick(Font_Word_36, X, Y, 3, 8, HighColor, LowColor); break;}
            case '5':{LCDDrawMonoBitmapQuick(Font_Word_37, X, Y, 3, 8, HighColor, LowColor); break;}
            case '6':{LCDDrawMonoBitmapQuick(Font_Word_38, X, Y, 3, 8, HighColor, LowColor); break;}
            case '7':{LCDDrawMonoBitmapQuick(Font_Word_39, X, Y, 3, 8, HighColor, LowColor); break;}
            case '8':{LCDDrawMonoBitmapQuick(Font_Word_40, X, Y, 3, 8, HighColor, LowColor); break;}
            case '9':{LCDDrawMonoBitmapQuick(Font_Word_41, X, Y, 3, 8, HighColor, LowColor); break;}
            case '0':{LCDDrawMonoBitmapQuick(Font_Word_42, X, Y, 3, 8, HighColor, LowColor); break;}
            default:{break;}
        }
        X += 4;
        if(Words[Bit] == '\n'){
            X = XStart;
            Y += 10;
        }
    }
}

void LCDDrawNum(uint16_t XStart, uint16_t YStart, uint32_t Num, uint8_t Len, uint16_t HighColor, uint16_t LowColor){
    if(Len > 10)return;
    uint8_t NumChar[10];
    for(uint8_t Bit = Len; Bit > 0; Bit --){
        switch((uint8_t)(Num % 10)){
            case 0:{NumChar[Bit - 1] = '0'; break;}
            case 1:{NumChar[Bit - 1] = '1'; break;}
            case 2:{NumChar[Bit - 1] = '2'; break;}
            case 3:{NumChar[Bit - 1] = '3'; break;}
            case 4:{NumChar[Bit - 1] = '4'; break;}
            case 5:{NumChar[Bit - 1] = '5'; break;}
            case 6:{NumChar[Bit - 1] = '6'; break;}
            case 7:{NumChar[Bit - 1] = '7'; break;}
            case 8:{NumChar[Bit - 1] = '8'; break;}
            case 9:{NumChar[Bit - 1] = '9'; break;}
            default:{NumChar[Bit - 1] = '-'; break;}
        }
        Num = Num / 10;
    }
    LCDDrawWords(XStart, YStart, NumChar, Len, HighColor, LowColor);
}