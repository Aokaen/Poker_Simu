#pragma once
#include "carta.h"
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
	char tablero_juego[11][26];

	Mesa();
	~Mesa();
	carta* crearMazo();
	carta* barajar(carta* c);
	void repartirCartas(jugador j, carta* mazo);
	void cartaTablero(carta* mazo);
	void cartaQuemada(carta* mazo);
	void recogerApuesta(jugador j);
	void entregarApuesta(jugador j);
	void finRonda(jugador winner, jugador loser);
	void creaTablero();
	void modificaTablero();
	void imprimirTablero();
	char conversorNumero(carta c);
	char conversorPalo(carta c);
};

