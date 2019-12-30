#include "Mesa.h"
#include <stdlib.h>
#include <iostream>
#include <array>
#include <string>
#include <time.h>
using namespace std;

Mesa::Mesa()
{
	
}
Mesa::~Mesa()
{

}
void Mesa::repartirCartas(jugador* J, carta* Mazo, carta* tablero, carta* Quemada)
{
	int aux = 0;
	aux = getIndiceMazo();
	for (int i = 0; i < 2; i++) //cambiar el valor de i<2 cuando se añadan mas jugadores
	{
		J[i].setMano(Mazo[aux], Mazo[aux + 1]);
		aux = aux + 2;
	}
	Quemada[0] = Mazo[aux];
	aux++;
	for (int i = 0; i < 3; i++)
	{
		tablero[i] = Mazo[aux];
		aux++;
	}
	Quemada[1] = Mazo[aux];
	aux++;
	tablero[3] = Mazo[aux];
	aux++;
	Quemada[2] = Mazo[aux];
	aux++;
	tablero[4] = Mazo[aux];

}

void Mesa::cartaTablero(carta* Mazo)
{
	int auxRonda = 0, auxTablero = 0, auxMazo = 0;
	auxRonda = getIndiceRonda();
	auxTablero = getIndiceTablero();
	auxMazo = getIndiceMazo();
	if (auxRonda == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			Tablero[auxTablero] = Mazo[auxMazo];
			auxMazo++;
			upIndiceMazo();
			auxTablero++;
			upIndiceTablero();
		}
	}
	else
	{
		Tablero[auxTablero] = Mazo[auxMazo];
		upIndiceMazo();
		upIndiceTablero();
	}
}

void Mesa::cartaQuemada(carta* Mazo)
{
	int auxRonda = 0, auxQuemada = 0, auxMazo = 0;
	auxRonda = getIndiceRonda();
	auxQuemada = getIndiceQuemada();
	auxMazo = getIndiceMazo();

	if(auxRonda==1)
	{
		upIndiceMazo();
		upIndiceMazo();
		//valido unicamente para 2 jugadores
	}
	Quemada[auxQuemada] = Mazo[auxMazo];
	upIndiceMazo(); 
	upIndiceQuemada();
}
//void Mesa::setapuesta(float f)
//{
//	apuesta = f;
//	cout << "Apuesta total: " << apuesta << endl;
//}
//
//void Mesa::resetapuesta()
//{
//	apuesta = 0;
//}
//float Mesa::getapuesta()
//{
//	return apuesta;
//}
//void Mesa::recogerApuesta(jugador j)
//{
//	float Apuesta = j.getApuesta();
//	setapuesta(Apuesta);
//	j.resetApuesta();
//}

void Mesa::entregarApuesta(jugador j)
{
	float dinero_act = j.getDinero(); // auxApuesta = getapuesta();
	j.setDinero(dinero_act + apuesta);
	apuesta = 0;
}

void Mesa::finRonda(jugador winner, jugador loser)
{
	
	//float total = winner.getDinero() + apuesta;
	//float actual = winner.getDinero();
	//winner.dinero = actual + total;
	//winner.resetApuesta();
	//loser.resetApuesta();
	apuesta = 0;//resetapuesta();
	resetIndiceMazo();
	resetIndiceQuemada();
	resetIndiceRonda();
	resetIndiceTablero();
	

	
}

bool Mesa::continuar()
{
	char entrada;
	bool salida;


	cout << "¿Desea continuar jugando?(Y/N)" << endl;
	do {
		cin >> entrada;
		if (entrada == 'Y' || entrada == 'y')
			salida = true;
		else if (entrada == 'N' || entrada == 'n')
			salida = false;
		else
		{
			cout << "Error. Introduzca Y si quiere seguir jugando o N para finalizar" << endl;
		}
	} while ((entrada == 'Y' || entrada == 'y') && (entrada == 'N' || entrada == 'n'));

	return salida;
}

carta* Mesa::crearMazo()
{
	static carta mazo[52];

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
	srand(NULL); //sustituir por semirandom

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

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			tablero_juego[i][j] = ' ';
		}

	}
	//mano del oponente
	tablero_juego[1][8] = '|';
	tablero_juego[1][11] = '|';
	tablero_juego[1][12] = '|';
	tablero_juego[1][15] = '|';


	//tu mano
	tablero_juego[9][8] = '|';
	tablero_juego[9][11] = '|';
	tablero_juego[9][12] = '|';
	tablero_juego[9][15] = '|';

	//mesa de juego
	tablero_juego[4][2] = '|';
	tablero_juego[4][5] = '|';
	tablero_juego[4][6] = '|';
	tablero_juego[4][9] = '|';
	tablero_juego[4][10] = '|';
	tablero_juego[4][13] = '|';
	tablero_juego[4][14] = '|';
	tablero_juego[4][17] = '|';
	tablero_juego[4][18] = '|';
	tablero_juego[4][21] = '|';

	//quemadas
	tablero_juego[6][6] = '|';
	tablero_juego[6][9] = '|';
	tablero_juego[6][10] = '|';
	tablero_juego[6][13] = '|';
	tablero_juego[6][14] = '|';
	tablero_juego[6][17] = '|';
}

void Mesa::modificaTablero(jugador* Jugadores)
{
	carta* mano_aux = new carta[2];
	carta* mano_aux2 = new carta[2];
	mano_aux=Jugadores[0].getMano();
	mano_aux2 = Jugadores[1].getMano();
	
	if (indiceRonda == 0)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				tablero_juego[i][j]=' ';
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
    
    if (indiceRonda != 0 && indiceRonda != 4)
    {
        float apuesta = Jugadores[1].getApuesta();
        apuesta = apuesta + 50;
        Jugadores[1].setApuesta(apuesta);
    }
    
    float apuestaTotal = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
    //setapuesta(apuestaTotal);
	apuesta = apuestaTotal;
}

void Mesa::imprimirTablero(jugador* Jugadores)
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
	cout << "Apuesta actual oponente:" << Jugadores[1].getApuesta() << endl;
	cout << "Dinero actual en juego:" << Jugadores[0].getApuesta() + Jugadores[1].getApuesta() << endl;
	cout << "Apuesta total: " << apuesta << endl;
}

void Mesa::CalculaApuestaTotal(jugador* J)
{
	float total = 0;
	total = J[0].getApuesta() + J[1].getApuesta();
	//setapuesta(total);
	apuesta = total;
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
	else if (c.getNumero() == 10)
	{ 
		salida = 'X';
	}
	else
	{
		salida = c.getNumero()+'0';
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
void Mesa::resetIndiceMazo()
{
	indiceMazo = 0;
}
void Mesa::upIndiceMazo()
{
	indiceMazo++;
}
int Mesa::getIndiceMazo()
{
	return indiceMazo;
}
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

