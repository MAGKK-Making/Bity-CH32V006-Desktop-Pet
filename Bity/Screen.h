#ifndef __Screen
#define __Screen

void LCDInit(void);
void LCDSetLocation(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd);
void LCDClear(uint16_t BackgroundColor);
void LCDClearArea(uint16_t XStart, uint16_t YStart, uint16_t XEnd, uint16_t YEnd, uint16_t BackgroundColor);
void LCDDrawPoint(uint16_t X, uint16_t Y, uint16_t Color);
void LCDDrawBitmap(const uint16_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H);
void LCDDrawMonoBitmap(const uint8_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H, uint16_t HighColor, uint16_t LowColor, uint8_t UseAlpha);
void LCDDrawMonoBitmapQuick(const uint8_t *Bitmap, uint16_t XStart, uint16_t YStart, uint16_t W, uint16_t H, uint16_t HighColor, uint16_t LowColor);
void LCDDrawTile(const uint16_t *Tile, const uint8_t *TileOffset, uint8_t TileSize, uint8_t MapWidth, uint8_t MapHeight, uint8_t XOffset, uint8_t YOffset);
void LCDDrawBar(uint16_t XStart, uint16_t YStart, uint16_t Len, float FullNum, float ShowNum, uint16_t BlankColor, uint16_t OutlineColor, uint16_t ShowbarColor);
void LCDDrawWords(uint16_t XStart, uint16_t YStart, uint8_t *Words, uint16_t WordsLen, uint16_t HighColor, uint16_t LowColor);
void LCDDrawNum(uint16_t XStart, uint16_t YStart, uint32_t Num, uint8_t Len, uint16_t HighColor, uint16_t LowColor);

#endif