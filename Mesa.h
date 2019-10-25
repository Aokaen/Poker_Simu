#pragma once
#include "carta.h"
#include "deck.h"
#include "jugador.h"
class Mesa
{
public:
	carta* Tablero = new carta[5];
	carta* Quemada = new carta[3];
	int indiceMazo = 0, indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;
	int numeroJugadores = 2;
	double apuesta = 0;
	void repartirCartas(jugador j, deck mazo);
	void cartaTablero();
	void cartaQuemada();
	void recogerApuesta(jugador j);
	void entregarApuesta(jugador j);
	void finRonda(jugador winner);
};

