#include "st75256.h"

st75256 myst75256;

void lcd_init(void){
	uint8_t data;
	HAL_SPI_Transmit(&hspi6, &data, 1, 1);
}
