#pragma once

#include "Carta.h"
#include "Jugador.h"

class Mesa
{

protected:
    
	int indiceMazo = 0, indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;
	
public:
    
	Carta* Tablero = new Carta[5];
	Carta* Quemada = new Carta[3];
    
	float apuesta = 0;
	char tablero_juego[11][26];

	Mesa();
	~Mesa();
    
	Carta* crearMazo();
	Carta* barajar(Carta* c);
	void repartirCartas(Jugador* j, Carta* mazo, Carta* tablero, Carta* Quemada);

	void creaTablero();
	void modificaTablero(Jugador* j);
	void imprimirTablero(Jugador* j);

	void cartaTablero(Carta* mazo);
	void cartaQuemada(Carta* mazo);
	
	void entregarApuesta(Jugador j);
	void finRonda();


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

	void CalculaApuestaTotal(Jugador* J);

	bool continuar();

	char conversorNumero(Carta c);
	char conversorPalo(Carta c);

	friend class Jugador;
    
};
