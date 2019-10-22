#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	~deck();// class destructor
	carta* barajarInicial(carta* c); //aleatorización inicial del mazo
	carta* barajar(carta* c);//aleatorización del mazo cuando se empieza cada mano, intentando simular una aleatorización lo más real posible
	carta* riffle(carta* c);
	carta* box(carta* c);
	carta* cut(carta* c);
};

