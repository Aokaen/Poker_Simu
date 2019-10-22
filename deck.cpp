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

carta* deck::barajarInicial(carta* c) // Fisher-yites para simular Washing
{
	int N = 52;
	for (int i = N - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		std::swap(c[i], c[r]);
	}
	return c;
}
carta* deck::riffle(carta* c)
{
	int n = rand() % (8);
	int j = rand() % (2);
	int s = 0;
	int a, b;
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
	carta* semimazo1 = new carta[a];
	carta* semimazo2 = new carta[b];
	for (int i = 0; i < a; i++)
	{
		semimazo1[i] = c[i];
	};
	for (int i = 0; i < b; i++)
	{
		semimazo2[i] = c[a + i];
	};
	int a_aux = a, b_aux = b;

	for (int i = 52; i == 0; i--)
	{
		if (a < b)
		{
			if (a_aux <= 0)
			{
				if (i % 2 == 0)
				{
					c[i] = semimazo1[a_aux];
					a_aux--;
				}
				else
				{
					c[i] = semimazo2[b_aux];
					b_aux--;
				}
			}
			else
			{
				c[i] = semimazo2[b_aux];
				b_aux--;
			}
		}
		else if (b < a)
		{
			if (b_aux <= 0)
			{
				if (i % 2 == 0)
				{
					c[i] = semimazo1[a_aux];
					a_aux--;
				}
				else
				{
					c[i] = semimazo2[b_aux];
					b_aux--;
				}
			}
			else
			{
				c[i] = semimazo1[a_aux];
				a_aux--;
			}
		}
		else if (b == a)
		{
			if (i % 2 == 0)
			{
				c[i] = semimazo1[a_aux];
				a_aux--;
			}
			else
			{
				c[i] = semimazo2[b_aux];
				b_aux--;
			}
		}
	}

	return c;
}
carta* deck::box(carta* c)
{
	int veces = rand() % (5-3);
	carta* mazo_aux = new carta[52];
	int fraccion = int(52 / veces);
	int cortes[4];
	int aux = 0, sumatotal=0, n_cartas=0;

	do
	{
		if (aux+1 < veces)
		{
			int margen = rand() % (6);
			int signo = rand() % (2);

			if (signo == 0)
			{
				n_cartas = fraccion + margen;
			}
			else if(signo ==1)
			{
				n_cartas = fraccion - margen;
			}
			cortes[aux] = n_cartas;
			sumatotal = sumatotal + n_cartas;
			aux++;
		}
		else if (aux + 1 == veces)
		{
			cortes[aux] = 52 - sumatotal;
			sumatotal = 52;
		}
		if (veces == 3)
			cortes[3] = 0;
	} while (aux < veces);
	int posicion = 52, corte = 0;
	for (int i = 0; i < veces; i++)
	{
		if (cortes[i] > 0)
		{
			posicion = posicion - cortes[i];
			for (int j = 0; j < cortes[i]; j++)
			{
				mazo_aux[posicion + j] = c[corte + j];
			}
			corte = cortes[i];
		}
	}
	return mazo_aux;
}

carta* deck::cut(carta* c)
{
	carta* mazo_aux = new carta[52];
	int corte1 = rand() % (36 - 15);
	int corte2 = 52 - corte1;

	for (int i = 0; i < corte1; i++)
	{
		mazo_aux[corte1 + i] = c[i];
	}
	for (int i = 0; i < corte2; i++)
	{
		mazo_aux[i] = c[corte1 + i];
	}
	return mazo_aux;
}

carta* deck::barajar(carta* c)
{
	c=riffle(c);
	c=riffle(c);
	c=box(c);
	c=riffle(c);
	c=cut(c);
	return c;

}