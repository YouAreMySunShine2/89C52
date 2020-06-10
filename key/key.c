/*******************************************************************************
* 实 验 名		 : 左右流水灯实验
* 使用的IO	     : P2
* 实验效果       : 点亮的LED从右边往左边移动，到达左边再往右边移动，依此循环。
* 注    意		 ：
*******************************************************************************/
#include<reg52.h>
#include<intrins.h>		//因为要用到左右移函数，所以加入这个头文件				 

#define GPIO_LED P1		//将P1口另外取名为GPIO_LED
#define K1 P2^0		//将P0.1口另外取名为K1 功能LED右移
#define K2 P2^1		//将P0.3口另外取名为K2 功能LED左移
#define K3 P2^2	//将P0.5口另外取名为K3 功能LED熄灭
#define K4 P2^3		//将P0.7口另外取名为K4 功能LED爆闪

void IntConfiguration();
void Delay50us();
void Delay10ms(unsigned int c);   //误差 0us
void CrolLed(); //左移LED
void CrorLed(); //右移LED
void DestroyLed(); //LED熄灭
void StrobeLed(); //LED爆闪
void ChangeKey();
unsigned char KeyValue = 3;
unsigned int InitLed = 0xfe;
unsigned int FullBright = 0x00;
unsigned int FullDestroy = 0xff;
/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出     	 : 无
*******************************************************************************/

void main(void)
{
	GPIO_LED = InitLed;
	IntConfiguration();
	P2 = 0xff;
	while (1)
	{
		GPIO_LED = InitLed;
		switch (KeyValue)
		{
		case 1:CrorLed(); break;
		case 2:CrolLed(); break;
		case 3:DestroyLed(); break;
		case 4:StrobeLed(); break;
		default:GPIO_LED = FullDestroy;
			break;
		}
	}
}
void DestroyLed()
{
		GPIO_LED = FullDestroy;
		Delay10ms(50);

}
void StrobeLed()
{
	while (KeyValue == 4) {
		GPIO_LED = FullBright;
		Delay10ms(50);
		GPIO_LED = FullDestroy;
		Delay10ms(50);
	}
}
void CrorLed()
{
	unsigned char n;
	for (n = 0; n < 8 && KeyValue == 1; n++)							 //右移7次，这样子就会到达最右边
	{
		GPIO_LED = _cror_(GPIO_LED, 1);	//将GPIO_LED右移一位
		Delay10ms(50);								//延时
	}
}
void CrolLed()
{
	unsigned char n;
	for (n = 0; n < 8 && KeyValue == 2; n++)						 //左移7次，这样子就会到达最左边
	{
		GPIO_LED = _crol_(GPIO_LED, 1); //将GPIO_LED左移一位
		Delay10ms(50);							 //延时
	}

}
/*******************************************************************************
* 函 数 名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Delay10ms(unsigned int c)   //误差 0us
{
	unsigned char a, b;
	for (; c > 0; c--)
		for (b = 38; b > 0; b--)
			for (a = 130; a > 0; a--);
}
/*******************************************************************************
* 函 数 名         : IntConfiguration()
* 函数功能		   : 设置外部中断
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void IntConfiguration()
{
	//设置INT1
	IT1 = 1;//跳变沿出发方式（上升沿）
	EX1 = 1;//打开INT1的中断允许。
	EA = 1;//打开总中断	
}
/*******************************************************************************
* 函 数 名         : Delay(unsigned int n)
* 函数功能		   : 延时
* 输    入         : n
* 输    出         : 无
*******************************************************************************/

void Delay50us()   //延时50us误差 0us
{
	unsigned char a, b, n;
	for (n = 1; n > 0; n--)
	{
		for (b = 1; b > 0; b--)
			for (a = 22; a > 0; a--);
	}
}

void ChangeKey()
{
	P2 = 0xff;
	Delay50us();		//延时消抖
	if (P2 == 0xff) {
		KeyValue = 3;
	}
	if (P2 == 0xfe)
	{
		KeyValue = 1;
	}
	if (P2 == 0xfd)
	{ 
		KeyValue = 2;
	}
	if (P2 == 0xfb)
	{
		KeyValue = 3;
	}
	if (P2 == 0xf7)
	{
		KeyValue = 4;
	}
}
/*******************************************************************************
* 函 数 名         : Int1() interrupt 1
* 函数功能		   : 外部中断1的中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Int1() interrupt 2		//外部中断1的中断函数
{
	EA = 0;
	ChangeKey();
	EA = 1;//打开总中断	
}