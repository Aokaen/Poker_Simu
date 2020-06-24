#pragma once

class Carta
{
    
protected:
    
	int palo=0;
	int numero=0;
    
public:
    
	Carta();
	~Carta();
    
	int getNumero();
    void setNumero(int N);

	int getPalo();
	void setPalo(int P);
    
	void imprimirCarta();
 
	friend class Jugador;
	friend class Mesa;
	friend class Algoritmo;
    
};
