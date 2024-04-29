/*SPI0_driver.c*/
#include <LPC21xx.H>
#include "header.h"

void spi0_init(void)
{
PINSEL0 |=0x1500; //P0.4-->CLK0,P0.5-->MISO,P0.6-->MOSI
IODIR0|=CS0;
IOSET0=CS0;
S0SPCR=0x20;//CPOL=CPHA=0 ,master mode selected, MSB first
S0SPCCR=150;//SPI0 freq is 100kbps
}

#define SPIF ((S0SPSR>>7)&1)
unsigned char spi0_txrx(unsigned char data)
{
S0SPDR=data;//data to slave
while(SPIF==0);
return S0SPDR;//data from slave
}
unsigned short int mcp3204_adc_read(unsigned char ch_num)
{
unsigned short int result=0;
unsigned char byteH=0,byteL=0,channel=0;
channel=ch_num<<6;
IOCLR0=CS0;
spi0_txrx(0x6);//start bit& select SGL mode
byteH=spi0_txrx(channel);//channel selection
byteL=spi0_txrx(0x00);
IOSET0=CS0;//deselect slave
byteH &=0x0F;//masking higher nibble;
result=(byteH<<8)|byteL;//merge result;
return result;
}
