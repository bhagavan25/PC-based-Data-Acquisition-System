/*uart0_driver.c*/
#include <LPC21xx.H>
#include <stdio.h>
void uart0_init(unsigned int baud)
{
int a[]={15,60,30,15,15};
unsigned int pclk=a[VPBDIV]*1000000;
unsigned int result=0;
result=pclk/(16*baud);
PINSEL0 |=0x05;  //P0.0-->TxD0 , P0.1-->RxD0
U0LCR=0x83; //for setting baud rate,8-data bits,1 stop bit,DLAB=1
U0DLL=result&0xFF;  //extracting lower 8 bits
U0DLM=(result>>8)&0xFF;  //extracting higher 8 bits
U0LCR=0x03;  //for locking baud rate,8-data bits,1 stop bit,DLAB=0
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}
void uart0_tx_string(char *ptr)
{
	while(*ptr)
	{
		uart0_tx(*ptr);
		ptr++;
	}
}
#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}
void uart0_rx_string(char* p,unsigned int max_bytes)
{
	int i;
	for(i=0;i<max_bytes;i++)
	{
		p[i]=uart0_rx();
		if(p[i]=='\r')
			break;
	}
	p[i]='\0';
}
void uart0_tx_integer(int num)
{
	char buf[10];
	sprintf(buf,"%d",num);
	uart0_tx_string(buf);
}
void uart0_tx_float(float num)
{
	char buf[10];
	sprintf(buf,"%.1f",num);
	uart0_tx_string(buf);
}
