// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"
#define NUM 2

using namespace std;
int main()
{
	Mesa Tablero;
	carta* mazo = Tablero.crearMazo();

	iniciarPartida(Tablero, mazo);
	jugarPartida(Tablero, mazo);

	system("PAUSE");
}

void iniciarPartida(Mesa T, carta* c)
{
	double dinero=0;

	cout << "Introduce cantidad inicial de dinero para los jugadores:" << endl;
	cin >> dinero;
	T.Jugadores[0].setDinero(dinero);
	T.Jugadores[1].setDinero(dinero);
	T.creaTablero();
}

void jugarPartida(Mesa T, carta* c) {
	bool continuar = true;
	bool Pasar = false;
	bool conversor_out;
	char entrada;
	do {
		T.indiceRonda = 0;
		T.indiceMazo = 0;
		T.barajar(c);
		T.repartirCartas(T.Jugadores[0], c);
		T.modificaTablero();
		apuestaInicial();
		do {
			cout << "¿Desea Pasar (S/N)?" << endl;
			cin >> entrada;
			if (entrada == 'Y')
			{
				cout << "El oponente ha ganado" << endl;
				T.finRonda(T.Jugadores[1], T.Jugadores[0]);
			}

		} while (entrada != 'Y' && entrada != 'N');
	} while (continuar == true);


}

void verApuesta() {}

void subirApuesta(double qty) {}

void pasarApuesta() {}

void ronda(Mesa T, carta* c) {}

void apuestaInicial() {}

void continuar() {
cout<<"¿Desea continuar jugando?(Y/N)"
}