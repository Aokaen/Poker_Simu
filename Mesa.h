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
	void cartaTablero(Carta* mazo);
	void cartaQuemada(Carta* mazo);
	//void recogerApuesta(jugador j);
	void entregarApuesta(Jugador j);
	void finRonda();
	void creaTablero();
	void modificaTablero(Jugador* j);
	void imprimirTablero(Jugador* j);
	char conversorNumero(Carta c);
	char conversorPalo(Carta c);
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
	//void setapuesta(float f);
	//float getapuesta();
	void CalculaApuestaTotal(Jugador* J);
	//void resetapuesta();
	bool continuar();

	friend class jugador;
    
};
