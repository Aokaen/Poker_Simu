#pragma once
#include "Mesa.h"
#include "Jugador.h"

class Algoritmo
{
public:
	int tipo = 0;
	float triple[3] = { 0,0,0 };
	bool pasa = false;
	int accion = 0;
	int obtenerAccion();//Randomizar probabilidad y obtener la accion
	void obtenerTriple(Jugador* J, Mesa M); //Lectura del algoritmo en R
	void reseteo();//Reseteo de fin de ronda
	char conversorAccion();


};