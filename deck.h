#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	~deck();// class destructor
	void barajarInicial(carta c*); //aleatorizaci�n inicial del mazo
	void barajar();//aleatorizaci�n del mazo cuando se empieza cada mano, intentando simular una aleatorizaci�n lo m�s real posible
	void riffle();
	void box();
	void cut();
};

