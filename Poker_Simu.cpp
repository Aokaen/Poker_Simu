// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"
#include "Mazo.h"
#include "Algoritmo.h"
#include <cstdlib>
#include "random.h"
#include <fstream>
#include <curl/curl.h>
#include <ctime>
#include <datetimeapi.h>

#define NUM 2

using namespace std;

//void AllIn(Jugador j, float qty) {
//
//	// Funcion para determinar si el jugador puede apostar o no (ALL IN)
//
//	float dinero = j.getDinero();
//	float apuesta = j.getApuesta();
//	float diferencia = qty - apuesta;
//	if (dinero <= diferencia)
//	{
//		j.setAllIn(true);
//	}
//	else
//	{
//		j.setAllIn(false);
//	}
//}

Carta* ordenarMano(Carta* c) {
	
	// Funcion para ordenar la mano de mayor a menor, sustituyendo el valor 1 por 14 del AS
	Carta aux;
	for (int i = 0; i < 7; i++)
	{
		if (c[i].getNumero() == 1)
		{
			c[i].setNumero(14);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		int j = i + 1;
		for (j; j < 7; j++)
		{
			if (c[i].getNumero() < c[j].getNumero())
			{
				aux = c[i];
				c[i] = c[j];
				c[j] = aux;

			}
		}

	}
	return c;
}
float jugada(Mesa T, Jugador j) {

	// Funcion para calcular el valor de cada jugada del jugador j

	float valor_jugada = 0;
	valor_jugada = j.getValor();
	return valor_jugada;
}

int jugadorGana(Mesa T, Jugador* Jugadores) {

	// Funcion para determinar que jugador gana, o si se produce un empate

	float Jug = 0, opo = 0;
	Jug = jugada(T, Jugadores[0]);
	opo = jugada(T, Jugadores[1]);
	cout << "Valor jugada Jugador: " << Jug << endl;
	cout << "Valor jugada Oponente: " << opo << endl;
	if (Jug > opo)
		return 1;
	else if (Jug < opo)
		return 2;
	else
		return 0;
}

bool comprobarDinero(Jugador* J)
{
	// Comprueba si la apuesta se ha igualado o si un jugador ha hecho un All in
	if (J[0].getApuesta() == J[1].getApuesta())
	{
		return true;
	}
	else if (J[0].getDinero() == 0 || J[1].getDinero() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}


}


bool pasarApuesta(Mesa T, Jugador* Jugadores, Mazo c) {

	//Funcion que efectua la accion de "Pasar" la apuesta

	bool continuar;
	float money = 0;
	float apuesta = 0;
	cout << "El oponente ha ganado" << endl;
	apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
	money = apuesta + Jugadores[1].getDinero();
	Jugadores[1].setDinero(money);
	Jugadores[1].resetApuesta();
	Jugadores[0].resetApuesta();
	T.finRonda(c);
	cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
	cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
	continuar = T.continuar();
	return continuar;
}
void subirApuesta(float qty, Mesa T, Jugador* Jugadores) {
	// //Funcion que efectua la accion de "Subir" la apuesta del jugador
	
	Jugadores[0].setApuesta(qty);
	
}

void subirApuestaAlg(float qty, Mesa T, Jugador* Jugadores) {
	// //Funcion que efectua la accion de "Subir" la apuestadel algoritmo

	Jugadores[1].setApuesta(qty);

}
void verApuesta(Mesa T, Jugador* Jugadores) { 

	//Funcion que efectua la accion de "Ver" la apuesta del jugador

	if (Jugadores[0].getDinero()<= Jugadores[1].getApuesta())
	{
		cout << "ALL IN JUGADOR" << endl;
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(Jugadores[1].getApuesta());
	}
	
}

void verApuestaAlg(Mesa T, Jugador* Jugadores) { 

	//Funcion que efectua la accion de "Ver" la apuesta del jugador

	if (Jugadores[1].getDinero() <= Jugadores[0].getApuesta())
	{
		cout << "ALL IN ALGORITMO" << endl;
		Jugadores[1].setApuesta(Jugadores[1].getDinero());
	}
	else
	{
		Jugadores[1].setApuesta(Jugadores[0].getApuesta());
	}

}

bool apostar(Mesa T, Jugador* Jugadores, Algoritmo alg)
{
	// Función que gestiona la ronda de apuestas y el funcionamiento de las apuestas

	char entrada, entrada_apuesta;
	bool pasar=false;
	float entrada_cantidad;
	float total = 0;
	bool apuesta_ok = false;
	bool apuestaFin = false;
	bool checkposible = true;
	int accion = -1;
	float cantidad_alg = 0;
	int checking = 0;

	if (Jugadores[0].getDinero() == 0 || Jugadores[1].getDinero() == 0)
	{
		checkposible = false;
	}
	if (Jugadores[0].getApuesta() != Jugadores[1].getApuesta() )
	{
		checkposible = false;
	}
	do {

		
		if (checkposible == false) 
		{
			if (Jugadores[0].turno == 0)
			{
				//Acción del jugador
				if (Jugadores[0].getDinero() == 0)
				{
					cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
					cout << "Pulse cualquier tecla para continuar..." << endl;
					char inside;
					cin >> inside;
					apuestaFin = true;
					pasar = false;
				}
				else if (Jugadores[1].getDinero() == 0)
				{
					cout << "El Oponente ha hecho All in." << endl;
					float diferencia = 0;
					diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
					do {
						float help = Jugadores[0].getDinero();
						if (diferencia >= help)
						{
							cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
						}
						else
						{
							cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
						}
						cin >> entrada;

						if (entrada == 'V')
						{
							verApuesta(T, Jugadores);
							pasar = false;

						}
						else if (entrada == 'P')
						{
							pasar = true;
						}
						else
						{
							cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

						}
					} while (entrada != 'P' && entrada != 'V');
					apuestaFin = true;
				}
				else
				{
					do {

						cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
						cin >> entrada;
						if (entrada == 'P')
						{
							pasar = true;
							apuestaFin = true;
						}
						else if (entrada == 'A')
						{
							pasar = false;
							do {
								cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
								cin >> entrada_apuesta;
								if (entrada_apuesta == 'V')
								{
									verApuesta(T, Jugadores);
									apuestaFin = true;

								}
								else if (entrada_apuesta == 'S')
								{
									do {

										cout << "Introduzca la nueva apuesta:";
										cin >> entrada_cantidad;
										cout << endl;
										if (entrada_cantidad > Jugadores[1].getApuesta())
										{
											float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

											if (diferencia >= Jugadores[0].getDinero())
											{
												cout << "All In" << endl;
												float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
												subirApuesta(qty, T, Jugadores);
											}
											else
											{
												subirApuesta(entrada_cantidad, T, Jugadores);
											}

											apuesta_ok = true;
										}
										else
										{
											cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
										}

									} while (apuesta_ok == false);
									
								}

								else
								{
									cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
								}
							} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

						}
						else
						{
							cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
						}

					} while (entrada != 'P' && entrada != 'A');
				}

				if (T.getIndiceRonda() == 0 && Jugadores[0].getApuesta() != Jugadores[1].getApuesta())
				{//Accion del algoritmo
					alg.obtenerTriple(Jugadores, T);
					accion = alg.obtenerAccion();
					if (accion == 0)
					{
						cout << "Algoritmo Pasa" << endl;
						alg.pasa = true;
						apuestaFin = true;
					}
					else if (accion == 1)
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
					else if (accion == 2)
					{

						random r;
						int randn = r.nrandomPorcent();
						cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
						cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
						float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

						if (diferencia_alg >= Jugadores[1].getDinero())
						{
							cout << "All In Algoritmo" << endl;
							float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
							subirApuestaAlg(qty, T, Jugadores);
						}
						else
						{
							cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
							cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
							subirApuestaAlg(cantidad_alg, T, Jugadores);
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
						T.actualizarApuesta(Jugadores);
						cout << "Apuesta total: " << T.apuesta << endl;


					}
				}
			}
			else
			{
			//Accion del algoritmo
			alg.obtenerTriple(Jugadores, T);
			accion = alg.obtenerAccion();
			if (accion == 0)
			{
				cout << "Algoritmo Pasa" << endl;
				alg.pasa = true;
				apuestaFin = true;
			}
			else if (accion == 1)
			{
				cout << "Algoritmo Ve la apuesta" << endl;
				verApuestaAlg(T, Jugadores);
				apuestaFin = true;
			}
			else if (accion == 2)
			{

				random r;
				int randn = r.nrandomPorcent();
				cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
				cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
				float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

				if (diferencia_alg >= Jugadores[1].getDinero())
				{
					cout << "All In Algoritmo" << endl;
					float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
					subirApuestaAlg(qty, T, Jugadores);
				}
				else
				{
					cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
					cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
					subirApuestaAlg(cantidad_alg, T, Jugadores);
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
				T.actualizarApuesta(Jugadores);
				cout << "Apuesta total: " << T.apuesta << endl;

				//Acción del jugador
				if (Jugadores[0].getDinero() == 0)
				{
					cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
					cout << "Pulse cualquier tecla para continuar..." << endl;
					char inside;
					cin >> inside;
					apuestaFin = true;
					pasar = false;
				}
				else if (Jugadores[1].getDinero() == 0)
				{
					cout << "El Oponente ha hecho All in." << endl;
					float diferencia = 0;
					diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
					do {
						float help = Jugadores[0].getDinero();
						if (diferencia >= help)
						{
							cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
						}
						else
						{
							cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
						}
						cin >> entrada;

						if (entrada == 'V')
						{
							verApuesta(T, Jugadores);
							pasar = false;

						}
						else if (entrada == 'P')
						{
							pasar = true;
						}
						else
						{
							cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

						}
					} while (entrada != 'P' && entrada != 'V');
					apuestaFin = true;
				}
				else
				{
					do {

						cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
						cin >> entrada;
						if (entrada == 'P')
						{
							pasar = true;
							apuestaFin = true;
						}
						else if (entrada == 'A')
						{
							pasar = false;
							do {
								cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
								cin >> entrada_apuesta;
								if (entrada_apuesta == 'V')
								{
									verApuesta(T, Jugadores);
									apuestaFin = true;

								}
								else if (entrada_apuesta == 'S')
								{
									do {

										cout << "Introduzca la nueva apuesta:";
										cin >> entrada_cantidad;
										cout << endl;
										if (entrada_cantidad > Jugadores[1].getApuesta())
										{
											float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

											if (diferencia >= Jugadores[0].getDinero())
											{
												cout << "All In" << endl;
												float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
												subirApuesta(qty, T, Jugadores);
											}
											else
											{
												subirApuesta(entrada_cantidad, T, Jugadores);
											}

											apuesta_ok = true;
										}
										else
										{
											cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
										}

									} while (apuesta_ok == false);
									
								}

								else
								{
									cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
								}
							} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

						}
						else
						{
							cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
						}

					} while (entrada != 'P' && entrada != 'A');
				}

			}
			}
		}

		else
		{
			if (Jugadores[0].turno == 0)
			{
				//Acción del jugador
				cout << "¿Desea seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
				cin >> entrada;
				if (entrada == 'P')
				{
					pasar = true;
					apuestaFin = true;
				}
				else if (entrada == 'S')
				{
					checkposible = false;
					bool apuesta_subida = false;
					float entrada_subida = 0;
					do {

						cout << "Introduzca la nueva apuesta:";
						cin >> entrada_subida;
						cout << endl;
						if (entrada_subida > Jugadores[1].getApuesta())
						{
							float diferencia = entrada_subida - Jugadores[0].getApuesta();

							if (diferencia >= Jugadores[0].getDinero())
							{
								cout << "All In" << endl;
								float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
								subirApuesta(qty, T, Jugadores);
							}
							else
							{
								subirApuesta(entrada_subida, T, Jugadores);
							}

							apuesta_subida = true;
						}
						else
						{
							cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
						}

					} while (apuesta_subida == false);
				}
				else if (entrada == 'C')
				{
					if (checking == 0)
					{
						checking = 1;
					}
					else
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
				}
				//Accion del algoritmo

				alg.obtenerTriple(Jugadores, T);
				accion = alg.obtenerAccion();
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
				}
				else if (accion == 1)
				{
					if (checking == 1)
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
					else
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
				}
				else if (accion == 2)
				{
					checkposible = false;
					random r;
					int randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						subirApuestaAlg(qty, T, Jugadores);
					}
					else
					{
						cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
						cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
						subirApuestaAlg(cantidad_alg, T, Jugadores);
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
					T.actualizarApuesta(Jugadores);
					cout << "Apuesta total: " << T.apuesta << endl;
				}
			}
			else
			{
				//Accion del algoritmo

				alg.obtenerTriple(Jugadores, T);
				accion = alg.obtenerAccion();
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
				}
				else if (accion == 1)
				{
					if (checking == 1)
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
					else
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
				}
				else if (accion == 2)
				{
					checkposible = false;
					random r;
					int randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						subirApuestaAlg(qty, T, Jugadores);
					}
					else
					{
						cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
						cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
						subirApuestaAlg(cantidad_alg, T, Jugadores);
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
					T.actualizarApuesta(Jugadores);
					cout << "Apuesta total: " << T.apuesta << endl;
				}
				//Acción del jugador

				if (Jugadores[0].getApuesta() == Jugadores[1].getApuesta())
				{
					cout << "¿Desea Seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
					cin >> entrada;
					if (entrada == 'P')
					{
						pasar = true;
						apuestaFin = true;
					}
					else if (entrada == 'S')
					{
						checkposible = false;
						bool apuesta_subida = false;
						float entrada_subida = 0;
						do {

							cout << "Introduzca la nueva apuesta:";
							cin >> entrada_subida;
							cout << endl;
							if (entrada_subida > Jugadores[1].getApuesta())
							{
								float diferencia = entrada_subida - Jugadores[0].getApuesta();

								if (diferencia >= Jugadores[0].getDinero())
								{
									cout << "All In" << endl;
									float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
									subirApuesta(qty, T, Jugadores);
								}
								else
								{
									subirApuesta(entrada_subida, T, Jugadores);
								}

								apuesta_subida = true;
							}
							else
							{
								cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
							}

						} while (apuesta_subida == false);
					}
					else if (entrada == 'C')
					{
						if (checking == 0)
						{
							checking = 1;
						}
						else
						{
							checking = 0;
							apuestaFin = true;
							cout << "Ambos siguen la apuesta" << endl;
						}
					}
				}
				else
				{
					//Acción del jugador
					if (Jugadores[0].getDinero() == 0)
					{
						cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
						cout << "Pulse cualquier tecla para continuar..." << endl;
						char inside;
						cin >> inside;
						apuestaFin = true;
						pasar = false;
					}
					else if (Jugadores[1].getDinero() == 0)
					{
						cout << "El Oponente ha hecho All in." << endl;
						float diferencia = 0;
						diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
						do {
							float help = Jugadores[0].getDinero();
							if (diferencia >= help)
							{
								cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
							}
							else
							{
								cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
							}
							cin >> entrada;

							if (entrada == 'V')
							{
								verApuesta(T, Jugadores);
								pasar = false;

							}
							else if (entrada == 'P')
							{
								pasar = true;
							}
							else
							{
								cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

							}
						} while (entrada != 'P' && entrada != 'V');
						apuestaFin = true;
					}
					else
					{
						do {

							cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
							cin >> entrada;
							if (entrada == 'P')
							{
								pasar = true;
								apuestaFin = true;
							}
							else if (entrada == 'A')
							{
								pasar = false;
								do {
									cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
									cin >> entrada_apuesta;
									if (entrada_apuesta == 'V')
									{
										verApuesta(T, Jugadores);
										apuestaFin = true;

									}
									else if (entrada_apuesta == 'S')
									{
										do {

											cout << "Introduzca la nueva apuesta:";
											cin >> entrada_cantidad;
											cout << endl;
											if (entrada_cantidad > Jugadores[1].getApuesta())
											{
												float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

												if (diferencia >= Jugadores[0].getDinero())
												{
													cout << "All In" << endl;
													float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
													subirApuesta(qty, T, Jugadores);
												}
												else
												{
													subirApuesta(entrada_cantidad, T, Jugadores);
												}

												apuesta_ok = true;
											}
											else
											{
												cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
											}

										} while (apuesta_ok == false);

									}

									else
									{
										cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
									}
								} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

							}
							else
							{
								cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
							}

						} while (entrada != 'P' && entrada != 'A');
					}

				}
			}
		}

	} while (apuestaFin == false);
		
	return pasar;
}

void calcularValorjugador(Mesa T, Jugador* J, int Ronda)
	{
	// Funcion que ejecuta y actualiza el valor de la Mano en función de la ronda de juego
	if (Ronda == 0)
	{
		J[0].valorManoInicial();
		J[1].valorManoInicial();
	}
	else if (Ronda == 1)
	{
		J[0].valorManoR1(T);
		J[1].valorManoR1(T);
	}
	else if (Ronda == 2)
	{
		
		J[0].valorManoR2(T);
		J[1].valorManoR2(T);
	}
	else if (Ronda == 3)
	{
		J[0].valorManoR3(T);
		J[1].valorManoR3(T);
	}

}
bool ronda(Mesa T, Mazo c, Jugador* J,Algoritmo alg) {
	// Funcionamiento de cada Ronda, modifica el tablero y lanza la funcion apostar
	bool pasar = false;
	bool jugador_gana;
	int auxRonda = T.getIndiceRonda();
	int auxTablero = T.getIndiceTablero();
	T.modificaTablero(J);
	T.actualizarApuesta(J);
	T.imprimirTablero(J);
	calcularValorjugador(T,J,auxRonda);
	cout << "Dinero actual jugador: " << J[0].getDinero() << endl;
	cout << "Dinero actual oponente: " << J[1].getDinero() << endl;
	cout << "Valor Jugada: "<<J->getValor() << endl;

	pasar = apostar(T,J,alg);

	return pasar;

}
bool pasarApuestaAlg(Mesa T, Jugador* Jugadores, Mazo c, Algoritmo alg1, Algoritmo alg2, int n_actual, int n_total)
{

	//Funcion que efectua la accion de "Pasar" la apuesta en el modo Algoritmo

	bool continuar;
	float money = 0;
	float apuesta = 0;
	apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
	if (alg1.pasa == true)
	{
		money = apuesta + Jugadores[1].getDinero();
		Jugadores[1].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
	else if (alg2.pasa == true)
	{
		money = apuesta + Jugadores[0].getDinero();
		Jugadores[0].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
	T.finRonda(c);
	if (n_actual >= n_total)
	{
		continuar = false;
	}
	else
	{
		continuar = true;
	}
	return continuar;
}
bool apostarAlg(Mesa T, Jugador* Jugadores, Algoritmo alg1, Algoritmo alg2, string acciones)
{
	bool pasar = false;
	float total = 0;
	bool apuesta_ok = false;
	bool apuestaFin = false;
	bool checkposible = true;
	int accion = -1;
	float cantidad_alg = 0;
	int checking = 0;
	
	if (Jugadores[0].getDinero() == 0 || Jugadores[1].getDinero() == 0)
	{
		checkposible = false;
	}
	if (Jugadores[0].getApuesta() != Jugadores[1].getApuesta())
	{
		checkposible = false;
	}

	do {


		if (checkposible == false)
		{
			if (Jugadores[0].turno == 0)
			{ //EN EDICION
				//Acción del algoritmo
				if (Jugadores[0].getDinero() == 0)
				{
					apuestaFin = true;
					pasar = false;
					alg1.accion = 0;
				}
				else if (Jugadores[1].getDinero() == 0)
				{

					float diferencia = 0;
					diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
					do {
						float help = Jugadores[0].getDinero();
						if (diferencia >= help)
						{
							cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
						}
						else
						{
							cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
						}
						cin >> entrada;

						if (entrada == 'V')
						{
							verApuesta(T, Jugadores);
							pasar = false;

						}
						else if (entrada == 'P')
						{
							pasar = true;
						}
						else
						{
							cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

						}
					} while (entrada != 'P' && entrada != 'V');
					apuestaFin = true;
				}
				else
				{
					do {

						cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
						cin >> entrada;
						if (entrada == 'P')
						{
							pasar = true;
							apuestaFin = true;
						}
						else if (entrada == 'A')
						{
							pasar = false;
							do {
								cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
								cin >> entrada_apuesta;
								if (entrada_apuesta == 'V')
								{
									verApuesta(T, Jugadores);
									apuestaFin = true;

								}
								else if (entrada_apuesta == 'S')
								{
									do {

										cout << "Introduzca la nueva apuesta:";
										cin >> entrada_cantidad;
										cout << endl;
										if (entrada_cantidad > Jugadores[1].getApuesta())
										{
											float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

											if (diferencia >= Jugadores[0].getDinero())
											{
												cout << "All In" << endl;
												float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
												subirApuesta(qty, T, Jugadores);
											}
											else
											{
												subirApuesta(entrada_cantidad, T, Jugadores);
											}

											apuesta_ok = true;
										}
										else
										{
											cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
										}

									} while (apuesta_ok == false);

								}

								else
								{
									cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
								}
							} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

						}
						else
						{
							cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
						}

					} while (entrada != 'P' && entrada != 'A');
				}

				if (T.getIndiceRonda() == 0 && Jugadores[0].getApuesta() != Jugadores[1].getApuesta())
				{//Accion del algoritmo
					alg.obtenerTriple(Jugadores, T);
					accion = alg.obtenerAccion();
					if (accion == 0)
					{
						cout << "Algoritmo Pasa" << endl;
						alg.pasa = true;
						apuestaFin = true;
					}
					else if (accion == 1)
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
					else if (accion == 2)
					{

						random r;
						int randn = r.nrandomPorcent();
						cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
						cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
						float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

						if (diferencia_alg >= Jugadores[1].getDinero())
						{
							cout << "All In Algoritmo" << endl;
							float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
							subirApuestaAlg(qty, T, Jugadores);
						}
						else
						{
							cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
							cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
							subirApuestaAlg(cantidad_alg, T, Jugadores);
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
						T.actualizarApuesta(Jugadores);
						cout << "Apuesta total: " << T.apuesta << endl;


					}
				}
			}
			else
			{
				//Accion del algoritmo
				alg.obtenerTriple(Jugadores, T);
				accion = alg.obtenerAccion();
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
				}
				else if (accion == 1)
				{
					cout << "Algoritmo Ve la apuesta" << endl;
					verApuestaAlg(T, Jugadores);
					apuestaFin = true;
				}
				else if (accion == 2)
				{

					random r;
					int randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						subirApuestaAlg(qty, T, Jugadores);
					}
					else
					{
						cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
						cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
						subirApuestaAlg(cantidad_alg, T, Jugadores);
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
					T.actualizarApuesta(Jugadores);
					cout << "Apuesta total: " << T.apuesta << endl;

					//Acción del jugador
					if (Jugadores[0].getDinero() == 0)
					{
						cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
						cout << "Pulse cualquier tecla para continuar..." << endl;
						char inside;
						cin >> inside;
						apuestaFin = true;
						pasar = false;
					}
					else if (Jugadores[1].getDinero() == 0)
					{
						cout << "El Oponente ha hecho All in." << endl;
						float diferencia = 0;
						diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
						do {
							float help = Jugadores[0].getDinero();
							if (diferencia >= help)
							{
								cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
							}
							else
							{
								cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
							}
							cin >> entrada;

							if (entrada == 'V')
							{
								verApuesta(T, Jugadores);
								pasar = false;

							}
							else if (entrada == 'P')
							{
								pasar = true;
							}
							else
							{
								cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

							}
						} while (entrada != 'P' && entrada != 'V');
						apuestaFin = true;
					}
					else
					{
						do {

							cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
							cin >> entrada;
							if (entrada == 'P')
							{
								pasar = true;
								apuestaFin = true;
							}
							else if (entrada == 'A')
							{
								pasar = false;
								do {
									cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
									cin >> entrada_apuesta;
									if (entrada_apuesta == 'V')
									{
										verApuesta(T, Jugadores);
										apuestaFin = true;

									}
									else if (entrada_apuesta == 'S')
									{
										do {

											cout << "Introduzca la nueva apuesta:";
											cin >> entrada_cantidad;
											cout << endl;
											if (entrada_cantidad > Jugadores[1].getApuesta())
											{
												float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

												if (diferencia >= Jugadores[0].getDinero())
												{
													cout << "All In" << endl;
													float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
													subirApuesta(qty, T, Jugadores);
												}
												else
												{
													subirApuesta(entrada_cantidad, T, Jugadores);
												}

												apuesta_ok = true;
											}
											else
											{
												cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
											}

										} while (apuesta_ok == false);

									}

									else
									{
										cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
									}
								} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

							}
							else
							{
								cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
							}

						} while (entrada != 'P' && entrada != 'A');
					}

				}
			}
		}

		else
		{
			if (Jugadores[0].turno == 0)
			{
				//Acción del jugador
				cout << "¿Desea seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
				cin >> entrada;
				if (entrada == 'P')
				{
					pasar = true;
					apuestaFin = true;
				}
				else if (entrada == 'S')
				{
					checkposible = false;
					bool apuesta_subida = false;
					float entrada_subida = 0;
					do {

						cout << "Introduzca la nueva apuesta:";
						cin >> entrada_subida;
						cout << endl;
						if (entrada_subida > Jugadores[1].getApuesta())
						{
							float diferencia = entrada_subida - Jugadores[0].getApuesta();

							if (diferencia >= Jugadores[0].getDinero())
							{
								cout << "All In" << endl;
								float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
								subirApuesta(qty, T, Jugadores);
							}
							else
							{
								subirApuesta(entrada_subida, T, Jugadores);
							}

							apuesta_subida = true;
						}
						else
						{
							cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
						}

					} while (apuesta_subida == false);
				}
				else if (entrada == 'C')
				{
					if (checking == 0)
					{
						checking = 1;
					}
					else
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
				}
				//Accion del algoritmo

				alg.obtenerTriple(Jugadores, T);
				accion = alg.obtenerAccion();
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
				}
				else if (accion == 1)
				{
					if (checking == 1)
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
					else
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
				}
				else if (accion == 2)
				{
					checkposible = false;
					random r;
					int randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						subirApuestaAlg(qty, T, Jugadores);
					}
					else
					{
						cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
						cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
						subirApuestaAlg(cantidad_alg, T, Jugadores);
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
					T.actualizarApuesta(Jugadores);
					cout << "Apuesta total: " << T.apuesta << endl;
				}
			}
			else
			{
				//Accion del algoritmo

				alg.obtenerTriple(Jugadores, T);
				accion = alg.obtenerAccion();
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
				}
				else if (accion == 1)
				{
					if (checking == 1)
					{
						checking = 0;
						apuestaFin = true;
						cout << "Ambos siguen la apuesta" << endl;
					}
					else
					{
						cout << "Algoritmo Ve la apuesta" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
				}
				else if (accion == 2)
				{
					checkposible = false;
					random r;
					int randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						subirApuestaAlg(qty, T, Jugadores);
					}
					else
					{
						cout << "Algoritmo Sube la Apuesta en: " << cantidad_alg << endl;
						cantidad_alg = cantidad_alg + Jugadores[1].getApuesta();
						subirApuestaAlg(cantidad_alg, T, Jugadores);
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
					T.actualizarApuesta(Jugadores);
					cout << "Apuesta total: " << T.apuesta << endl;
				}
				//Acción del jugador

				if (Jugadores[0].getApuesta() == Jugadores[1].getApuesta())
				{
					cout << "¿Desea Seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
					cin >> entrada;
					if (entrada == 'P')
					{
						pasar = true;
						apuestaFin = true;
					}
					else if (entrada == 'S')
					{
						checkposible = false;
						bool apuesta_subida = false;
						float entrada_subida = 0;
						do {

							cout << "Introduzca la nueva apuesta:";
							cin >> entrada_subida;
							cout << endl;
							if (entrada_subida > Jugadores[1].getApuesta())
							{
								float diferencia = entrada_subida - Jugadores[0].getApuesta();

								if (diferencia >= Jugadores[0].getDinero())
								{
									cout << "All In" << endl;
									float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
									subirApuesta(qty, T, Jugadores);
								}
								else
								{
									subirApuesta(entrada_subida, T, Jugadores);
								}

								apuesta_subida = true;
							}
							else
							{
								cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
							}

						} while (apuesta_subida == false);
					}
					else if (entrada == 'C')
					{
						if (checking == 0)
						{
							checking = 1;
						}
						else
						{
							checking = 0;
							apuestaFin = true;
							cout << "Ambos siguen la apuesta" << endl;
						}
					}
				}
				else
				{
					//Acción del jugador
					if (Jugadores[0].getDinero() == 0)
					{
						cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
						cout << "Pulse cualquier tecla para continuar..." << endl;
						char inside;
						cin >> inside;
						apuestaFin = true;
						pasar = false;
					}
					else if (Jugadores[1].getDinero() == 0)
					{
						cout << "El Oponente ha hecho All in." << endl;
						float diferencia = 0;
						diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
						do {
							float help = Jugadores[0].getDinero();
							if (diferencia >= help)
							{
								cout << "¿Desea Ver el All in del oponente haciendo un All in (V) o Pasar (P)?" << endl;
							}
							else
							{
								cout << "¿Desea Ver el All in del oponente (V) o Pasar (P)?" << endl;
							}
							cin >> entrada;

							if (entrada == 'V')
							{
								verApuesta(T, Jugadores);
								pasar = false;

							}
							else if (entrada == 'P')
							{
								pasar = true;
							}
							else
							{
								cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

							}
						} while (entrada != 'P' && entrada != 'V');
						apuestaFin = true;
					}
					else
					{
						do {

							cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
							cin >> entrada;
							if (entrada == 'P')
							{
								pasar = true;
								apuestaFin = true;
							}
							else if (entrada == 'A')
							{
								pasar = false;
								do {
									cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
									cin >> entrada_apuesta;
									if (entrada_apuesta == 'V')
									{
										verApuesta(T, Jugadores);
										apuestaFin = true;

									}
									else if (entrada_apuesta == 'S')
									{
										do {

											cout << "Introduzca la nueva apuesta:";
											cin >> entrada_cantidad;
											cout << endl;
											if (entrada_cantidad > Jugadores[1].getApuesta())
											{
												float diferencia = entrada_cantidad - Jugadores[0].getApuesta();

												if (diferencia >= Jugadores[0].getDinero())
												{
													cout << "All In" << endl;
													float qty = Jugadores[0].getApuesta() + Jugadores[0].getDinero();
													subirApuesta(qty, T, Jugadores);
												}
												else
												{
													subirApuesta(entrada_cantidad, T, Jugadores);
												}

												apuesta_ok = true;
											}
											else
											{
												cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
											}

										} while (apuesta_ok == false);

									}

									else
									{
										cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
									}
								} while (entrada_apuesta != 'S' && entrada_apuesta != 'V');

							}
							else
							{
								cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
							}

						} while (entrada != 'P' && entrada != 'A');
					}

				}
			}
		}

	} while (apuestaFin == false);

	return pasar;
}
bool rondaAlg(Mesa T, Mazo c, Jugador* J, Algoritmo alg1, Algoritmo alg2, string acciones)
{
	// Funcionamiento de cada Ronda para el modo Algoritmo y lanza la funcion apostar del modo Algoritmo
	bool pasar = false;
	bool jugador_gana;
	int auxRonda = T.getIndiceRonda();
	int auxTablero = T.getIndiceTablero();
	T.actualizarApuesta(J);
	calcularValorjugador(T, J, auxRonda);
	pasar = apostarAlg(T, J, alg1, alg2, acciones);

	return pasar;

}

void jugarPartida(Mesa T, Mazo c, Jugador* Jugadores, bool jugador, int elegido, Algoritmo alg, float apuestaInicial) {
	// Funcion que controla el flujo de las rondas de juego

	bool continuar = true;
	bool pasar = false;
	int jugador_gana=-1; //1 jugador gana, 2 oponente gana, 0 empate
	char entrada;
	float money = 0;
	float apuestainicialjugador0 = Jugadores[0].getApuestaInicial();
	float apuestainicialjugador1 = Jugadores[1].getApuestaInicial();
	bool primeraPartida = true;
	int aux = -1;
	float apuestaaux = 0;
	alg.tipo = 4;
	if (jugador == true)
	{
		do {
			T.resetIndiceRonda();
			c.resetIndiceMazo();
			c.barajar();
			int auxRonda = T.getIndiceRonda();

			if (primeraPartida == false)
			{
				aux = Jugadores[0].turno;
				Jugadores[0].turno = Jugadores[1].turno;
				Jugadores[1].turno = aux;

				apuestaaux = apuestainicialjugador0;
				apuestainicialjugador0 = apuestainicialjugador1;
				apuestainicialjugador1 = apuestaaux;
			}

			Jugadores[0].setApuesta(apuestainicialjugador0);
			Jugadores[1].setApuesta(apuestainicialjugador1);
			c.repartirCartas(T, Jugadores);
			

			T.modificaTablero(Jugadores);
			T.actualizarApuesta(Jugadores);
			pasar = ronda(T, c, Jugadores, alg); // Preflop 
			do {
				
				if (pasar == true)
					continuar = pasarApuesta(T, Jugadores,c);
				else {
					T.upIndiceRonda();
					auxRonda++;
					if (T.getIndiceRonda() == 4)
					{

						T.modificaTablero(Jugadores);
						T.actualizarApuesta(Jugadores);
						T.imprimirTablero(Jugadores);

						cout << "Show-down" << endl;
						jugador_gana = jugadorGana(T, Jugadores);
						if (jugador_gana == 1)
						{
							cout << "Jugador Gana" << endl;
							money = T.apuesta + Jugadores[0].getDinero();
							Jugadores[0].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if(Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						else if (jugador_gana == 2)
						{
							cout << "Oponente Gana" << endl;
							money = T.apuesta + Jugadores[1].getDinero();
							Jugadores[1].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if (Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						else if (jugador_gana == 0)
						{
							float money_jug = 0, money_opo = 0;
							cout << "EMPATE" << endl;
							money = T.apuesta / 2;
							money_jug = money + Jugadores[0].getDinero();
							money_opo = money + Jugadores[1].getDinero();
							Jugadores[0].setDinero(money_jug);
							Jugadores[1].setDinero(money_opo);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if (Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						
					}
					else {
						{

						}
						pasar = ronda(T, c, Jugadores,alg); //Flop, turn y river
						if (pasar == true)
						{
							continuar = pasarApuesta(T, Jugadores,c);
						}

					}
				}
				
			} while (pasar == false && auxRonda < 4);

			if (continuar == true)
			{
				system("cls");
			} 

			if (continuar == false)
			{
				if (Jugadores[0].getDinero() > 0 && Jugadores[1].getDinero() > 0)
				{
					continuar == true;
				}
			}

			primeraPartida = false;
		} while (continuar == true);

		cout << "Fin de la partida" << endl;
		if (Jugadores[0].getDinero() == 0)
		{
			cout << "El jugador ha perdido" << endl;
		}
		else if (Jugadores[1].getDinero() == 0)
		{
			cout << "El oponente ha perdido" << endl;
		}
	}
	else
	{
	Algoritmo algOpo; //Jugador[1]
	algOpo.tipo = elegido;
	fstream registro("log.txt");
	int n = 0;
	string acciones;
	int n_veces=0;
	cout << "Introducir el numero de iteracciones deseadas:";
	cin >> n_veces;
	cout << endl;
	Carta* manoAux = new Carta[2];
	Carta* mesaAux = new Carta[5];
	if (!registro.is_open())
	{
		registro.open("log.txt", ios::out);
	}
	char formato[30];
	int status;

		do {
			n = n + 1;
			system("cls");
			T.resetIndiceRonda();
			c.resetIndiceMazo();
			c.barajar();
			int auxRonda = T.getIndiceRonda();

			if (primeraPartida == false)
			{
				aux = Jugadores[0].turno;
				Jugadores[0].turno = Jugadores[1].turno;
				Jugadores[1].turno = aux;

				apuestaaux = apuestainicialjugador0;
				apuestainicialjugador0 = apuestainicialjugador1;
				apuestainicialjugador1 = apuestaaux;
			}

			Jugadores[0].setApuesta(apuestainicialjugador0);
			Jugadores[1].setApuesta(apuestainicialjugador1);
			c.repartirCartas(T, Jugadores);
			T.actualizarApuesta(Jugadores);
			status = GetTimeFormatA(LOCALE_CUSTOM_DEFAULT,
				TIME_FORCE24HOURFORMAT, NULL, NULL, formato, 30);
			registro << "Iteraccion: " << n << " Timelog: " << status << endl;
			manoAux = Jugadores[0].getMano();
			registro << "Mano Algoritmo: " << T.conversorNumero(manoAux[0]) << T.conversorPalo(manoAux[0]) << " " << T.conversorNumero(manoAux[1]) << T.conversorPalo(manoAux[1]) << endl;
			manoAux = Jugadores[1].getMano();
			registro << "Mano Algoritmo elegido: " << T.conversorNumero(manoAux[0]) << T.conversorPalo(manoAux[0]) << " " << T.conversorNumero(manoAux[1]) << T.conversorPalo(manoAux[1]) << endl;
			pasar = rondaAlg(T, c, Jugadores, alg,algOpo, acciones); // Preflop 
			registro << "Preflop" << endl;
			registro << acciones << endl;

			do {
				
				if (pasar == true)
					continuar = pasarApuestaAlg(T, Jugadores,c, alg, algOpo, n, n_veces);
				else {
					T.upIndiceRonda();
					auxRonda++;
					if (T.getIndiceRonda() == 4)
					{

						T.modificaTablero(Jugadores);
						T.actualizarApuesta(Jugadores);
						T.imprimirTablero(Jugadores);

						cout << "Show-down" << endl;
						jugador_gana = jugadorGana(T, Jugadores);
						if (jugador_gana == 1)
						{
							cout << "Jugador Gana" << endl;
							money = T.apuesta + Jugadores[0].getDinero();
							Jugadores[0].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if(Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						else if (jugador_gana == 2)
						{
							cout << "Oponente Gana" << endl;
							money = T.apuesta + Jugadores[1].getDinero();
							Jugadores[1].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if (Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						else if (jugador_gana == 0)
						{
							float money_jug = 0, money_opo = 0;
							cout << "EMPATE" << endl;
							money = T.apuesta / 2;
							money_jug = money + Jugadores[0].getDinero();
							money_opo = money + Jugadores[1].getDinero();
							Jugadores[0].setDinero(money_jug);
							Jugadores[1].setDinero(money_opo);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							if (Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							{
								continuar = false;
							}
							else
							{
								continuar = T.continuar();
							}
						}
						
					}
					else {
						{

						}
						pasar = ronda(T, c, Jugadores,alg); //Flop, turn y river
						if (pasar == true)
						{
							continuar = pasarApuesta(T, Jugadores,c);
						}

					}
				}
				
			} while (pasar == false && auxRonda < 4);

			if (continuar == true)
			{
				system("cls");
			} 

			if (continuar == false)
			{
				if (Jugadores[0].getDinero() > 0 && Jugadores[1].getDinero() > 0)
				{
					continuar == true;
				}
			}

			primeraPartida = false;
		} while (continuar == true);

		cout << "Fin de la partida" << endl;
		if (Jugadores[0].getDinero() == 0)
		{
			cout << "El jugador ha perdido" << endl;
		}
		else if (Jugadores[1].getDinero() == 0)
		{
			cout << "El oponente ha perdido" << endl;
		}
	}

}
float apuestaInicial(Mesa T, Jugador* Jugadores) {

	//Funcion para determinar la apuesta que se va a definir como Ciega Grande y, por tanto, a ciega pequeña

	float bid = 0;
	cout << "Introduzca el valor inicial de la apuesta (Ciega Grande):" << ' ';
	cin >> bid;
	cout << endl;
	random r;
	int coin = r.randomN(2);
	coin = 1;
	if (coin == 0)
	{
		Jugadores[0].turno = 0;
		Jugadores[1].turno = 1;
		Jugadores[0].setApuestaInicial(bid / 2);
		Jugadores[1].setApuestaInicial(bid);
	}
	else if (coin == 1)
	{
		Jugadores[0].turno = 1;
		Jugadores[1].turno = 0;
		Jugadores[1].setApuestaInicial(bid / 2);
		Jugadores[0].setApuestaInicial(bid);

	}
	return bid;
}
float iniciarPartida(Mesa T, Mazo c, Jugador* Jugadores)
{
	// Funcion de iniciar los valores de la partida: introduccion del valor del dinero inicial,
	// la apuesta inicial e inicializa el tablero de juego

	float dinero = 0;
	float bidini = 0;

	cout << "Introduce cantidad inicial de dinero para los jugadores:" << endl;
	cin >> dinero;
	Jugadores[0].setDinero(dinero);
	Jugadores[1].setDinero(dinero);
	T.creaTablero();
	bid=apuestaInicial(T, Jugadores);
	return bidini;
}
bool SeleccionarModo()
{ // Funcion para determinar si el algoritmo se va a enfrentar a un jugador o a uno de los algoritmos predefinidos
	char entrada;
	bool ok = false;
	do {
		cout << "¿Desea que el algoritmo se enfrente a un jugador o a otro algoritmo?" << endl;
		cout << "Introduzca J para Jugador o A para algoritmo: ";
		cin >> entrada;
		cout << endl;
		if (entrada == 'J')
		{
			ok = true;
			return true;
			
		}
		else if (entrada == 'A')
		{
			ok = true;
			return false;
			
		}
		else
		{
			cout << "Error. Por favor, introduzca J para Jugador o A para algoritmo " << endl;
		}
	} while (ok == false);

};

int SeleccionarAlgoritmo() 
{
	//Funcion para seleccionar el algoritmo contra el que jugará el algoritmo en el modo Algoritmo
	char entrada;
	bool ok = false;
	do {
		cout << "Algoritmos" << endl;
		cout << "1-Maniaco: Jugador agresivo, con fuertes subidas de manos y muchos faroles puros con manos malas" << endl;
		cout << "2-Roca: Jugador pasivo, juega sobre seguro, rara vez hace faroles" << endl;
		cout << "3-Calling Station: Jugador que juega de manera arriesgada, pero pasivamente, viendo apuestas con manos que no deberia" << endl;
		cout << "4-Algoritmo contra sí mismo: En caso de querer que el algoritmo se enfrente a sí mismo" << endl;
		cout << "5-Aleatorio: Se elige aleatoriamente uno de las otras 4 opciones" << endl;
		cout << "Introduzca el numero del algoritmo elegido: ";
		cin >> entrada;
		cout<< endl;
		if (entrada == '1')
		{
			return 1;
			ok = true;
		}
		else if (entrada == '2')
		{
			return 2;
			ok = true;
		}
		else if (entrada == '3')
		{
			return 3;
			ok = true;
		}
		else if (entrada == '4')
		{
			return 4;
			ok = true;
		}
		else if (entrada == '5')
		{
			return 5;
			ok = true;
		}
		else
		{
			cout << "Error. Por favor, introduzca uno de los indices de las opciones (1 a 5)" << endl;
		}
	} while (ok == false);
}

int main()
{

	Mesa Tablero ;
	Mazo deck;
	Jugador* Jugadores = new Jugador[NUM];
	bool jugador = true;
	int parametro = 0;
	jugador = SeleccionarModo();
	Algoritmo alg;
	if (jugador == false)
	{
		parametro = SeleccionarAlgoritmo();
	}
	float bidaux = 0;

	bidaux=iniciarPartida(Tablero, deck, Jugadores);
	jugarPartida(Tablero, deck, Jugadores, jugador, parametro, alg, bidaux);

	system("PAUSE");
}
