#pragma once

#include "Carta.h"

class Mesa;

class Jugador
{
    
protected:
    
	Carta* mano = new Carta[2];
	
	float apuesta = 0;
	float apuestaInicial = 0;
	float valor_num_mano = 0;
    
	bool escalera_real_posible;
	bool poker_posible;
	bool escalera_color_posible;
	bool full_posible;
	bool escalera_posible;
	bool color_posible;
	bool trio_posible;
	bool doble_pareja_posible;
	bool pareja_posible;
	bool escalera_real_obtenida;
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
    
	Carta* mejor_jugada = new Carta[5];

	float valor_mano = 0;
	float valor_mano_r1 = 0;
	float valor_mano_r2 = 0;
	float valor_mano_r3 = 0;
	float dinero = 0;
	
	Jugador();
	~Jugador();
    
    Carta* getMano();
	void setMano(Carta c1, Carta c2);

    float getDinero();
	void setDinero(float d);
    
	float getValor();
	//void setValorInicial(); una vez implementada la heuristica
	//void setValor(float i); una vez implementada la heuristica
    
	float getApuesta();
	void setApuesta(float ap);
    
    float getApuestaInicial();
	void setApuestaInicial(float ap);
    
    bool getAllIn();
    void setAllIn(bool b);
    
    void resetBool();
	void resetApuesta();
    void resetObtenidas();

	void valorNumericoMano();
	void valorManoInicial();
	void valorManoR1(Mesa T);
	void valorManoR2(Mesa T);
	void valorManoR3(Mesa T);
	float calcularValorJugada(Carta* c, int i);
    
	void imprimirMano();

	friend class Mesa;

};
