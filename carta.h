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
    
	void operator <<(Carta c);
	friend class jugador;
	friend class Mesa;
    
};
