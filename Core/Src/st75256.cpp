#include "st75256.h"

st75256 myst75256;

void lcd_init(void){
	myst75256.init();
}

void lcd_active250(void){
	static int a=0;
	if(a==0){
		myst75256.write_cmd(0xa7); // inverse
		a=1;
	 }else {
		 myst75256.write_cmd(0xa6); // inverse
		 a=0;
	 }
}
