#include "Mesa.h"
#include <stdlib.h>
#include <iostream>
#include <array>
#include <string>
#include <time.h>
using namespace std;

Mesa::Mesa()
{
	Tablero = new carta[5];
	Quemada = new carta[3];
	indiceMazo = 0, indiceTablero = 0, indiceQuemada = 0, indiceRonda = 0;
	numeroJugadores = 2;
	apuesta = 0;
	
}
Mesa::~Mesa()
{
	delete[] Tablero;
	delete[] Quemada;
}
void Mesa::repartirCartas(jugador J, carta* Mazo)
{

	J.setMano(Mazo[indiceMazo], Mazo[indiceMazo + numeroJugadores]);
	indiceMazo++;
}

void Mesa::cartaTablero(carta* Mazo)
{
	if (indiceRonda == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			Tablero[indiceTablero] = Mazo[indiceMazo];
			indiceMazo++;
			indiceTablero++;
		}
	}
	else
	{
		Tablero[indiceTablero] = Mazo[indiceMazo];
		indiceMazo++;
		indiceTablero++;
	}
}

void Mesa::cartaQuemada(carta* Mazo)
{
	if(indiceRonda==1)
	{
		indiceMazo++;
		indiceMazo++; //valido unicamente para 2 jugadores
	}
	Quemada[indiceQuemada] = Mazo[indiceMazo];
	indiceMazo++;
	indiceQuemada++;
}

void Mesa::recogerApuesta(jugador j)
{
	apuesta = j.getApuesta();
	j.setApuesta(0);
}

void Mesa::entregarApuesta(jugador j)
{
	double dinero_act = j.getDinero();
	j.setDinero(dinero_act + apuesta);
	apuesta = 0;
}

bool Mesa::finRonda(jugador winner, jugador loser)
{
	bool salida=true;
	char entrada;
	recogerApuesta(winner);
	recogerApuesta(loser);
	entregarApuesta(winner);
	indiceMazo = 0;
	indiceQuemada = 0;
	indiceRonda = 0;
	indiceTablero = 0;
	cout << "¿Desea continuar jugando?(Y/N)" << endl;
	do {
		cin >> entrada;
		if (entrada == 'Y')
			salida = true;
		else if (entrada == 'N')
			salida = false;
		else
		{
			cout << "Error. Introduzca Y si quiere seguir jugando o N para finalizar"<<endl;
		}
	} while (entrada != 'Y' && entrada != 'N');

	return salida;
}

carta* Mesa::crearMazo()
{
	carta mazo[52];

	srand(time(NULL));
	int p = 1;
	int n = 1;

	for (int i = 0; i < 52; i++)
	{
		mazo[i].setPalo(p);
		mazo[i].setNumero(n);
		n++;
		if (n == 14)
		{
			p++;
			n = 1;
		}

	}
	return mazo;
}

carta* Mesa::barajar(carta* mazo)
{
	srand(NULL);

	int N = 52;
	for (int i = N - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		std::swap(mazo[i], mazo[r]);
	}
	return mazo;
}

void Mesa::creaTablero()
{
	//mano del oponente
	tablero_juego[1][8] = '['; 
	tablero_juego[1][11] = ']';
	tablero_juego[1][12] = '[';
	tablero_juego[1][15] = ']';


	//tu mano
	tablero_juego[9][8] = '[';
	tablero_juego[9][11] = ']';
	tablero_juego[9][12] = '[';
	tablero_juego[9][15] = ']';

	//mesa de juego
	tablero_juego[4][2] = '[';
	tablero_juego[4][5] = ']';
	tablero_juego[4][6] = '[';
	tablero_juego[4][9] = ']';
	tablero_juego[4][10] = '[';
	tablero_juego[4][13] = ']';
	tablero_juego[4][14] = '[';
	tablero_juego[4][17] = ']';
	tablero_juego[4][18] = '[';
	tablero_juego[4][21] = ']';

	//quemadas
	tablero_juego[6][6] = '[';
	tablero_juego[6][9] = ']';
	tablero_juego[6][10] = '[';
	tablero_juego[6][13] = ']';
	tablero_juego[6][14] = '[';
	tablero_juego[6][17] = ']';

}

void Mesa::modificaTablero()
{
	carta* mano_aux = new carta[2];
	carta* mano_aux2 = new carta[2];
	mano_aux=Jugadores[0].getMano();
	mano_aux2 = Jugadores[1].getMano();
	
	if (indiceRonda == 0)
	{
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
		tablero_juego[4][15] = conversorNumero(Tablero[3]);
		tablero_juego[4][16] = conversorPalo(Tablero[3]);
	}
	else if (indiceRonda == 3)
	{
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
	}

}

void Mesa::imprimirTablero()
{
	system("cls");

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			cout << tablero_juego[i][j];
		}
		cout << endl;
	}
	cout << "Apuesta actual jugador:" << Jugadores[0].getApuesta() << endl;
	cout << "Apuesta actual oponente:" << Jugadores[1].getApuesta() << endl;
	cout << "Dinero actual en juego:" << Jugadores[0].getApuesta() + Jugadores[1].getApuesta() << endl;


}


char Mesa::conversorNumero(carta c) 
{
	char salida;
	if (c.getNumero() == 1)
	{
		salida = 'A';
	}
	else if (c.getNumero() == 11)
	{
		salida = 'J';
	}
	else if (c.getNumero() == 12)
	{
		salida = 'Q';
	}
	else if (c.getNumero() == 13)
	{
		salida = 'K';
	}
	else
	{
		salida = (char)c.getNumero();
	}
	return salida;
}

char Mesa::conversorPalo(carta c)
{
	char salida=0;

	switch (c.getPalo())
	{
	case 1:
		salida = 'T';
		break;
	case 2:
		salida = 'P';
		break;
	case 3:
		salida = 'D';
		break;
	case 4:
		salida = 'C';
		break;
	}

	return salida;
}



