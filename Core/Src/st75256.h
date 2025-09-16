#pragma once

#include <stdint.h>
#include "main.h"

#ifdef __cplusplus

extern SPI_HandleTypeDef hspi6;

// 4 bit spi mode
class st75256 {
public:
	//@formatter:off
	void rst(int v) { HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, (GPIO_PinState)v); }
	void cs(int v)  { HAL_GPIO_WritePin(LCD_CS_GPIO_Port,    LCD_CS_Pin,    (GPIO_PinState)v); }
	void rs(int v)  { HAL_GPIO_WritePin(LCD_RS_GPIO_Port,    LCD_RS_Pin,    (GPIO_PinState)v); }

	void delay(int n) { HAL_Delay(n); }

			//@formatter:on

	void write_cmd(uint8_t c) {
		cs(0);
		HAL_SPI_Transmit(&hspi6, &c, 1, HAL_MAX_DELAY);
		cs(1);
	}

	void write_data(uint8_t *d, uint16_t len = 1) {
		cs(0);
		HAL_SPI_Transmit(&hspi6, d, len, HAL_MAX_DELAY);
		cs(1);
	}

	void init(void) {
		rst(0);
		delay(50);
		rst(1);
	}
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void lcd_init(void);

#ifdef __cplusplus
}
#endif

