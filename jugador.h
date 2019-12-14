#pragma once
#include "carta.h"
class jugador
{
protected:
		carta* mano = new carta[2];
		carta* mejor_jugada = new carta[5];
		float dinero=0, apuesta = 0;
		float valor_mano=0;
		bool Escalera_Real_posible;
		bool poker_posible;
		bool escalera_color_posible;
		bool full_posible;
		bool escalera_posible;
		bool color_posible;
		bool trio_posible;
		bool doble_pareja_posible;
		bool pareja_posible;
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
	//void calcularValorJugada(carta* c);
	void resetear_bool();
	void ValorManoInicial();
	void ValorManoR1(carta* c);
	void ValorManoR2(carta* c);
	void ValorManoR3(carta* c);
	float calcularValorJugada(carta* c);
	void imprimeMano();


};

