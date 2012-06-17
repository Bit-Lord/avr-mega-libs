/*
 * LCD.c
 *
 * Created: 31.05.2012 23:22:22
 *  Author: Hirschfeld
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

unsigned char cursor=0;

void busy(){
	DATADDR = 0x00;
	LCD_CTRL &= ~(1<<RS);
	LCD_CTRL |= (1<<RW);
	LCD_DATA = 0xFF;
	LCD_CTRL |= (1<<E);
	__asm__("NOP\n NOP"); 
	while(LCD_DIN & 0x80);
	LCD_CTRL &= ~(1<<E);
	LCD_DATA = 0x00;
	DATADDR = 0xFF;
}
void write_cmd(unsigned char cmd){
	LCD_CTRL &= ~(1<<RS);
	LCD_CTRL &= ~(1<<RW);
	LCD_DATA = cmd;
	LCD_CTRL |= (1<<E);
	_delay_us(0.2);
	LCD_CTRL &= ~(1<<E);
	if(cursor != 128)
		busy();

}

void cursor_set(){
	if(N){
		cursor++;
		switch(cursor){
			case 20:
			//lcd_shift_cr(21);
			write_cmd(SET_DDR + 0x40);
			return;
			case 40:
			//lcd_shift_cl(41);
			write_cmd(SET_DDR + 20);
			return;			
			case 60:
			//lcd_shift_cr(21);
			write_cmd(SET_DDR + 0x54);
			return;
			case 80:
			cursor = 0;
			default:
			return;
		}
	}
	
}
void write_data(unsigned char data)
{
	LCD_CTRL |= (1<<RS);
	LCD_CTRL &= ~(1<<RW);
	LCD_DATA = data;
	LCD_CTRL |= (1<<E);
	_delay_us(0.2);
	LCD_CTRL &= ~(1<<E);
	LCD_DATA = 0x00;
	busy();
	cursor_set();
	
}
void set_user(){
	unsigned char i=0;
	
	write_cmd(SET_CGR + i++);
	write_data(BATC1);
	write_cmd(SET_CGR + i++);
	write_data(BATC2);
	write_cmd(SET_CGR + i++);
	write_data(BATC3);
	write_cmd(SET_CGR + i++);
	write_data(BATC4);
	write_cmd(SET_CGR + i++);
	write_data(BATC5);
	write_cmd(SET_CGR + i++);
	write_data(BATC6);
	write_cmd(SET_CGR + i++);
	write_data(BATC7);
	write_cmd(SET_CGR + i++);
	write_data(BATC8);
	
	write_cmd(SET_CGR + i++);
	write_data(BATL1);
	write_cmd(SET_CGR + i++);
	write_data(BATL2);
	write_cmd(SET_CGR + i++);
	write_data(BATL3);
	write_cmd(SET_CGR + i++);
	write_data(BATL4);
	write_cmd(SET_CGR + i++);
	write_data(BATL5);
	write_cmd(SET_CGR + i++);
	write_data(BATL6);
	write_cmd(SET_CGR + i++);
	write_data(BATL7);
	write_cmd(SET_CGR + i++);
	write_data(BATL8);
	
	write_cmd(SET_CGR + i++);
	write_data(BATH1);
	write_cmd(SET_CGR + i++);
	write_data(BATH2);
	write_cmd(SET_CGR + i++);
	write_data(BATH3);
	write_cmd(SET_CGR + i++);
	write_data(BATH4);
	write_cmd(SET_CGR + i++);
	write_data(BATH5);
	write_cmd(SET_CGR + i++);
	write_data(BATH6);
	write_cmd(SET_CGR + i++);
	write_data(BATH7);
	write_cmd(SET_CGR + i++);
	write_data(BATH8);
	
	write_cmd(SET_CGR + i++);
	write_data(BATF1);
	write_cmd(SET_CGR + i++);
	write_data(BATF2);
	write_cmd(SET_CGR + i++);
	write_data(BATF3);
	write_cmd(SET_CGR + i++);
	write_data(BATF4);
	write_cmd(SET_CGR + i++);
	write_data(BATF5);
	write_cmd(SET_CGR + i++);
	write_data(BATF6);
	write_cmd(SET_CGR + i++);
	write_data(BATF7);
	write_cmd(SET_CGR + i++);
	write_data(BATF8);
	
	cursor = 0;
}

void lcd_init(void){
	LCD_DATA = 0x00;
	DATADDR  = 0xFF;
	CTRLDDR |= ((1<<E)|(1<<RW)|(1<<RS));
	cursor = 128;
	_delay_ms(15);
	write_cmd(F_SET);
	_delay_ms(4.1);
	write_cmd(F_SET);
	_delay_ms(0.1);
	write_cmd(F_SET);
	_delay_us(37);
	write_cmd(F_SET);
	_delay_us(37);
	write_cmd(ON);
	_delay_us(37);
	write_cmd(CLR);
	_delay_ms(1.52);
	write_cmd(ENTMOD |(1<<I_D)|(0<<S));
	cursor = 0;
	write_cmd(ON | (1<<D)|(1<<B));
	set_user();
}
void lcd_data(unsigned char data){
	write_data(data);
}
void lcd_set_cursor(unsigned char column,unsigned char row){
	if(column<COLUMN && row<ROW){
		if(N){
			//write_cmd(RET);
			switch(column){
				case 0:
				cursor = row;
				//lcd_shift_cr(row);
				write_cmd(SET_DDR + row);
				break;
				case 1:
				cursor = 20 + row;
				//lcd_shift_cr(row + 40);
				write_cmd(SET_DDR + 64 + row);
				break;
				case 2:
				cursor = 40 + row;
				//lcd_shift_cr(row + 20);
				write_cmd(SET_DDR + 20 + row);
				break;
				case 3:
				cursor = 60 + row;
				//lcd_shift_cr(60 + row);
				write_cmd(SET_DDR + 84 + row);
			}
		}		
	}
}
void lcd_clr(void){
	write_cmd(CLR);
	cursor = 0;
}
void lcd_return(void){
	write_cmd(RET);
	cursor = 0;
}
void lcd_cursor_on(void){
	write_cmd(ON |(1<<D)|(1<<C));
}
void lcd_cursor_bl(void){
	write_cmd(ON | (1<<D)|(1<<B));
}
void lcd_off(void){
	write_cmd(ON);
}
void lcd_on(void){
	write_cmd(ON | (1<<D));
}
void lcd_bs(void){
	lcd_shift_cl(1);
}
unsigned char lcd_read_ac(void){
	unsigned char temp;
	LCD_CTRL &= ~(1<<RS);
	LCD_CTRL |= (1<<RW);
	DATADDR = 0x00;
	LCD_DATA = 0xFF;
	LCD_CTRL |= (1<<E);
	__asm__("NOP");
	temp = LCD_DIN;
	LCD_CTRL &= ~(1<<E);
	LCD_DATA = 0x00;
	DATADDR = 0xFF;
	return temp;
}
void lcd_set_ac(unsigned char ac){
	if(ac < 20){
		cursor = ac;
	}		
	if((ac >= 20 ) && (ac <= 0x27)){
		cursor = 40 + (ac - 20);
	}
	if((ac>= 0x40)&&(ac < 0x54)){
		cursor = 20 + (ac - 0x40);
	}
	if((ac >= 0x54 ) && (ac <= 0x67)){
		cursor = 60 + (ac - 0x54);
	}
	write_cmd(SET_DDR + ac);
}
void lcd_shift_cl(unsigned char i){
	unsigned char x=0;
	for(x=0;x<i;x++){
		write_cmd(SHIFT);
	}
}
void lcd_shift_cr(unsigned char i){
	unsigned char x;
	for(x=0;x<i;x++){
		write_cmd(SHIFT | (1<<R_L));
	}
}