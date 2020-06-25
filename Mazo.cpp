#include "Mazo.h"
#include <time.h>
#include <random>
#include <chrono>
#include "random.h"

Mazo::Mazo()
{
	//Función constructora de mazo, que inicializa las 52 cartas
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
	//Función para aleatorizar las posiciones de los elementos Carta en Mazo
	

	int N = 52;
	random j;
	for (int i = N - 1; i > 0; i--)
	{
		int r = j.randomN(i);
		//int r = j.nrandom() % (i + 1);
		std::swap(deck[i], deck[r]);
	}


}

void Mazo::repartirCartas(Mesa T, Jugador* J)
{
	//Función para realizar el reparto de cartas a jugadores, Mesa y a Quemadas
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
	//Función para reiniciar el índice del mazo
	indiceMazo = 0;
}