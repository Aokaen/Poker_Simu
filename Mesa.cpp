#include "Mesa.h"

#include <stdlib.h>
#include <iostream>
#include <array>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
#include "Mazo.h"
using namespace std;

Mesa::Mesa()
{

}

Mesa::~Mesa()
{

}

// FUNCIONES DE INDICES

// IndiceRonda

void Mesa::resetIndiceRonda()
{
	indiceRonda = 0;
}

void Mesa::upIndiceRonda()
{
	indiceRonda++;
}

int Mesa::getIndiceRonda()
{
	return indiceRonda;
}

// IndiceTablero

void Mesa::resetIndiceTablero()
{
	indiceTablero = 0;
}

void Mesa::upIndiceTablero()
{
	indiceTablero++;
}

int Mesa::getIndiceTablero()
{
	return indiceTablero;
}

// IndiceQuemada

void Mesa::resetIndiceQuemada()
{
	indiceQuemada = 0;
}

void Mesa::upIndiceQuemada()
{
	indiceQuemada++;
}

int Mesa::getIndiceQuemada()
{
	return indiceQuemada;
}


// Funciones de representacion gráfica del tablero

void Mesa::creaTablero()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			tablero_juego[i][j] = ' ';
		}
	}
}

void Mesa::modificaTablero(Jugador* Jugadores)
{
	Carta* mano_aux = new Carta[2];
	Carta* mano_aux2 = new Carta[2];
	mano_aux = Jugadores[0].getMano();
	mano_aux2 = Jugadores[1].getMano();

	if (indiceRonda == 0)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				tablero_juego[i][j] = ' ';
			}

		}
		tablero_juego[9][9] = conversorNumero(mano_aux[0]);
		tablero_juego[9][10] = conversorPalo(mano_aux[0]);
		tablero_juego[9][13] = conversorNumero(mano_aux[1]);
		tablero_juego[9][14] = conversorPalo(mano_aux[1]);
	}
	else if (indiceRonda == 1)
	{
		tablero_juego[4][3] = conversorNumero(Tablero[0]);
		tablero_juego[4][4] = conversorPalo(Tablero[0]);
		tablero_juego[4][7] = conversorNumero(Tablero[1]);
		tablero_juego[4][8] = conversorPalo(Tablero[1]);
		tablero_juego[4][11] = conversorNumero(Tablero[2]);
		tablero_juego[4][12] = conversorPalo(Tablero[2]);
	}
	else if (indiceRonda == 2)
	{
		tablero_juego[4][3] = conversorNumero(Tablero[0]);
		tablero_juego[4][4] = conversorPalo(Tablero[0]);
		tablero_juego[4][7] = conversorNumero(Tablero[1]);
		tablero_juego[4][8] = conversorPalo(Tablero[1]);
		tablero_juego[4][11] = conversorNumero(Tablero[2]);
		tablero_juego[4][12] = conversorPalo(Tablero[2]);
		tablero_juego[4][15] = conversorNumero(Tablero[3]);
		tablero_juego[4][16] = conversorPalo(Tablero[3]);
	}
	else if (indiceRonda == 3)
	{
		tablero_juego[4][3] = conversorNumero(Tablero[0]);
		tablero_juego[4][4] = conversorPalo(Tablero[0]);
		tablero_juego[4][7] = conversorNumero(Tablero[1]);
		tablero_juego[4][8] = conversorPalo(Tablero[1]);
		tablero_juego[4][11] = conversorNumero(Tablero[2]);
		tablero_juego[4][12] = conversorPalo(Tablero[2]);
		tablero_juego[4][15] = conversorNumero(Tablero[3]);
		tablero_juego[4][16] = conversorPalo(Tablero[3]);
		tablero_juego[4][19] = conversorNumero(Tablero[4]);
		tablero_juego[4][20] = conversorPalo(Tablero[4]);
	}
	else if (indiceRonda == 4)
	{
		tablero_juego[1][9] = conversorNumero(mano_aux2[0]);
		tablero_juego[1][10] = conversorPalo(mano_aux2[0]);
		tablero_juego[1][13] = conversorNumero(mano_aux2[1]);
		tablero_juego[1][14] = conversorPalo(mano_aux2[1]);

		tablero_juego[6][7] = conversorNumero(Quemada[0]);
		tablero_juego[6][8] = conversorPalo(Quemada[0]);
		tablero_juego[6][11] = conversorNumero(Quemada[1]);
		tablero_juego[6][12] = conversorPalo(Quemada[1]);
		tablero_juego[6][15] = conversorNumero(Quemada[2]);
		tablero_juego[6][16] = conversorPalo(Quemada[2]);

		tablero_juego[4][3] = conversorNumero(Tablero[0]);
		tablero_juego[4][4] = conversorPalo(Tablero[0]);
		tablero_juego[4][7] = conversorNumero(Tablero[1]);
		tablero_juego[4][8] = conversorPalo(Tablero[1]);
		tablero_juego[4][11] = conversorNumero(Tablero[2]);
		tablero_juego[4][12] = conversorPalo(Tablero[2]);
		tablero_juego[4][15] = conversorNumero(Tablero[3]);
		tablero_juego[4][16] = conversorPalo(Tablero[3]);
		tablero_juego[4][19] = conversorNumero(Tablero[4]);
		tablero_juego[4][20] = conversorPalo(Tablero[4]);
	}


}

