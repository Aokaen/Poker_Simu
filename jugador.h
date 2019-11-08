#pragma once
#include "carta.h"
class jugador
{
protected:
		carta* mano = new carta[2];
		float dinero=0, apuesta = 0;
		float valor_mano=0;
public:
	jugador();
	~jugador();
	void setMano(carta c1, carta c2);
	void setDinero(float d);
	carta* getMano();
	float getDinero();
	float getValor();
	//void setValorInicial(); una vez implementada la heuristica
	//void setValor(float i); una vez implementada la heuristica
	float getApuesta();
	void setApuesta(float ap);
	void calcularValorJugada(carta* c);
	void imprimeMano();


};

