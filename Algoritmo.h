#pragma once
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"

class Algoritmo
{
public:
	int tipo = 0;
	float triple[3] = { 0,0,0 };
	bool pasa = false;
	int accion = 0;
	int obtenerAccion(Jugador J, Mesa M);//Randomizar probabilidad y obtener la accion sin haber acciones previas
	int obtenerAccionSegundo(Jugador J, Mesa M, int accionprevia);//Randomizar probabilidad y obtener la accion habiendo acciones previas siendo la primera accion del algoritmo de la ronda
	int  obtenerAccionAct(Jugador J, Mesa M, int accionprevia); //Obtener la accion habiendo acciones previas sin ser la primera accion de la ronda
	void obtenerTriple(Jugador J, Mesa M); //Lectura del algoritmo en R sin acciones previas
	void obtenerTripleAccion(Jugador J, Mesa M, int accionprevia);
	void obtenerTripleAct(Jugador J, Mesa M,int accionprevia);
	void reseteo();//Reseteo de fin de ronda
	void pasar(int ronda);//Funcion para enviar que el oponente ha pasado al algoritmo
	int obtenerSubida(float apuesta,float apuesta_ini);


};