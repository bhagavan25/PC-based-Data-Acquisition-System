/*adc_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void adc_init(void)
{
	PINSEL1 |=0x15400000;
	ADCR=0x00200400;
}
#define DONE ((ADDR>>31)&1)
unsigned int adc_read(int ch_num)
{
	unsigned int result=0;
	ADCR |=(1<<ch_num); //select ch_num
	ADCR |=(1<<24); //start conversion
	while(DONE==0);
	ADCR ^=(1<<24); //stop conversion
	ADCR ^=(1<<ch_num); //de-select ch_num
	result=(ADDR>>6)&0x3ff; //extract result
	return result;
}
