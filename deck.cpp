#include "deck.h"
#include <stdlib.h>
#include <iostream>
#include <array>

deck::deck()
{

for (int i = 0; i < 4; i++)
{
	for ()
	palo = Palos[p];
	numero = Numeros[n];
	n++;
	if (n == 12)
	{
		n = 0;
		p++;
	}
}
barajarInicial(mazo);
}

// class destructor
deck::~deck()
{
	// insert your code here
}

void deck::barajarInicial(carta c*) // Fisher-yites
{
	int N = 52;
	for (int i = N - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		swap(c[i], c[r]);
	}
}
void deck::riffle()
{
	int n = rand() % (8);
	int j = rand() % (1);
	int s = 0;
	if (j == 0)
	{
		a = 26 + n;
		b = 26 - n;
	}
	else
	{
		a = 26 - n;
		b = 26 + n;
	}
	semimazo1 = new carta[a];
	semimazo2 = new carta[b];
	for (int i = 0; i < a; i++)
	{
		semimazo1[i] = mazo[i];
	};
	for (int i = 0; i < b; i++)
	{
		semimazo2[i] = mazo[a + i];
	};
}
void deck::barajar()
{
	riffle();
	riffle();
	box();
	riffle();
	cut();


}