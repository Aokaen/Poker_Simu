#include "Mesa.h"

void Mesa::repartirCartas(jugador J, deck Mazo)
{

	J.setMano(Mazo[indiceMazo], Mazo[indiceMazo + numeroJugadores]);
}