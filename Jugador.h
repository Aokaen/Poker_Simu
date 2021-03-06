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
    
	
	bool escalera_real_obtenida;
	bool poker_obtenida;
	bool escalera_color_obtenida;
	bool full_obtenida;
	bool escalera_obtenida;
	bool color_obtenida;
	bool trio_obtenida;
	bool doble_pareja_obtenida;
	bool pareja_obtenida;

	
    
public:
    
	Carta* mejor_jugada = new Carta[5];

	float valor_mano = 0;
	float valor_mano_r1 = 0;
	float valor_mano_r2 = 0;
	float valor_mano_r3 = 0;

	float dinero = 0;
	int turno = 0;
	bool AllIn;
	Jugador();
	~Jugador();
    
    Carta* getMano();
	void setMano(Carta c1, Carta c2);

    float getDinero();
	void setDinero(float d);
    
	float getValor();
    
	float getApuesta();
	void setApuesta(float ap);
    
    float getApuestaInicial();
	void setApuestaInicial(float ap);
    
    
    void resetBool();
	void resetApuesta();
    void resetObtenidas();

	void valorManoInicial();
	void valorManoR1(Mesa T);
	void valorManoR2(Mesa T);
	void valorManoR3(Mesa T);
	float calcularValorJugada(Carta* c, int i);
    
	void imprimirMano();

	friend class Mesa;
	friend class Algoritmo;

};
