#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	~deck();// class destructor
	void barajarInicial(carta c*); //aleatorización inicial del mazo
	void barajar();//aleatorización del mazo cuando se empieza cada mano, intentando simular una aleatorización lo más real posible
	void riffle();
	void box();
	void cut();
};

