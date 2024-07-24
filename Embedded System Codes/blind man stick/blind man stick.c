/*
 * blind_man_stick.c
 *
 * Created: 9/22/2017 12:24:58 AM
 *  Author: HP
 */ 
volatile unsigned char serial_buff[80];
unsigned char lon[15];
unsigned char lat[15];
unsigned char cant = 0;
#define F_CPU 2000000UL
#define triga	5
#define echo	6
#define buzer	7
#define gpsbaud	12
#define gsmbaud	12
#define bit_a		2
#define bit_b		3
//-----------------------------------------------------------------
#include <avr/io.h>
#include <util/delay.h>
#include <MyAVR/lcd4bit.h>
#include <MyAVR/serial.h>
#include <MyAVR/dec2ascii.h>
#include <MyAVR/sim800L.h>
#include <MyAVR/ADC.h>
#include <MyAVR/HCSR04.h>
//------------------------------------------------------------------
ISR(USART_RXC_vect)
{
	serial_buff[cant] = UDR;
	cant++;
	if (cant == 80)
	{
		cant = 0;
	}
}

int main(void)
{
	void switch2gps(void)
	{
		PORTD &=~ (1<<bit_b);
		PORTD &=~ (1<<bit_a);
		serial_init_no_inter(gpsbaud);
		_delay_ms(100);
	}
	void switch2gsm(void)
	{
		PORTD |= (1<<bit_a);
		PORTD &=~(1<<bit_b);
		serial_init_inter(gsmbaud);
		_delay_ms(100);
	}
	//88888888888888888888888 GPS FUNCTION 888888888888888888888888888
	unsigned char gps_read(void)
	{
		switch2gps();
		unsigned char bola;
gps1:	do
		{
			bola = serial_rx();
		} while (bola != '$');
		serial_buff[0] = serial_rx();
		serial_buff[1] = serial_rx();
		serial_buff[2] = serial_rx();
		serial_buff[3] = serial_rx();
		serial_buff[4] = serial_rx();
		if (serial_buff[2] == 'G' && serial_buff[3] == 'L' && serial_buff[4] == 'L')
		{
			cant = 0;
			do
			{
				serial_buff[cant] = serial_rx();
				cant++;
			} while (serial_buff[cant-1] != 0x0d);
			serial_buff[cant] = 0x0d;
			if (serial_buff[0] == ',' && serial_buff[1] == ',' && serial_buff[2] == ',')
			{
				bola = 1;
			}
			else
			{
				cant = 1;
				for (unsigned char a=0; a<12; a++)
				{
					lat[a] = serial_buff[cant];
					cant++;
				}
				cant = 14;
				for (unsigned char a=0; a<13; a++)
				{
					lon[a] = serial_buff[cant];
					cant++;
				}
				bola = 2;
			}
		}
		else
		{
			goto gps1;
		}
		
		return bola;
	}
	void sendGPS (char *num)
	{
		switch2gsm();
		serial_tx_string("AT+CMGS=");
		serial_tx(0x22);
		serial_tx_string(num);
		serial_tx(0x22);
		serial_tx(0x0D);
		_delay_ms(500);
		serial_tx_string("Attention...smoke detected at Lat: ");
		for (unsigned char a=0; a<12; a++)
		{
			serial_tx(lat[a]);
		}
		serial_tx_string(" and Long: ");
		for (unsigned char a=0; a<13; a++)
		{
			serial_tx(lon[a]);
		}
		serial_tx(0x1A);
		_delay_ms(3000);
	}
	void beep(unsigned char a)
	{
		for (unsigned char c=0; c<a; c++)
		{
			PORTD |= (1<<buzer);
			_delay_ms(60);
			PORTD &=~ (1<<buzer);
			_delay_ms(100);
		}		
	}
	//----------------------------------------------------------
	
	DDRD |= (1<<bit_a);   
	DDRD |= (1<<bit_b);  
	DDRD |= (1<<buzer); 
	DDRD &=~ (1<<echo);
	DDRD |= (1<<triga);
	_delay_ms(2000);
	beep(3);
	switch2gsm();
	sim800init();
	findNetwork();
	beep(2);
	_delay_ms(2000);
		 
    while(1)
    {
        do 
        {
			int obj = HCSR04_read();
			if (obj < 50)
			{
				beep(3);				
			}			
        } while (adc_read(0x00) < 245);
		
		unsigned char aaa = gps_read();
		if (aaa == 2)
		{
			switch2gsm();
			sendGPS("+2349078166101");
			beep(3);
		}
		else
		{
			switch2gsm();
			send_sms("+2349078166101", "Attention... smoke detected but GPS has no lock on satellite");
			beep(5);
		}
		_delay_ms(2000);	
		 
    }
}