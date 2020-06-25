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
	//función para crear un número pseudoaleatorio con bajo periodo con el fin
	//de determinar cuantas veces se hace el warm up antes de obtener el número pseudoaleatorio deseado
	struct timespec ts;
	if (timespec_get(&ts, TIME_UTC) != 0) {
		srand(ts.tv_nsec ^ ts.tv_sec);
		return rand();
	}
}


void randk_reset(void)
{
	//Función para reiniciar la semilla a la semilla por defecto.
	j = QSIZE - 1;
	carry = 0;
	xs = 362436362436362436ULL;
	cng = 1066149217761810ULL; /* use this as the seed */
}

u64 B64MWC(void)
{
	//Función para calcular la multiplicación con acarreo
	u64 t, x;
	j = (j + 1) & (QSIZE - 1);
	x = QARY[j];
	t = (x << 58) + carry;
	carry = (x >> 6) - (t < x);
	return (QARY[j] = t - x);
}


void randk_seed(void)
{
	//Función para inicializar el generador KISS con la semilla por defecto
	u64 i;
	for (i = 0; i < QSIZE; i++)
		QARY[i] = CNG + XS;
}

void randk_seed_manual(u64 seed)
{
	//Función para asignar una semilla manualmente
	cng ^= seed;
	xs ^= cng;
	randk_seed();
}

u64 randk(void)
{
	//Función para generar un número pseudoaleatorio usando el generador KISS
	return KISS;
}


void randk_warmup(int rounds)
{
	//Función para ejecutar rounds veces el KISS
	int i;
	for (i = 0; i < rounds; i++)
		randk();
}

float random::nrandomPorcent()
{
	//función para obtener un número decimal entre 0 y 1
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
	//Función para obtener un número entre 0 y n
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
