#pragma once
#include "carta.h"
#include "deck.h"
#include "jugador.h"
class Mesa
{
public:
	carta* Tablero;
	carta* Quemada;
	int indiceMazo, indiceTablero, indiceQuemada, indiceRonda;
	int numeroJugadores;
	double apuesta;
	jugador Jugadores[2];
	Mesa();
	~Mesa();
	void repartirCartas(jugador j, carta* mazo);
	void cartaTablero(carta* mazo);
	void cartaQuemada(carta* mazo);
	void recogerApuesta(jugador j);
	void entregarApuesta(jugador j);
	void finRonda(jugador winner, jugador loser);
};

