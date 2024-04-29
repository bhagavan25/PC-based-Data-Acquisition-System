/*delay.c*/
#include <LPC21xx.H>
void delay_sec(unsigned int sec)
{
int a[]={15,60,30,15,15},b,r;
if(VPBDIV>4)
{
	if(VPBDIV%4==0)
	{
		r=VPBDIV/4;
		b=VPBDIV/r;
	}
	else
		b=VPBDIV%4;
}
else
	b=VPBDIV;
T0PC=0;
T0PR=a[b]*1000000-2;
T0TC=0;
T0TCR=1;
while(T0TC<sec);
T0TCR=0;
}
void delay_ms(unsigned int ms)
{
int a[]={15,60,30,15,15},b,r;
if(VPBDIV>4)
{
	if(VPBDIV%4==0)
	{
		r=VPBDIV/4;
		b=VPBDIV/r;
	}
	else
		b=VPBDIV%4;
}
else
	b=VPBDIV;
T0PC=0;
T0PR=a[b]*1000-2;
T0TC=0;
T0TCR=1;
while(T0TC<ms);
T0TCR=0;
}
