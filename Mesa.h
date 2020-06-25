#pragma once

#include "Carta.h"
#include "Jugador.h"
class Mazo;

class Mesa
{

protected:

	int indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;

public:

	Carta* Tablero = new Carta[5]; // Array de elementos Carta que representa las cartas en la mesa
	Carta* Quemada = new Carta[3]; // Array de elementos Carta que representa las cartas que se "queman" durante la partida

	float apuesta = 0;
	char tablero_juego[11][26];

	Mesa();
	~Mesa();

	bool modoJ;

	void creaTablero();
	void modificaTablero(Jugador* j);
	void imprimirTablero(Jugador* j);

	void entregarApuesta(Jugador j);
	void finRonda(Mazo m);
	void actualizarApuesta(Jugador* J);

	void resetIndiceTablero();
	void upIndiceTablero();
	int getIndiceTablero();



	void resetIndiceQuemada();
	void upIndiceQuemada();
	int getIndiceQuemada();

	void resetIndiceRonda();
	void upIndiceRonda();
	int getIndiceRonda();

	void CalculaApuestaTotal(Jugador* J);

	bool continuar();

	char conversorNumero(Carta c);
	char conversorPalo(Carta c);


	friend class Jugador;

};