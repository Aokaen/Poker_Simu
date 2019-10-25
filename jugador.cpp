#include "jugador.h"
#include "carta.h"

jugador::jugador()
{

}
jugador::~jugador()
{

}

void jugador::setMano(carta c1, carta c2)
{
	mano[0] = c1;
	mano[1] = c2;
}

void jugador::setDinero(int d)
{
	dinero = d;
}
void jugador::calcularManoInicial()
{

}

void jugador::calcularValorJugada()
{

}

carta* jugador::getMano()
{
	return mano;
}

int jugador::getDinero()
{
	return dinero;
}

double jugador::getValor()
{
	return valor_mano;
}