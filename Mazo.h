#pragma once
#include"Carta.h"
#include "Jugador.h"
#include "Mesa.h"

class Mazo
{
public:
	Carta deck[52];
	int indiceMazo;

	Mazo();
	void barajar();
	void repartirCartas(Mesa Table, Jugador* J);
	void resetIndiceMazo();
};