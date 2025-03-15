#include "Arduino.h"
#include "Display.h"

template <uint8_t pin>
void Display<pin>::attach()
{
  digitalPin.config(OUTPUT, LOW);
  for (int i = 0; i < 64; i++)
  {
    bitZero();
    delayMicroseconds(6);
  }
}

template <uint8_t pin>
void Display<pin>::printSeconds(int num)
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
  printNumW(c);
  printNum(d);
}

template <uint8_t pin>
void Display<pin>::printMinutesSeconds(long int ms)
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

template <uint8_t pin>
void Display<pin>::printVoltage(int value)
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

  printSymbolString(STR_DB_SYMBOL);
}

template <uint8_t pin>
void Display<pin>::printDistance(int value)
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

template <uint8_t pin>
void Display<pin>::printNumber(int num)
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

template <uint8_t pin>
void Display<pin>::printSymbolString(int k)
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

template <uint8_t pin>
void Display<pin>::printNum(int num)
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

template <uint8_t pin>
void Display<pin>::printNumW(int num)
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

template <uint8_t pin>
void Display<pin>::printZero()
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

template <uint8_t pin>
void Display<pin>::bitZero()
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

template <uint8_t pin>
void Display<pin>::bitOne()
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

void DisplayFunction()
{
    Display<30> d;
}