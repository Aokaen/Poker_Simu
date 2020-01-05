#pragma once
#include "carta.h"
#include "Mesa.h"

class jugador
{
protected:
	carta* mano = new carta[2];
	
	float apuesta = 0;
	
	float valor_num_mano = 0;
	bool Escalera_Real_posible;
	bool poker_posible;
	bool escalera_color_posible;
	bool full_posible;
	bool escalera_posible;
	bool color_posible;
	bool trio_posible;
	bool doble_pareja_posible;
	bool pareja_posible;
	bool Escalera_Real_obtenida;
	bool poker_obtenida;
	bool escalera_color_obtenida;
	bool full_obtenida;
	bool escalera_obtenida;
	bool color_obtenida;
	bool trio_obtenida;
	bool doble_pareja_obtenida;
	bool pareja_obtenida;
	bool AllIn;
public:
	carta* mejor_jugada = new carta[5];
	float valor_mano = 0;
	float valor_mano_r1 = 0;
	float valor_mano_r2 = 0;
	float valor_mano_r3 = 0;
	float dinero = 0;
	
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
	void resetApuesta();
	void valorNumericoMano();
	void resetear_bool();
	void ValorManoInicial();
	void ValorManoR1(Mesa T);
	void ValorManoR2(Mesa T);
	void ValorManoR3(Mesa T);
	float calcularValorJugada(carta* c, int i);
	void reseteo_obtenidas();
	void imprimeMano();
	bool getAll();
	void setAll(bool b);

	friend class Mesa;


};
