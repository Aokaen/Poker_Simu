#include "random.h"
#include <stdio.h>
#include <math.h>

static unsigned long long
x = 1234567890987654321ULL,
c = 123456123456123456ULL,
y = 362436362436362436ULL,
z = 1066149217761810ULL,
t;
#define MWC (t=(x<<58)+c, c=(x>>6), x+=t, c+=(x<t), x)
#define XSH ( y^=(y<<13), y^=(y>>17), y^=(y<<43) )
#define CNG ( z=6906969069LL*z+1234567 )
#define KISS (MWC+XSH+CNG)


float random::nrandomPorcent()
{
	float a = 0;
	t = KISS;
	a = t / pow(2, 64);
	return(a);

}

float random::randomN(int n)
{
	t = KISS%n;
	return t;

}
