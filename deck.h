#pragma once
#include "carta.h"
class deck :
	public carta
{
public:

	deck();// class constructor
	//deck(carta* c);// class conversor
	~deck();
	// class destructor
	void barajar(carta* m); //aleatorización mazo

};

