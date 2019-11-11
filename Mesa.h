#pragma once
#include "carta.h"
#include "jugador.h"
class Mesa
{
public:
	carta* Tablero;
	carta* Quemada;
	int indiceMazo, indiceTablero, indiceQuemada, indiceRonda;
	float apuesta;
	
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
	bool finRonda(jugador winner, jugador loser);
	void creaTablero();
	void modificaTablero(jugador* j);
	void imprimirTablero(jugador* j);
	char conversorNumero(carta c);
	char conversorPalo(carta c);


	friend class jugador;
};

