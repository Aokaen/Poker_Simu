#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	~deck();// class destructor
	carta* barajarInicial(carta* c); //aleatorizaci�n inicial del mazo
	carta* barajar(carta* c);//aleatorizaci�n del mazo cuando se empieza cada mano, intentando simular una aleatorizaci�n lo m�s real posible
	carta* riffle(carta* c);
	carta* box(carta* c);
	carta* cut(carta* c);
};

