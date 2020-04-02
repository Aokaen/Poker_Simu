#include "Algoritmo.h"
#include <math.h>
#include <cstdlib>
#include "random.h"

int Algoritmo::obtenerAccion()
{

	random r;
	float p = 0, v = 0, s = 0, n = 0;
	n = r.nrandomPorcent();
	//n = rand()%(100+1)*0.01;
	p = triple[0];
	v = p + triple[1];
	if (triple[2] != 0)
	{
		s =1;
	}
	else
	{
		s = 0;
	}
	if (n <= p)
	{
		return 0;
	}
	else if (n <= v)
	{
		return 1;
	}
	else
	{
		return 2;
	}


}
void Algoritmo::obtenerTriple(Jugador* J, Mesa M)
{
	//Codigo temporal hasta arreglar el tunel
	random r;
	float n = r.nrandomPorcent();
	//float r = rand()%(100+1) * 0.01;
	triple[0] = n * 0.5;
	triple[1] = n * 0.5;
	triple[2] = 1 - (triple[1] + triple[2]);


}
void Algoritmo::reseteo()
{}

char Algoritmo::conversorAccion()
{
	switch (accion)
	{
	case 0:
		return 'P';
	case 1:
		return 'V';
	case 2: 
		return 'S';
	default:
		break;
	}
}