// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"

using namespace std;
int main()
{
	Mesa Tablero;
	iniciarPartida();
	carta* mazo = new carta[52];
	mazo = Tablero.crearMazo(mazo);
	mazo = Tablero.barajar(mazo);
	for (int i = 0; i < 52; i++)
	{
		mazo[i].imprimeCarta();
	}


	system("PAUSE");
}

void iniciarPartida()
{


}

void verApuesta() {}

void subirApuesta(double qty) {}

void pasarApuesta() {}

void ronda() {}
