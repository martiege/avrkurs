#define F_CPU 3333333ul
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdbool.h>
#include "oled.h"
#include "fonts.h"
#include "spi.h"
//#include "display.h"


static uint8_t oled_current_line_num;

#define OLED_MODE_bm (1 << 3)
#define OLED_MODE_PORT PORTC
#define OLED_RESET_bm (1 << 7)
#define OLED_RESET_PORT PORTC

#define DATA_MODE 1
#define COMMAND_MODE 0

//------------------------------------------------------------

uint8_t oled_get_current_line(){
	return oled_current_line_num;
}

void oled_init()  // Documentation on oled screen on: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
{	
	OLED_RESET_PORT.DIRSET = OLED_RESET_bm;
	OLED_MODE_PORT.DIRSET = OLED_MODE_bm;
	oled_set_mode(1);
	oled_reset();
	
	oled_write_c(0xAE); // display off

	// p32
	oled_write_c(0xD5); // clock
	oled_write_c(0xF0); // upper nibble is rate, lower nibble is divisor

	// p31
	oled_write_c(0xA8); // mux ratio p31
	oled_write_c(0x20); // rtfm

	// p31
	oled_write_c(0xD3); // display offset
	oled_write_c(0x00); // rtfm

	// p3 (appendix)
	oled_write_c(0x8D); // charge pump
	oled_write_c(0x14); // enable

	// p30, p34
	oled_write_c(0x20); // memory addr mode
	oled_write_c(0x00); // horizontal

	// p31
	oled_write_c(0xA1); // segment remap
	oled_write_c(0xA5); // display on

	// p31
	oled_write_c(0xC8); // com scan direction

	// p31
	oled_write_c(0x7F); // display start line

	// p31
	oled_write_c(0x22); // set page address
	oled_write_c(0x00);
	oled_write_c(0x03);

	// p31, p40
	oled_write_c(0xDA); // com hardware cfg
	oled_write_c(0x02); // com cfg

	// p28
	oled_write_c(0x81); // contrast aka current
	oled_write_c(0xFF); // 128 is midpoint

	// p32
	oled_write_c(0xD9); // precharge
	oled_write_c(0x11); // rtfm

	// p32
	oled_write_c(0xDB); // vcomh deselect level
	oled_write_c(0x20); // rtfm

	oled_write_c(0xA6); // non-inverted
	oled_write_c(0xA4); // display scan on
	oled_write_c(0xAF); // drivers on

	oled_clear_screen();
}

/* Hardware reset the screen */
void oled_reset()
{
	OLED_RESET_PORT.OUTCLR = OLED_RESET_bm;
	_delay_ms(10);
	OLED_RESET_PORT.OUTSET = OLED_RESET_bm;
	_delay_ms(10);
}

/* Set data/command mode */
void oled_set_mode(uint8_t mode)
{
	if (mode == DATA_MODE)
	{
		OLED_MODE_PORT.OUTSET=OLED_MODE_bm;
	}
	if (mode == COMMAND_MODE)
	{
		OLED_MODE_PORT.OUTCLR=OLED_MODE_bm;
	}
}

/* Write command */
void oled_write_c(uint8_t command){
	oled_set_mode(0);
	spi_transmit(command);
}

/* Write data*/
void oled_write_d(uint8_t data){
	oled_set_mode(1);
	spi_transmit(data);
}

/* Clear the screen */
void oled_clear_screen(){
	for(int line=0;line<4;line++){
		oled_clear_line(line);
	}
}
/* Clear one line */
void oled_clear_line(uint8_t line){ 		
	oled_write_c(0xb0 + line); 		// selects row/page
	for(int byte=0;byte<128;byte++){
			// Clear current column
		oled_set_mode(1);
		spi_transmit(0x00);
	}
}

/* Go to given row*/
void oled_goto_line(uint8_t line){
	oled_write_c(0xb0 + line);
	oled_current_line_num = line;
}

/* Go to given row and column*/
void oled_pos(uint8_t row, uint8_t col){
	oled_write_c(0xb0 + row);			// Go to row/page
	oled_current_line_num = row;
	oled_write_c(0x00 + (col & 0x0F));          	// Low column start address
	oled_write_c(0x10 + ((col >> 4) & 0x0F));	// High column start address
}

/* Write a character to the screen with font 4 to current position*/
int oled_putchar4(char character, FILE *stream){ 	// Use ASCII code minus 32, Font4
	if(character == '\n'){
		oled_pos(oled_current_line_num +1, 8);	// Next line with column margin of 8
		return 0;
	}
	for(uint8_t i = 0; i < 4; ++i){
		oled_write_d(pgm_read_word(&font4[character - 32][i]));
	}
	oled_write_d(0x00);
	return 0;
}

/* Write a character to the screen with font 5 to current position */
int oled_putchar5(char character, FILE *stream){ // Use ASCII code minus 32, Font5
    if(character == '\n'){
	    oled_pos(oled_current_line_num +1, 8);
		return 0;
    }
	for(uint8_t i = 0; i < 5; ++i){
        oled_write_d(pgm_read_word(&font5[character - 32][i]));
    }
	oled_write_d(0x00);
	return 0;
}

/* Write a character to the screen with font 8 to current position */
int oled_putchar8(char character, FILE *stream){ // Use ASCII code minus 32, Font8
    if(character == '\n'){
	    oled_pos(oled_current_line_num +1, 8);
		return 0;
    }
	for(uint8_t i = 0; i < 4; ++i){
        oled_write_d(pgm_read_word(&font8[character - 32][i]));
    }
	return 0;
}

/* Set brightness, 0-255 */
void oled_set_brightness(uint8_t lvl){
    oled_write_c(0x81); // Set brightness command
    oled_write_c(lvl); 	// Set brightness level
}
