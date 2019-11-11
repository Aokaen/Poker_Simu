#pragma once
#include "carta.h"
#include "jugador.h"
class Mesa
{
protected:
	int indiceMazo = 0, indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;
	float apuesta = 0;
public:
	carta* Tablero = new carta[5];
	carta* Quemada = new carta[3];
	
	
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
	void resetIndiceTablero();
	void upIndiceTablero();
	int getIndiceTablero();
	void resetIndiceMazo();
	void upIndiceMazo();
	int getIndiceMazo();
	void resetIndiceQuemada();
	void upIndiceQuemada();
	int getIndiceQuemada();
	void resetIndiceRonda();
	void upIndiceRonda();
	int getIndiceRonda();
	void setapuesta(float f);
	float getapuesta();


	friend class jugador;
};

