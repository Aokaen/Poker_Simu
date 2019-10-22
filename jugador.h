#pragma once
#include "carta.h"
class jugador
{
protected:
		carta* mano = new carta[2];
		int dinero;
		double valor_mano;
public:
	jugador();
	~jugador();
	void setMano(carta c1, carta c2);
	void setDinero(int d);
	void calcularManoInicial();
	void calcularValorJugada();
	carta* getMano();
	int getDinero();
	double getValor();
};

