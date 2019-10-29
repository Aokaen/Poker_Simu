#pragma once
#include "carta.h"
class jugador
{
protected:
		carta* mano = new carta[2];
		double dinero=0;
		double valor_mano=0, apuesta=0;
public:
	jugador();
	~jugador();
	void setMano(carta c1, carta c2);
	void setDinero(double d);
	carta* getMano();
	double getDinero();
	double getValor();
	//void setValorInicial(); una vez implementada la heuristica
	//void setValor(double i); una vez implementada la heuristica
	double getApuesta();
	void setApuesta(double ap);
	void calcularManoInicial();
	void calcularValorJugada();


};

