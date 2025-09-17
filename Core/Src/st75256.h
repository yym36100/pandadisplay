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
		rs(0);
		HAL_SPI_Transmit(&hspi6, &c, 1, HAL_MAX_DELAY);
		cs(1);
	}

	void write_dat(uint8_t d) {
		cs(0);
		rs(1);
		HAL_SPI_Transmit(&hspi6, &d, 1, HAL_MAX_DELAY);
		cs(1);
	}

	void init(void) {
		rst(0);
		delay(50);
		rst(1);
		delay(50);
		// after reset we are in sleep ext 0, disp 0ff, osc off, disp mono, otp auto read enabled

		write_cmd(0x30);
		write_cmd(0x94); // sleep out

#if 0
		write_cmd(0x31);
		write_cmd(0xd7);
		write_dat(0x9f); // auto read disable


//#if 0

		write_cmd(0x32); // analog set, booster freq and bias ratio
		write_dat(0x00);
		write_dat(0x01);
		write_dat(0x00);

		write_cmd(0x20); /* gray levels */
		write_dat(0x01);
		write_dat(0x03);
		write_dat(0x05);
		write_dat(0x07);
		write_dat(0x09);
		write_dat(0x0b);
		write_dat(0x0d);
		write_dat(0x10);
		write_dat(0x11);
		write_dat(0x13);
		write_dat(0x15);
		write_dat(0x17);
		write_dat(0x19);
		write_dat(0x1b);
		write_dat(0x1d);
		write_dat(0x1f);
#endif

		write_cmd(0x30); /* select 00 commands */

		write_cmd(0x75); // rows
		write_dat(0x00);
		write_dat(0x28);

		write_cmd(0x15); // cols
		write_dat(0x00);
		write_dat(0xff);

		write_cmd(0xbc); // data scan dir
		write_dat(0x00);

		write_cmd(0xa6); // normal display

		write_cmd(0x0c); /* data format LSB top */

		write_cmd(0xca); /* display control, 3 args follow  */
		write_dat(0x00); /* 0x00: no clock division, 0x04: devide clock */
		write_dat(159); /* 1/160 duty value from the DS example code */
		write_dat(0x20); /* nline off */

		write_cmd(0xf0); // disp mode = mono
		write_dat(0x10);

		write_cmd(0x81); // ev control set vop
		write_dat(0x18);
		write_dat(0x05);

		write_cmd(0x20); // power control
		write_dat(0x0b);

		delay(1);
		write_cmd(0xaf); // disp on

		//write_cmd(0xa7); // inverse

	}

	void clear(uint8_t v) {
		write_cmd(0x75); // rows
		write_dat(0x00);
		write_dat(0x28);

		write_cmd(0x15); // cols
		write_dat(0x00);
		write_dat(0xff);

		write_cmd(0x5c); // write data

		for(int i=0;i<256*160/8;i++){
			write_dat(v);
		}

	}
	void load_img(uint8_t *p) {
			write_cmd(0x75); // rows
			write_dat(0x00);
			write_dat(0x28);

			write_cmd(0x15); // cols
			write_dat(0x00);
			write_dat(0xff);

			write_cmd(0x5c); // write data

			for(int i=0;i<256*160/8;i++){
				write_dat(*p++);
			}

		}
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

void lcd_init(void);
void lcd_active250(void);

#ifdef __cplusplus
}
#endif

