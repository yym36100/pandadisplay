#include "st75256.h"

st75256 myst75256;

uint8_t framebuff[5120];

void lcd_init(void){
	myst75256.init();
}

void lcd_active250(void){
	static int a=0;
	static uint8_t b=0;
	if(a==0){
		myst75256.write_cmd(0xa7); // inverse
		a=1;
	 }else {
		 myst75256.write_cmd(0xa6); // inverse
		 a=0;
	 }
	//myst75256.clear(b++);
	//restore output.bin binary framebuff
	//restore c:\Users\yym\Downloads\zsuzsi_.bin binary framebuff
	myst75256.load_img(framebuff);

}
