#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	~deck();// class destructor
	carta* barajar(carta* c); //aleatorización mazo

};

