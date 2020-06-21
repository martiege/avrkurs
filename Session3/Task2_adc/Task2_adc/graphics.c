#include <stdarg.h>
#include <stdio.h>
#include "oled.h"
#include "graphics.h"

/* Custom printf function. Text 4, 5 or 8*/
void graphics_printf(uint8_t size,const char *__fmt, ...){
	va_list args;
	va_start(args, __fmt);
	if(size==4){
		vfprintf(FONT4,__fmt,args);
	}
	else if(size==8){
		vfprintf(FONT8,__fmt,args);
	}
	else{
		vfprintf(FONT5,__fmt,args);
	}
	va_end(args);
}
/* Clear the screen */
void graphics_clear_screen(){
	oled_pos(0,0);
	oled_clear_screen();
}


/* Draw the outline of the loading bar */
void graphics_loading_bar_init()
{
	oled_pos(1,12);
	oled_write_d(0xf8);
	oled_pos(2,12);
	oled_write_d(0x1f);
	oled_pos(1,115);
	oled_write_d(0xf8);
	oled_pos(2,115);
	oled_write_d(0x1f);
	for(uint8_t i=0;i<101;i++)
	{
		oled_pos(1,13+i);
		oled_write_d(0x08);
		oled_pos(2,13+i);
		oled_write_d(0x10);
	}
}

/* Set length of loading bar. Between 0 and 1023 */
void graphics_loading_bar_set(uint16_t data)
{
	if(data>1023){  //Highest data value
		data=1023;
	}
	data=data/10; //convert  data to percentages
	for(int i=0; i<data;i++){
		oled_pos(1,13+i);
		oled_write_d(0xf8);
		oled_pos(2,13+i);
		oled_write_d(0x1f);
	}
	for(int i=data; i<102;i++){
		oled_pos(1,13+i);
		oled_write_d(0x08);
		oled_pos(2,13+i);
		oled_write_d(0x10);
	}
}


/* Print bitmap to screen */
void graphics_print_bitmap(const uint8_t* bm)
{
	
	for(uint8_t y = 0; y < 4; y++)
	{
		for(uint8_t x = 0; x < 16; x++)
		{
			uint8_t d[8] = {
				pgm_read_byte(&(bm[(8 * y + 0) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 1) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 2) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 3) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 4) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 5) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 6) * 16 + x])),
				pgm_read_byte(&(bm[(8 * y + 7) * 16 + x]))
			};

			for(uint8_t b = 0; b < 8; b++)
			{
				uint8_t db = 0;
				db |= (((d[0] >> b) & 0x1) << 0);
				db |= (((d[1] >> b) & 0x1) << 1);
				db |= (((d[2] >> b) & 0x1) << 2);
				db |= (((d[3] >> b) & 0x1) << 3);
				db |= (((d[4] >> b) & 0x1) << 4);
				db |= (((d[5] >> b) & 0x1) << 5);
				db |= (((d[6] >> b) & 0x1) << 6);
				db |= (((d[7] >> b) & 0x1) << 7);

				oled_write_d(db);
			}
		}
	}
}