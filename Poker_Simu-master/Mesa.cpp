#include "Mesa.h"
#include <stdlib.h>
#include <iostream>
#include <array>
#include <string>
#include <time.h>
using namespace std;

Mesa::Mesa()
{
	Tablero = new carta[5];
	Quemada = new carta[3];
	indiceMazo = 0, indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;
	numeroJugadores = 2;
	apuesta = 0;
}
Mesa::~Mesa()
{
	delete[] Tablero;
	delete[] Quemada;
}
void Mesa::repartirCartas(jugador J, carta* Mazo)
{

	J.setMano(Mazo[indiceMazo], Mazo[indiceMazo + numeroJugadores]);
	indiceMazo++;
}

void Mesa::cartaTablero(carta* Mazo)
{
	Tablero[indiceTablero] = Mazo[indiceMazo];
	indiceMazo++;
	indiceTablero++;
}

void Mesa::cartaQuemada(carta* Mazo)
{
	Quemada[indiceQuemada] = Mazo[indiceMazo];
	indiceMazo++;
	indiceQuemada++;
}

void Mesa::recogerApuesta(jugador j)
{
	apuesta = j.getApuesta();
	j.setApuesta(0);
}

void Mesa::entregarApuesta(jugador j)
{
	double dinero_act = j.getDinero();
	j.setDinero(dinero_act + apuesta);
	apuesta = 0;
}

void Mesa::finRonda(jugador winner, jugador loser)
{
	recogerApuesta(winner);
	recogerApuesta(loser);
	entregarApuesta(winner);
	indiceMazo = 0;
	indiceQuemada = 0;
	indiceRonda = 0;
	indiceTablero = 0;
}

carta* Mesa::crearMazo(carta* mazo)
{
	//carta mazo[52];

	srand(time(NULL));
	int p = 1;
	int n = 1;

	for (int i = 0; i < 52; i++)
	{
		mazo[i].setPalo(p);
		mazo[i].setNumero(n);
		n++;
		if (n == 14)
		{
			p++;
			n = 1;
		}

	}
	return mazo;
}

carta* Mesa::barajar(carta* mazo)
{
	int N = 52;
	for (int i = N - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		std::swap(mazo[i], mazo[r]);
	}
	return mazo;
}


void Mesa::imprimirTablero()
{



}