/*DAS_project.c*/
#include<LPC21xx.H>
#include"header.h"
main()
{
	unsigned int adcval,pot;
	unsigned short int ext_adc;
	float vout,tempr,press,ldr;
	adc_init();
	uart0_init(9600);
	spi0_init();
	while(1)
	{
		adcval=adc_read(1);
		pot=adc_read(2);
		vout=(adcval*3.3)/1023;
		tempr=(vout-0.5)/0.01; //get tempr
		uart0_tx_string("\r\ntemp=");
		uart0_tx_float(tempr);
		uart0_tx_string(" C");
		delay_ms(1000);
		vout=(pot*3.3)/1023;
		press=((vout/4.8)+0.095)/0.009;
		uart0_tx_string("\r\npressure=");
		uart0_tx_float(press);
		uart0_tx_string("pascal");
		delay_ms(1000);
        ext_adc=mcp3204_adc_read(2);
        vout=((ext_adc*100)/4095);
        ldr=100-vout;
		uart0_tx_string("\r\nldr=");
        uart0_tx_float(ldr);
		uart0_tx_string("%");
        delay_sec(1);
	}
}
