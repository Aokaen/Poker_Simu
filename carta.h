#pragma once


class carta
{
protected:
	int palo;
	int numero;
public:
	carta();// class constructor
	~carta();// class destructor
	int getNumero();//funci�n para obtener el n�mero de la carta
	int getPalo();// funci�n para obtener el palo de la carta
	void setNumero(int N);
	void setPalo(int P);
	void imprimeCarta();
	friend class jugador;
};


