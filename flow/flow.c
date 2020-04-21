#include <reg52.h>
#define unint unsigned int
#define unchart unsigned char
void delayed(unint z);
main()
{
	while (1)
	{
	P1 = 0xfe;
	delayed(500);
	P1 = 0xfd;
	delayed(500);
	P1 = 0xfb;
	delayed(500);
	P1 = 0xf7;
	delayed(500);
	P1 = 0xef;
	delayed(500);
	P1 = 0xdf;
	delayed(500);
	P1 = 0xbf;
	delayed(500);
	P1 = 0x7f;
	delayed(500);
	}
	
}
void delayed(unint z) {
	unint x, y;
	for (x=0;x<z;x++)
	{
		for (y = 0; y < 110;y++);
	}

}
