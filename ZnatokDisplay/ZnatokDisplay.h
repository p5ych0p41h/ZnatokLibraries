#ifndef ZnatokDisplay_h
#define ZnatokDisplay_h

#define SEGMENT_COUNT		8
#define STR_ERROR_SYMBOL	0
#define STR_MA_SYMBOL		1
#define STR_KELVIN_SYMBOL	2
#define STR_OHM_SYMBOL		3
#define STR_VOLTAGE_SYMBOL	4
#define STR_LUX_SYMBOL		5
#define STR_DB_SYMBOL		6

#pragma once
#include "Arduino.h"
#include "libs/DigitalIO.h"

template <uint8_t pin>
class ZnatokDisplay{
  public:
    void attach()
	{
	  digitalPin.config(OUTPUT, LOW);
	  for (int i = 0; i < 64; i++)
	  {
		bitZero();
		delayMicroseconds(6);
	  }
	}
	
    void printSeconds(int num)
	{
	  int a, b, c, d;
	  d = num % 10;
	  num = num / 10;
	  c = num % 10;
	  num = num / 10;
	  b = num % 10;
	  num = num / 10;
	  a = num;
	  printNum(a);
	  printNum(b);
	  printNum(c);
	  printNum(d);
	}
	
    void printMinutesSeconds(long int ms)
	{
	  int ms_in_seconds = ms / 1000;
	  int clock_seconds = ms_in_seconds % 60;
	  int c = clock_seconds / 10;
	  int d = clock_seconds % 10;

	  int clock_minutes = ms_in_seconds / 60;
	  int a = clock_minutes / 10;
	  int b = clock_minutes % 10;

	  printNum(a);

	  if (ms % 1000 > 500)
	  {
		printNum(b);
	  }
	  else
	  {
		printNumW(b);
	  }
	  printNum(c);
	  printNum(d);
	}
	
    void printVoltage(int value)
	{
	  float voltage = (float)value * 5 / 1024;
	  int disp_voltage = (int)(100 * voltage) + 1;
	  int a, b, c, d;
	  d = disp_voltage % 10;
	  disp_voltage /= 10;
	  c = disp_voltage % 10;
	  b = disp_voltage / 10;
	  a = 10;
	  printNum(a);
	  printNum(a);
	  printNumW(b);
	  printNum(c);

	  printSymbolString(STR_VOLTAGE_SYMBOL);
	}
	
    void printDistance(int value)
	{
	  int a, b, c, d;

	  d = value % 10;
	  value /= 10;
	  c = value % 10;
	  b = value / 10;
	  a = 10;

	  printNum(a);
	  printNum(b);
	  printNum(c);
	  printNumW(d);
	}
	
    void printNumber(int num)
	{
	  int a, b, c, d;

	  d = num % 10;
	  num /= 10;
	  c = num % 10;
	  b = num / 10;
	  a = 10;

	  printNum(a);
	  printNum(b);
	  printNum(c);
	  printNum(d);
	}

  private:
    DigitalPin<pin> digitalPin;
    byte numberSegments[11] = {
      0b00111111, //0
      0b00000110, //1
      0b01011011, //2
      0b01001111, //3
      0b01100110, //4
      0b01101101, //5
      0b01111101, //6
      0b00000111, //7
      0b01111111, //8
      0b01101111, //9
      0b00000000  //off
    };
    void printSymbolString(int k)
	{
	  for (int j = 0; j < 4; j++)
	  {
		for (int i = 0; i < 8; i++)
		{
		  if (i == k)
		  {
			bitOne();
		  }
		  else
		  {
			bitZero();
		  }
		  delayMicroseconds(6);
		}
	  }
	}

    void printNum(int num)
	{

	  for (int i = 0; i < SEGMENT_COUNT; i++) {
		// определяем: должен ли он быть включён.
		boolean enableSegment = bitRead(numberSegments[num], i);
		if (enableSegment == 1)
		{
		  bitOne();
		  delayMicroseconds(6);
		}
		else
		{
		  bitZero();
		  delayMicroseconds(6);
		}
	  }
	  delayMicroseconds(10);
	}
	
    void printNumW(int num)
	{

	  for (int i = 0; i < SEGMENT_COUNT; i++) {
		// определяем: должен ли он быть включён.
		boolean enableSegment = bitRead(numberSegments[num], i);
		if (enableSegment == 1 || i == 7)
		{
		  bitOne();
		  delayMicroseconds(6);
		}
		else
		{
		  bitZero();
		  delayMicroseconds(6);
		}
	  }
	  delayMicroseconds(10);
	}
	
    void printZero()
	{
	  for (int i = 0; i < 6; i++)
	  {
		bitOne();
		delayMicroseconds(6);
	  }
	  bitZero();
	  delayMicroseconds(6);
	  bitZero();
	  delayMicroseconds(6);
	}
	
    void bitZero()
	{
	  digitalPin.toggle();
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  digitalPin.toggle();
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	}
	
    void bitOne()
	{
	  digitalPin.toggle();
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  digitalPin.toggle();
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	  asm volatile ( "nop":: );
	}
};
#endif
