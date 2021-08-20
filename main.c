#include <at89c5131.h>
#include "lcd.h"
#include <string.h>
#include <stdio.h>
#include "serial.c"
sbit P = P1^7;

sbit counter_A = P1^0;
sbit counter_B = P1^1;
sbit counter_C = P1^2;
sbit counter_D = P1^3;


int toggle_check(bit a1,bit  b1,bit c1, bit d1, bit a2, bit b2, bit c2, bit d2)
{
	if (a1 ^ a2== 1)
	{return 1;}
	
	else if (b1 ^ b2 ==1)
	{return 2;}
	
	else if (c1 ^ c2 ==1)
	{return 3;}
	
	else if (d1 ^ d2==1)
	{return 4;}
	
	else {return 0;}
}

void main(void)
{ unsigned int token_number = 0;
	unsigned char token[2];
	unsigned char ch;
	unsigned int low = 0;
	unsigned int high = 0;
	bit a,b,c,d;
	unsigned char a_state[2];
	unsigned char b_state[2];
	unsigned char c_state[2]; 
	unsigned char d_state[2];
	bit flagg=0;
	int toggle;
	a_state[0] = 32;
	a_state[1] = 32;
	b_state[0] = 32;
	b_state[1] = 32;
	c_state[0] = 32;
	c_state[1] = 32;
	d_state[0] = 32;
	d_state[1] = 32;
	//sprintf(a_state,"%s","XX");
	//sprintf(b_state,"%s","XX");
	//sprintf(c_state,"%s","  ");
	//sprintf(d_state,"%s","  ");
	lcd_init();
	uart_init();
	
	lcd_write_string("A:   B:  ");
	lcd_cmd(0xC0);
	lcd_write_string("C:   D:  "); 
  ch = 'p';
	ch = receive_char();
	if (ch == 't')
	{
		token_number = token_number + 1;
		lcd_cmd(0x01);	// LCD clear
		lcd_cmd(0x80);
		token[0] = token_number/10 + 48;
		token[1] = token_number%10 + 48;
		lcd_write_string("Token: "); // printing the "token: XX" on lcd
		lcd_write_char(token[0]);
		lcd_write_char(token[1]);
		msdelay(2000);
		high = high + 1;
	}
	lcd_cmd(0x01);	// LCD clear
	lcd_cmd(0x80);
	lcd_write_string("A:   B:  ");
	lcd_cmd(0x8B);
	lcd_write_string("     ");
	lcd_cmd(0xC0);
	lcd_write_string("C:   D:  ");
	
	
	//token_number = 90;
	//high = 90;
	//low = 85;
	
	
	
	
	
	ch = 'p';
	while(1)
	{
		a = counter_A;
		b = counter_B;
		c = counter_C;
		d = counter_D;
		msdelay(1000);
		ch = SBUF;
		if (ch=='t' && rx_complete == 1)
		{
			if (token_number==99) {flagg=1;}
			token_number = increment(token_number);
			lcd_cmd(0x01);	// LCD clear
			lcd_cmd(0x80);
			token[0] = token_number/10 + 48;
		  token[1] = token_number%10 + 48;
			lcd_write_string("Token: "); // printing the "token: XX" on lcd
			lcd_write_char(token[0]);
			lcd_write_char(token[1]);
			msdelay(2000);
			high = increment(high);
			rx_complete = 0;
			lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
				lcd_write_string("A:");
				lcd_write_char(a_state[0]);
			  lcd_write_char(a_state[1]);
			  lcd_write_char(32);
			  lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
			  lcd_write_char(b_state[1]);
				lcd_write_char(32);
				lcd_write_string("      ");
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_char(c_state[0]);
				lcd_write_char(c_state[1]);
				lcd_write_char(32);
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				lcd_write_char(32);
				lcd_write_string("      ");
		}
		
		toggle = toggle_check(a,b,c,d,counter_A,counter_B,counter_C,counter_D);
		if (toggle==0)
		{
		continue;}
		
		else if (toggle==1)
		{
			if (high > low || flagg==1)
			{ low = increment(low);
				if (high>=low)
				{flagg=0;}
				//sprintf(a_state, "%d",low);
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				*/
				lcd_cmd(0x80);
				lcd_write_string("A:");
				a_state[0] = low/10 + 48;
				a_state[1] = low%10 + 48;
				lcd_write_char(a_state[0]);
				lcd_write_char(a_state[1]);
				lcd_write_char(32);
				/*
				lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
			
			else
			{
				/*
			  lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				*/
				lcd_cmd(0x80);
			  lcd_write_string("A:   ");
				a_state[0] = 32;
				a_state[1] = 32;
				/*
				lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
		}
		
		
		
		else if (toggle==2)
		{
			if (high > low || flagg==1)
			{
				low = increment(low);
				if (high>=low)
				{flagg=0;}
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
				*/
				b_state[0] = low/10 + 48;
				b_state[1] = low%10 + 48;
				/*
				lcd_write_string("A:");
				lcd_write_string(a_state);
				*/
				lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_write_char(32);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				/*
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
			
			else
			{ 
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
			  lcd_write_string("A:");
				lcd_write_string(a_state);
				*/
				lcd_cmd(0x85);
				lcd_write_string("B:   ");
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				b_state[0] = 32;
				b_state[1] = 32;
				/*
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
		}
		
		
		else if (toggle==3)
		{
			if (high > low || flagg==1)
			{
				low = increment(low);
				if (high>=low)
				{flagg=0;}
				c_state[0] = low/10 + 48;
				c_state[1] = low%10 + 48;
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
				lcd_write_string("A:");
				lcd_write_string(a_state);
				lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				*/
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_char(c_state[0]);
				lcd_write_char(c_state[1]);
				lcd_write_char(32);
				/*
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
			
			else
			{
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
			  lcd_write_string("A:");
				lcd_write_string(a_state);
				lcd_cmd(0x85);
				lcd_write_string("B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				*/
				
				lcd_cmd(0xC0);
				lcd_write_string("C:   ");
				c_state[0] = 32;
				c_state[1] = 32;
				/*
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
				*/
			}
		}
		
		
		
		
		else if (toggle==4)
		{
			if (high > low || flagg==1)
			{
				low = increment(low);
				if (high>=low)
				{flagg=0;}
				d_state[0] = low/10 + 48;
				d_state[1] = low%10 + 48;
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
				lcd_write_string("A:");
				lcd_write_string(a_state);
				lcd_cmd(0x85);
				lcd_write_string(" B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				*/
				lcd_cmd(0xC5);
				lcd_write_string("D:");
				lcd_write_char(d_state[0]);
				lcd_write_char(d_state[1]);
			}
			
			else
			{
				/*
				lcd_cmd(0x80);
				lcd_write_string("                ");
				lcd_cmd(0xC0);
				lcd_write_string("                ");
				lcd_cmd(0x80);
			  lcd_write_string("A:");
				lcd_write_string(a_state);
				lcd_cmd(0x85);
				lcd_write_string(" B:");
				lcd_write_char(b_state[0]);
				lcd_write_char(b_state[1]);
				lcd_cmd(0x8B);
				lcd_write_string("     ");
				
				lcd_cmd(0xC0);
				lcd_write_string("C:");
				lcd_write_string(c_state);
				*/
				lcd_cmd(0xC5);
				lcd_write_string("D:   ");
				d_state[0] = 32;
				d_state[1] = 32;
			}
		}
		ch = 'p';
	}
}