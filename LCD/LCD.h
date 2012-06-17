/**
 * LCD.h
 *
 * Created: 31.05.2012 23:24:04
 *  Author: Hirschfeld
 *	Description: LCD Subroutines for ST7066 and compatible LCD-Driver IC's 
 */ 


#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU

#warning "F_CPU not defined for LCD.h"

#endif


#define COLUMN	4
#define ROW		20

/*
 *	User defined Symbols 
 */

//battery Full
#define BATF1	0b00001110
#define BATF2	0b00011111
#define BATF3	0b00011111
#define BATF4	0b00011111
#define BATF5	0b00011111
#define BATF6	0b00011111
#define BATF7	0b00011111
#define BATF8	0b00011111

//battery 50%
#define BATH1	0b00001110
#define BATH2	0b00011111
#define BATH3	0b00010001
#define BATH4	0b00011111
#define BATH5	0b00011111
#define BATH6	0b00011111
#define BATH7	0b00011111
#define BATH8	0b00011111

//battery Low
#define BATL1	0b00001110
#define BATL2	0b00011111
#define BATL3	0b00010001
#define BATL4	0b00010001
#define BATL5	0b00010001
#define BATL6	0b00011111
#define BATL7	0b00011111
#define BATL8	0b00011111

//battery Empty
#define BATC1	0b00001110
#define BATC2	0b00011111
#define BATC3	0b00010001
#define BATC4	0b00010001
#define BATC5	0b00010001
#define BATC6	0b00010001
#define BATC7	0b00010001
#define BATC8	0b00011111


/*
 *	LCD Port Definitions
 */
#define LCD_DATA PORTC	//Port for Display Data Output
#define LCD_DIN	 PINC	//Port for Display Data Input
#define DATADDR	 DDRC	//DDR for Display Data Port
#define LCD_CTRL PORTD
#define CTRLDDR  DDRD	//DDR for Display Control Bits
#define RS		 PD3	//Select Instruction/Data
#define RW		 PD4	//Select Read/Write
#define E		 PD6	//Enable


/*
 *	Instuction Definitions
 */
#define CLR	0x01	//Clear Display Data and Reset Cursor
#define RET 0x02	//Return Cursor and reset display if shifted

#define ENTMOD 0x04	//Entry Mode Set Use Bit shift I_D and S
#define I_D		1	//increment(1)/decrement(0) DDRAM address
#define S		0	//Shift Display(1) according to I_D (1:left;0:right)

#define ON	   0x08	//Turn Display Cursor and Cursor Blink on/off
#define D		2	//Display On(1)/Off(0)
#define C		1	//Cursor On(1)/Off(0)
#define B		0	//Cursor Blink On(1)/Off(0)

#define SHIFT  0x10 //Cursor or Display Shift
#define S_C		3	//Shift Display(1)/Cursor(0)
#define R_L		2	//Shift right(1)/left(0)

//Function Set Use 1/0 behind defines 
#define DL		1	//Data length 8-bit(1)/4-bit(0) 
#define N		1	//Display line number 2-line(1)/1-line(0)
#define F		0	//Display font type 5x10 dots(1)/5x8 dots(0)
#define F_SET   (32+(DL*16)+(N*8)+(F*4))

#define SET_CGR 64	//Set CGRAM Address
#define SET_DDR	128	//SET DDRAM Address


/*
 * Public Subroutines
 */
extern void lcd_init(void);
extern void lcd_data(unsigned char data);
extern void lcd_set_cursor(unsigned char column,unsigned char row);
extern void lcd_clr(void);
extern void lcd_return(void);
extern void lcd_cursor_on(void);
extern void lcd_cursor_bl(void);
extern void lcd_off(void);
extern void lcd_on(void);
extern void lcd_bs(void);
extern unsigned char lcd_read_ac(void);
extern void lcd_set_ac(unsigned char ac);

extern void lcd_shift_cr(unsigned char i);
extern void lcd_shift_cl(unsigned char i);

#endif /* LCD_H_ */