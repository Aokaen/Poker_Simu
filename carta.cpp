#include "carta.h"
#include <iostream>
#include <string>
using namespace std;

carta::carta()
{
}

carta::~carta()
{
}

void carta::setNumero(int N)
{
	numero = N;
}

void carta::setPalo(int P)
{
	palo = P;
}

int carta::getNumero()
{
	return numero;
}

int carta::getPalo()
{
	return palo;
}

void carta::imprimeCarta()
{
	string Palo_escrito;
	string Numero_escrito;
	if (palo == 1)
		Palo_escrito = "Treboles";
	else if (palo == 2)
		Palo_escrito = "Picas";
	else if (palo == 3)
		Palo_escrito = "Diamantes";
	else if (palo == 4)
		Palo_escrito = "Corazones";
	if (numero == 1)
		Numero_escrito = "As";
	else if (numero == 11)
		Numero_escrito = "Jota";
	else if (numero == 12)
		Numero_escrito == "Reina";
	else if (numero == 13)
		Numero_escrito == "Rey";
	else
	{
		Numero_escrito = "" + numero;
	}


	cout << "La carta es " << Numero_escrito << " de " << Palo_escrito<< "." << "/n";
}
