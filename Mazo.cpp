#include "Mazo.h"
#include <time.h>
#include <random>
#include <chrono>
//#include "random.h"

Mazo::Mazo()
{
	int p = 1;
	int n = 1;

	for (int i = 0; i < 52; i++)
	{
		deck[i].setPalo(p);
		deck[i].setNumero(n);
		n++;
		if (n == 14)
		{
			p++;
			n = 1;
		}
	}

	indiceMazo = 0;
}

void Mazo::barajar()
{

	unsigned semilla = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand srng(semilla);

	int N = 52;
//	random j;
	for (int i = N - 1; i > 0; i--)
	{
		int r = srng() % (i + 1);
		//int r = j.nrandom() % (i + 1);
		std::swap(deck[i], deck[r]);
	}


}

void Mazo::repartirCartas(Mesa T, Jugador* J)
{

	for (int i = 0; i < 2; i++)
	{
		J[i].setMano(deck[indiceMazo], deck[indiceMazo + 1]);
		indiceMazo = indiceMazo + 2;
	}
	T.Quemada[0] = deck[indiceMazo];
	indiceMazo++;
	for (int i = 0; i < 3; i++)
	{
		T.Tablero[i] = deck[indiceMazo];
		indiceMazo++;
	}
	T.Quemada[1] = deck[indiceMazo];
	indiceMazo++;
	T.Tablero[3] = deck[indiceMazo];
	indiceMazo++;
	T.Quemada[2] = deck[indiceMazo];
	indiceMazo++;
	T.Tablero[4] = deck[indiceMazo];
}
void Mazo::resetIndiceMazo()
{
	indiceMazo = 0;
}