void Mesa::imprimirTablero(Jugador* Jugadores)
{
	system("cls");
	cout << "RONDA" << getIndiceRonda() << endl;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			cout << tablero_juego[i][j];
		}
		cout << endl;
	}

	cout << "Apuesta actual jugador:" << Jugadores[0].getApuesta() << endl;
	if (Jugadores[0].getDinero() == 0)
	{
		cout << "JUGADOR HA HECHO ALL IN" << endl;
	}
	cout << "Apuesta actual oponente:" << Jugadores[1].getApuesta() << endl;
	if (Jugadores[1].getDinero() == 0)
	{
		cout << "OPONENTE HA HECHO ALL IN" << endl;
	}
	cout << "Apuesta total: " << apuesta << endl;
}

// Funciones correspondientes al de fin de ronda y si seguir la partida

void Mesa::entregarApuesta(Jugador j)
{
	float dinero_act = j.getDinero();
	j.setDinero(dinero_act + apuesta);
	apuesta = 0;
}

void Mesa::finRonda(Mazo m)
{
	apuesta = 0;
	m.resetIndiceMazo();
	resetIndiceQuemada();
	resetIndiceRonda();
	resetIndiceTablero();
}

bool Mesa::continuar()
{
	char entrada;
	bool salida = false;

	cout << "Desea continuar jugando?(Y/N)" << endl;
	do {
		cin >> entrada;
		if (entrada == 'Y')
			salida = true;
		else if (entrada == 'N')
			salida = false;
		else
		{
			cout << "Error. Introduzca Y si quiere seguir jugando o N para finalizar" << endl;
		}
	} while ((entrada != 'Y') && (entrada != 'N'));

	return salida;
}

// Funciones de modificacion del valor Apuesta

void Mesa::actualizarApuesta(Jugador* Jugadores)
{ 
	float apuestaTotal = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
	apuesta = apuestaTotal;

}

void Mesa::CalculaApuestaTotal(Jugador* J)
{
	float total = 0;
	total = J[0].getApuesta() + J[1].getApuesta();
	apuesta = total;
}

// Conversiones del int de Numero y Palo al correspondiente Char

char Mesa::conversorNumero(Carta c)
{
	int numero = c.getNumero();

	switch (numero) {
	case 1:
		return 'A';
	case 10:
		return 'T';
	case 11:
		return 'J';
	case 12:
		return 'Q';
	case 13:
		return 'K';
	case 14:
		return 'A';
	default:
		return numero + '0';
	}
}

char Mesa::conversorPalo(Carta c)
{
	int palo = c.getPalo();

	switch (palo) {
	case 1:
		return 'T';
	case 2:
		return 'P';
	case 3:
		return 'D';
	case 4:
		return 'C';
	default:
		return '-';
	}
}