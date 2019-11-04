#pragma once


class carta
{
protected:
	int palo=0;
	int numero=0;
public:
	carta();// class constructor
	~carta();// class destructor
	int getNumero();//función para obtener el número de la carta
	int getPalo();// función para obtener el palo de la carta
	void setNumero(int N);
	void setPalo(int P);
	void imprimeCarta();
	void operator <<(carta c);
	friend class jugador;
	
};


