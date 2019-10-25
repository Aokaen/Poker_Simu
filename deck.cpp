#include "deck.h"
#include <stdlib.h>
#include <iostream>
#include <array>

deck::deck()
{
	carta* mazo = new carta[52];
	
	int p = 1;
	int n = 1;
	
for (int i = 0; i < 4; i++)
{
	mazo[i].setPalo(p);
	mazo[i].setNumero(n);
	n++;
	if (n==14)
	{
		p++;
		n = 1;
	}

}
	mazo = barajarInicial(mazo);
}

// class destructor
deck::~deck()
{
	// insert your code here
}

carta* deck::barajar(carta* c) // Fisher-yites para simular Washing
{
	int N = 52;
	for (int i = N - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		std::swap(c[i], c[r]);
	}
	return c;
}

