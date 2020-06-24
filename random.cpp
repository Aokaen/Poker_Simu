#include "random.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <iostream>

typedef uint64_t u64;

#define QSIZE 0x200000
#define CNG (cng = 6906969069ULL * cng + 1234567)
#define XS (xs ^= (xs << 13), xs ^= (xs >> 17), xs ^= (xs << 43))
#define KISS (B64MWC() + CNG + XS)

static u64 QARY[QSIZE];
static int j;
static u64 carry;
static u64 xs;
static u64 cng;

int func()
{
	struct timespec ts;
	if (timespec_get(&ts, TIME_UTC) == 0) {
		/* Handle error */
	}
	else {
		srand(ts.tv_nsec ^ ts.tv_sec);
		return rand();
	}
}


void randk_reset(void)
{
	j = QSIZE - 1;
	carry = 0;
	xs = 362436362436362436ULL;
	cng = 1066149217761810ULL; /* use this as the seed */
}

u64 B64MWC(void)
{
	u64 t, x;
	j = (j + 1) & (QSIZE - 1);
	x = QARY[j];
	t = (x << 58) + carry;
	carry = (x >> 6) - (t < x);
	return (QARY[j] = t - x);
}

/* Initialize PRNG with default seed */
void randk_seed(void)
{
	u64 i;
	/* Seed QARY[] with CNG+XS: */
	for (i = 0; i < QSIZE; i++)
		QARY[i] = CNG + XS;
}

void randk_seed_manual(u64 seed)
{
	cng ^= seed;
	xs ^= cng;
	randk_seed();
}

/* Generate a pseudorandom 64-bit unsigned integer. */
u64 randk(void)
{
	return KISS;
}


void randk_warmup(int rounds)
{
	int i;
	/* Run through several rounds to warm up the state */
	for (i = 0; i < rounds; i++)
		randk();
}

float random::nrandomPorcent()
{
	float a = 0;
	static unsigned long long h,j;
	randk_seed();
	j = func();
	randk_warmup(j);
	h = randk();
	randk_seed_manual(h);
	h = randk();
	a = h / pow(2, 64);
	return(a);

}

int random::randomN(int n)
{
	static unsigned long long h,j;
	randk_seed();
	j = func();
	randk_warmup(j);
	h = randk();
	randk_seed_manual(h);
	h = randk();
	h = KISS%n;
	return h;

}
