/*******************************************************************************
* ʵ �� ��		 : ������ˮ��ʵ��
* ʹ�õ�IO	     : P2
* ʵ��Ч��       : ������LED���ұ�������ƶ���������������ұ��ƶ�������ѭ����
* ע    ��		 ��
*******************************************************************************/
#include<reg52.h>
#include<intrins.h>		//��ΪҪ�õ������ƺ��������Լ������ͷ�ļ�				 

#define GPIO_LED P1		//��P1������ȡ��ΪGPIO_LED
#define K1 P2^0		//��P0.1������ȡ��ΪK1 ����LED����
#define K2 P2^1		//��P0.3������ȡ��ΪK2 ����LED����
#define K3 P2^2	//��P0.5������ȡ��ΪK3 ����LEDϨ��
#define K4 P2^3		//��P0.7������ȡ��ΪK4 ����LED����

void IntConfiguration();
void Delay50us();
void Delay10ms(unsigned int c);   //��� 0us
void CrolLed(); //����LED
void CrorLed(); //����LED
void DestroyLed(); //LEDϨ��
void StrobeLed(); //LED����
void ChangeKey();
unsigned char KeyValue = 3;
unsigned int InitLed = 0xfe;
unsigned int FullBright = 0x00;
unsigned int FullDestroy = 0xff;
/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��     	 : ��
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
	for (n = 0; n < 8 && KeyValue == 1; n++)							 //����7�Σ������Ӿͻᵽ�����ұ�
	{
		GPIO_LED = _cror_(GPIO_LED, 1);	//��GPIO_LED����һλ
		Delay10ms(50);								//��ʱ
	}
}
void CrolLed()
{
	unsigned char n;
	for (n = 0; n < 8 && KeyValue == 2; n++)						 //����7�Σ������Ӿͻᵽ�������
	{
		GPIO_LED = _crol_(GPIO_LED, 1); //��GPIO_LED����һλ
		Delay10ms(50);							 //��ʱ
	}

}
/*******************************************************************************
* �� �� ��         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Delay10ms(unsigned int c)   //��� 0us
{
	unsigned char a, b;
	for (; c > 0; c--)
		for (b = 38; b > 0; b--)
			for (a = 130; a > 0; a--);
}
/*******************************************************************************
* �� �� ��         : IntConfiguration()
* ��������		   : �����ⲿ�ж�
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void IntConfiguration()
{
	//����INT1
	IT1 = 1;//�����س�����ʽ�������أ�
	EX1 = 1;//��INT1���ж�����
	EA = 1;//�����ж�	
}
/*******************************************************************************
* �� �� ��         : Delay(unsigned int n)
* ��������		   : ��ʱ
* ��    ��         : n
* ��    ��         : ��
*******************************************************************************/

void Delay50us()   //��ʱ50us��� 0us
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
	Delay50us();		//��ʱ����
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
* �� �� ��         : Int1() interrupt 1
* ��������		   : �ⲿ�ж�1���жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Int1() interrupt 2		//�ⲿ�ж�1���жϺ���
{
	EA = 0;
	ChangeKey();
	EA = 1;//�����ж�	
}