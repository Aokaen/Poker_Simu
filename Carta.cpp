#include "Carta.h"

#include <iostream>
#include <string>

using namespace std;

Carta::Carta()
{
}

Carta::~Carta()
{
}

// Numero de carta

int Carta::getNumero()
{
    return numero;
}

void Carta::setNumero(int N)
{
	numero = N;
}

// Palo de carta

int Carta::getPalo()
{
    return palo;
}

void Carta::setPalo(int P)
{
	palo = P;
}

//Funcion para imprimir el valor y el palo de una carta

void Carta::imprimirCarta()
{
    string numero_escrito;

    switch (numero)
    {
        case 1:
            numero_escrito = "As";
            break;
        case 11:
            numero_escrito = "Jota";
            break;
        case 12:
            numero_escrito = "Reina";
            break;
        case 13:
            numero_escrito = "Rey";
            break;
        case 14:
            numero_escrito = "As";
            break;
    }
    
	string palo_escrito;
    
    switch (palo)
    {
        case 1:
            palo_escrito = "Treboles";
            break;
        case 2:
            palo_escrito = "Picas";
            break;
        case 3:
            palo_escrito = "Diamantes";
            break;
        case 4:
            palo_escrito = "Corazones";
            break;
    }

	cout << "La carta es " << numero_escrito << " de " << palo_escrito << "." << endl;
}

