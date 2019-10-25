#pragma once
#include "carta.h"
class jugador
{
protected:
		carta* mano = new carta[2];
		int dinero=0;
		double valor_mano=0;
public:
	jugador();
	~jugador();
	void setMano(carta c1, carta c2);
	void setDinero(int d);
	carta* getMano();
	int getDinero();
	double getValor();
	void calcularManoInicial();
	void calcularValorJugada();

};

