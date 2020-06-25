#pragma once
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"

class Algoritmo
{
public:
	int tipo = 0;
	float triple[3] = { 0,0,0 };
	bool pasa = false;
	int accion = 0;
	int obtenerAccion(Jugador J, Mesa M);
	int obtenerAccionSegundo(Jugador J, Mesa M, int accionprevia);
	int  obtenerAccionAct(Jugador J, Mesa M, int accionprevia);
	void obtenerTriple(Jugador J, Mesa M);
	void obtenerTripleAccion(Jugador J, Mesa M, int accionprevia);
	void obtenerTripleAct(Jugador J, Mesa M, int accionprevia);
	void reseteo();
	void pasar(int ronda);
	int obtenerSubida(float apuesta, float apuesta_ini);
	void actualizaBayes(int ronda);

};