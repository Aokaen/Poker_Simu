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
	if (T.modoJ == true)
	{
		cout << "Valor jugada Jugador: " << Jug << endl;
		cout << "Valor jugada Oponente: " << opo << endl;
	}
	else
	{
		cout << "Showdown alcanzado" << endl;
	}
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


bool pasarApuesta(Mesa T, Jugador* Jugadores, Mazo c, int i) {

	//Funcion que efectua la accion de "Pasar" la apuesta

	bool continuar;
	float money = 0;
	float apuesta = 0;
	if(i==-1)
	{ 
		cout << "El jugador ha ganado" << endl;
		apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
		money = apuesta + Jugadores[0].getDinero();
		Jugadores[0].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
	else {
		cout << "El oponente ha ganado" << endl;
		apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
		money = apuesta + Jugadores[1].getDinero();
		Jugadores[1].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
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

void subirApuestaAlg(float qty, Mesa T, Jugador Jugador) {
	// //Funcion que efectua la accion de "Subir" la apuestadel algoritmo

	Jugador.setApuesta(qty);

}
void verApuesta(Mesa T, Jugador* Jugadores) { 

	//Funcion que efectua la accion de "Ver" la apuesta del jugador
	float diffJug = 0;
	diffJug= Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
	if (Jugadores[0].getDinero()<= diffJug)
	{
		cout << "ALL IN JUGADOR" << endl;
		Jugadores[0].setApuesta(Jugadores[0].getDinero()+ Jugadores[0].getApuesta());
	}
	else if (diffJug>=0)
	{
		Jugadores[0].setApuesta(Jugadores[1].getApuesta());
	}
	
}
void registro(string acciones, bool fin_linea)
{
	//Función para almacenar la información en el archivo .txt

	fstream registro;
	int k = 0;
	string lineaFinal;
	registro.open("log.txt", ios::in | ios::out);
	
	if (!registro.is_open())
	{
		registro.open("log.txt", ios::in | ios::out);
	}
	else {
		registro.seekg(-1, ios_base::end);
		bool bucle = true;
		while (bucle)
		{
			char ch;
			registro.get(ch);
			int auxiliar = (int)registro.tellg();
			if (auxiliar <= 1)
			{
				registro.seekg(0);
				bucle = false;
			}
			else if (ch == '\n')
			{
				bucle = false;
			}
			else
			{
				registro.seekg(-2, ios_base::cur);
			}
		}
		k = (int)registro.tellg();
		getline(registro, lineaFinal);
		registro.close();
	}

	registro.open("log.txt", ios::in | ios::out);
	if (registro.is_open())
	{
		registro.seekp(k, ios_base::beg);
		string grabar=lineaFinal.append(acciones);
		if (fin_linea == true)
		{
			registro << grabar << endl;
		}
		else
		{
			registro << grabar;
		}
		registro.close();
	}
	
}
void verApuestaAlg(Mesa T, Jugador* Jugadores) { 
	//Funcion que efectua la accion de "Ver" la apuesta del algoritmo
	float diffAlg = 0;
	if (T.modoJ == true)
	{
		diffAlg = Jugadores[0].getApuesta() - Jugadores[1].getApuesta();
		if (Jugadores[1].getDinero() <= diffAlg)
		{
			cout << "ALL IN AlGORITMO" << endl;
			Jugadores[1].setApuesta(Jugadores[1].getDinero()+ Jugadores[1].getApuesta());
		}
		else if (diffAlg>=0)
		{
			Jugadores[1].setApuesta(Jugadores[0].getApuesta());
		}
	}
	else
	{
		if (Jugadores[1].getApuesta() < Jugadores[0].getApuesta())
		{
			diffAlg = Jugadores[0].getApuesta() - Jugadores[1].getApuesta();
			if (Jugadores[1].getDinero() <= diffAlg)
			{
				cout << "ALL IN PATRON" << endl;
				Jugadores[1].setApuesta(Jugadores[1].getDinero()+ Jugadores[1].getApuesta());
			}
			else if (diffAlg>=0)
			{
				Jugadores[1].setApuesta(Jugadores[0].getApuesta());
			}
		}
		else if (Jugadores[1].getApuesta() > Jugadores[0].getApuesta())
		{
			diffAlg = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();
			if (Jugadores[0].getDinero() <= diffAlg)
			{
				cout << "ALL IN ALGORITMO" << endl;
				Jugadores[0].setApuesta(Jugadores[0].getDinero()+Jugadores[0].getApuesta());
			}
			else
			{
				Jugadores[0].setApuesta(Jugadores[1].getApuesta());
			}
		}
	}
}

int apostar(Mesa T, Jugador* Jugadores, Algoritmo alg)
{
	// Función que gestiona la ronda de apuestas y el funcionamiento de las apuestas en el modo Jugador vs Máquina

	char entrada, entrada_apuesta;
	bool pasar=false;
	float entrada_cantidad;
	float total = 0;
	bool apuesta_ok = false;
	bool apuestaFin = false;
	bool checkposible = true;
	int accion = -1;
	int accion_jugador = -1;
	int cantidad_alg = 0;
	int checking = 0;
	bool okay = false;
	int salida = 10;
	alg.pasa = false;
	
	int rond = T.getIndiceRonda();

	if (Jugadores[0].getDinero() == 0 || Jugadores[1].getDinero() == 0)
	{
		checkposible = false;
	}
	if (Jugadores[0].getApuesta() != Jugadores[1].getApuesta() )
	{
		checkposible = false;
	}

	if (rond == 0)
	{
		if (Jugadores[0].getDinero() != 0 && Jugadores[1].getDinero() != 0)
		{
			checkposible = true;
		}
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
					
					apuestaFin = true;
					accion_jugador = 1;
					
				}
				else if (Jugadores[1].getDinero() == 0)
				{
					if (Jugadores[1].AllIn == false)
					{
						cout << "El Algoritmo ha hecho All in." << endl;
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
								
								accion_jugador = 1;
								Jugadores[1].AllIn = true;
								alg.actualizaBayes(T.getIndiceRonda());
							}
							else if (entrada == 'P')
							{
								pasar = true;
								accion_jugador = 0;
								alg.pasar(T.getIndiceRonda());
							}
							else
							{
								cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

							}
						} while (entrada != 'P' && entrada != 'V');
					}
					else
					{
						cout << "El Algoritmo ha hecho All in y el jugador ha visto el All In." << endl;
						accion_jugador = 1;
					
					}
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
							accion_jugador = 0;
							alg.pasar(T.getIndiceRonda());
						}
						else if (entrada == 'A')
						{
						
							do {
								cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
								cin >> entrada_apuesta;
								if (entrada_apuesta == 'V')
								{
									verApuesta(T, Jugadores);
									apuestaFin = true;
									accion_jugador = 1;
									alg.actualizaBayes(T.getIndiceRonda());

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
									accion_jugador = 2;
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

				
				if (apuestaFin == false && Jugadores[0].getApuesta() != Jugadores[1].getApuesta())
				{//Accion del algoritmo
					if (Jugadores[1].getDinero() == 0)
					{
						cout << "El algoritmo no puede apostar, ya que ha hecho All In" << endl;

						apuestaFin = true;
						accion =1;
					
					}
					else if (Jugadores[0].getDinero() == 0)
					{
						if (Jugadores[0].AllIn == false)
						{
							cout << "El jugador ha hecho All in." << endl;
							T.actualizarApuesta(Jugadores);
							accion = alg.obtenerAccionAct(Jugadores[1], T, accion_jugador);
							if (accion == 0)
							{
								cout << "Algoritmo Pasa" << endl;
								alg.pasa = true;
								apuestaFin = true;
								pasar = true;
								system("PAUSE");
							}
							else
							{
								cout << "Algoritmo Ve el All In" << endl;
								verApuestaAlg(T, Jugadores);
								apuestaFin = true;
								Jugadores[0].AllIn = true;
								system("PAUSE");
							}
						}
						else
						{ 
							cout << "El jugador ha hecho All in y el algoritmo ha visto el All In." << endl;
							accion = 1;
							
							system("PAUSE");
						}
						apuestaFin = true;
					}
					else
					{
						T.actualizarApuesta(Jugadores);
						accion = alg.obtenerAccionAct(Jugadores[1], T, accion_jugador);
						if (accion == 0)
						{
							cout << "Algoritmo Pasa" << endl;
							alg.pasa = true;
							apuestaFin = true;
							pasar = true;
							system("PAUSE");
						}
						else if (accion == 1)
						{
							cout << "Algoritmo Ve la apuesta" << endl;
							verApuestaAlg(T, Jugadores);
							apuestaFin = true;
							system("PAUSE");
						}
						else if (accion == 2)
						{

							random r;
							int randn = r.nrandomPorcent();
							cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
							cantidad_alg = Jugadores[0].getApuesta() + (Jugadores[1].getApuestaInicial() + cantidad_alg * randn);
							float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

							if (diferencia_alg >= Jugadores[1].getDinero())
							{
								cout << "All In Algoritmo" << endl;
								float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						
								Jugadores[1].setApuesta(qty);
							}
							else
							{
								cout << "La nueva apuesta del algoritmo es: " << cantidad_alg << endl;

							
								Jugadores[1].setApuesta(cantidad_alg);
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
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							cout << "Apuesta total: " << T.apuesta << endl;


						}
					}
				}
				else if (Jugadores[1].getDinero() == 0)
				{
					cout << "El algoritmo no puede apostar, ya que ha hecho All In" << endl;
					apuestaFin = true;
					
					accion = 1;
					system("PAUSE");
				}
			}
			else
			{
				//Accion del algoritmo
				if (Jugadores[1].getDinero()==0)
			{ 
				cout << "El algoritmo no puede apostar, ya que ha hecho All In" << endl;
				apuestaFin = true;
				accion = 1;
				
				system("PAUSE");
			}
				else if (Jugadores[0].getDinero() == 0)
			{
				if(Jugadores[0].AllIn==false)
				{ 
					T.actualizarApuesta(Jugadores);
					accion = alg.obtenerAccionAct(Jugadores[1], T, accion_jugador);
					if (accion == 0)
					{
						cout << "Algoritmo Pasa" << endl;
						alg.pasa = true;
						pasar = true;
						apuestaFin = true;
						system("PAUSE");
					}
					else
					{
						cout << "Algoritmo Ve el All In" << endl;
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
						Jugadores[0].AllIn = true;
						system("PAUSE");
					}

				}
				else
				{
					cout << "El jugador ha hecho All in y el algoritmo ha visto el All In." << endl;
					accion = 1;
					pasar = false;
					system("PAUSE");
				}
			}
				else {
					T.actualizarApuesta(Jugadores);
				accion = alg.obtenerAccionAct(Jugadores[1], T, accion_jugador);
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
					pasar = true;
					system("PAUSE");
				}
				else if (accion == 1)
				{
					cout << "Algoritmo Ve la apuesta" << endl;
					verApuestaAlg(T, Jugadores);
					apuestaFin = true;
					pasar = true;
					system("PAUSE");
				}
				else if (accion == 2)
				{

					random r;
					float randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (Jugadores[1].getApuestaInicial() + cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						
						Jugadores[1].setApuesta(qty);
					}
					else
					{
						cout << "La nueva apuesta es:  " << cantidad_alg << endl;

						Jugadores[1].setApuesta(cantidad_alg);
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
					cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
					cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
					cout << "Apuesta total: " << T.apuesta << endl;
				}
			}
				//Acción del jugador
				if (apuestaFin == false && Jugadores[0].getApuesta() != Jugadores[1].getApuesta())
					{
						if (Jugadores[0].getDinero() == 0)
						{
							cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
							apuestaFin = true;
							pasar = false;
							accion_jugador = 1;
						}
						else if (Jugadores[1].getDinero() == 0)
						{
							if (Jugadores[1].AllIn == false)
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
										accion_jugador = 1;
										Jugadores[1].AllIn = true;
										alg.actualizaBayes(T.getIndiceRonda());

									}
									else if (entrada == 'P')
									{
										pasar = true;
										accion_jugador = 0;
										alg.pasar(T.getIndiceRonda());
									}
									else
									{
										cout << "Error. Introduzca V si quiere Ver el All in o P si quiere Pasar" << endl;

									}
								} while (entrada != 'P' && entrada != 'V');
							}
							else
							{
								cout << "El Algoritmo ha hecho All in y el jugador ha visto el All In." << endl;
								accion_jugador = 1;
								pasar = false;
							}
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
									accion_jugador = 0;
									alg.pasar(T.getIndiceRonda());
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
											accion_jugador = 1;
											alg.actualizaBayes(T.getIndiceRonda());

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
												accion_jugador = 2;
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
					else if (Jugadores[0].getDinero() == 0)
					{
					cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
					apuestaFin = true;
					
					accion_jugador = 1;
					}
			}
		}

		else
		{
		Jugadores[0].AllIn = false;
		Jugadores[1].AllIn = false;
			if (Jugadores[0].turno == 0)
			{
				//Acción del jugador
				do {
				if (rond == 0)
				{
					cout << "¿Desea ver la apuesta inicial (V), Subir la Apuesta (S) o Pasar (P)?" << endl;
				}
				else
				{
					cout << "¿Desea seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
				}
				cin >> entrada;
				
					if (entrada == 'P')
					{
						okay = true;
						pasar = true;
						apuestaFin = true;
						accion_jugador = 0;
						alg.pasar(T.getIndiceRonda());
					}
					else if (entrada == 'S')
					{
						okay = true;
						checkposible = false;
						bool apuesta_subida = false;
						float entrada_subida = 0;
						accion_jugador = 2;
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
						checking = 1;
						accion_jugador = 1;
						okay = true;
						
					}
					else if (entrada == 'V')
					{
						checking = 1;
						verApuesta(T, Jugadores);
						accion_jugador = 1;
						okay = true;
						
					}
					else
					{
						cout << "Error. Introduzca una opción válida" << endl;
					}
				} while (okay == false);
				//Accion del algoritmo
				if (apuestaFin == false)
				{
					if(Jugadores[1].getDinero()==0)
					{ 
						cout << "El algoritmo no puede apostar, ya que ha hecho All In" << endl;
						apuestaFin = true;
						accion = 1;
						
					}
					else if(Jugadores[0].getDinero()==0)
					{ 
						if (Jugadores[1].AllIn == false)
						{
							T.actualizarApuesta(Jugadores);
							accion = alg.obtenerAccionSegundo(Jugadores[1], T, accion);
							if (accion == 0)
							{
								cout << "Algoritmo Pasa" << endl;
								alg.pasa = true;
								apuestaFin = true;
								pasar = true;
								system("PAUSE");
							}
							else
							{
								cout << "Algoritmo Ve el All in" << endl;
								verApuestaAlg(T, Jugadores);
								apuestaFin = true;
								Jugadores[1].AllIn = true;
							}


						}
						else
						{
							cout << "El jugador ha hecho el All in y el algoritmo lo ha visto" << endl;
							apuestaFin = true;
							accion = 1;
							
						}
					}
					else
					{
						T.actualizarApuesta(Jugadores);
						accion = alg.obtenerAccionSegundo(Jugadores[1], T, accion_jugador);
						if (accion == 0)
						{
							cout << "Algoritmo Pasa" << endl;
							alg.pasa = true;
							apuestaFin = true;
							pasar = true;
							system("PAUSE");
						}
						else if (accion == 1)
						{
							if (checking == 1)
							{
								checking = 0;
								apuestaFin = true;
								if (rond == 0)
								{
									cout << "Ambos ven la apuesta" << endl;
								}
								else
								{
									cout << "Ambos siguen la apuesta" << endl;
								}
							}
							else
							{
								cout << "Algoritmo Ve la apuesta" << endl;
								verApuestaAlg(T, Jugadores);
								apuestaFin = true;
							}
							system("PAUSE");
						}
						else if (accion == 2)
						{
							checkposible = false;
							random r;
							float randn = r.nrandomPorcent();
							cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
							cantidad_alg = Jugadores[0].getApuesta() + (cantidad_alg + cantidad_alg * randn);
							float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

							if (diferencia_alg >= Jugadores[1].getDinero())
							{
								cout << "All In Algoritmo" << endl;
								float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
							
								Jugadores[1].setApuesta(qty);
							}
							else
							{
								cout << "La nueva apuesta del algoritmmo es: " << cantidad_alg << endl;
								Jugadores[1].setApuesta(cantidad_alg);
								
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
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							cout << "Apuesta total: " << T.apuesta << endl;
						}
					}
				}
			}
			else
			{
				//Accion del algoritmo
				T.actualizarApuesta(Jugadores);
				accion = alg.obtenerAccion(Jugadores[1], T);
				if (accion == 0)
				{
					cout << "Algoritmo Pasa" << endl;
					alg.pasa = true;
					apuestaFin = true;
					pasar = true;
					system("PAUSE");
				}
				else if (accion == 1)
				{
					if (rond == 0)
					{
						cout << "Algoritmo iguala la apuesta inicial" << endl;
						verApuestaAlg(T, Jugadores);
					}
					else
					{
						cout << "Algoritmo sigue la apuesta" << endl;
					}
					checking = 1;
				}
				else if (accion == 2)
				{
					checkposible = false;
					random r;
					float randn = r.nrandomPorcent();
					cantidad_alg = Jugadores[1].getApuestaInicial() * 2;
					cantidad_alg = Jugadores[0].getApuesta() + (Jugadores[1].getApuestaInicial() + cantidad_alg * randn);
					float diferencia_alg = cantidad_alg - Jugadores[1].getApuesta();

					if (diferencia_alg >= Jugadores[1].getDinero())
					{
						cout << "All In Algoritmo" << endl;
						float qty = Jugadores[1].getApuesta() + Jugadores[1].getDinero();
						
						Jugadores[1].setApuesta(qty);
					}
					else
					{
						cout << "La nueva apuesta es: " << cantidad_alg << endl;
					
						Jugadores[1].setApuesta(cantidad_alg);
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
					cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
					cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
					cout << "Apuesta total: " << T.apuesta << endl;
				}

				//Acción del jugador
				if (alg.pasa == false)
				{	
					if (Jugadores[0].getApuesta() == Jugadores[1].getApuesta())
					{
						do {
							okay = false;
							cout << "¿Desea Seguir la apuesta (C), Subir la Apuesta (S) o Pasar (P)?" << endl;
							cin >> entrada;
							if (entrada == 'P')
							{
								pasar = true;
								apuestaFin = true;
								accion_jugador = 0;
								okay = true;
								alg.pasar(T.getIndiceRonda());
							}
							else if (entrada == 'S')
							{
								okay = true;
								checkposible = false;
								bool apuesta_subida = false;
								float entrada_subida = 0;
								accion_jugador = 2;
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
								okay = true;
								accion_jugador = 1;
								checking = 0;
								apuestaFin = true;
								alg.actualizaBayes(T.getIndiceRonda());
								cout << "Ambos siguen la apuesta" << endl;

							}
							else
							{
								cout << "Error, eliga una opción válida" << endl;
							}
						} while (okay == false);
					}
					else
					{
						
						if (Jugadores[0].getDinero() == 0)
						{
							cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
							cout << "Pulse cualquier tecla para continuar..." << endl;
							char inside;
							cin >> inside;
							apuestaFin = true;
							
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
								
									accion_jugador = 1;
									alg.actualizaBayes(T.getIndiceRonda());

								}
								else if (entrada == 'P')
								{
									pasar = true;
									accion_jugador = 0;
									alg.pasar(T.getIndiceRonda());
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
									accion_jugador = 0;
									pasar = true;
									apuestaFin = true;
									alg.pasar(T.getIndiceRonda());
								}
								else if (entrada == 'A')
								{
									
									do {
										cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
										cin >> entrada_apuesta;
										if (entrada_apuesta == 'V')
										{
											accion_jugador = 1;
											verApuesta(T, Jugadores);
											apuestaFin = true;
											alg.actualizaBayes(T.getIndiceRonda());

										}
										else if (entrada_apuesta == 'S')
										{
											apuestaFin = false;
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
												accion_jugador = 2;

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
		}

	} while (apuestaFin == false);
	if (pasar == true)
	{
		if (alg.pasa == true)
		{
			salida = -1;
		}
		else
		{
			salida = 1;
		}
	}
	else
	{
		salida = 0;
	}
	return salida;
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
int ronda(Mesa T, Mazo c, Jugador* J,Algoritmo alg) {
	// Funcionamiento de cada Ronda, modifica el tablero y lanza la funcion apostar en el modo Jugador vs Maquina
	int salida = 10;
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

	salida = apostar(T,J,alg);

	return salida;

}
bool pasarApuestaAlg(Mesa T, Jugador* Jugadores, Mazo c, int pasa, int n_actual, int n_total)
{

	//Funcion que efectua la accion de "Pasar" la apuesta en el modo Máquina vs Máquina

	bool continuar;
	float money = 0;
	float apuesta = 0;
	float beneficio = 0;
	string log;
	apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
	if (pasa == 2)
	{
		
		beneficio = apuesta - Jugadores[0].getApuesta();
		log =log + "//Patron Pasa//" + "J1WJ2L" + "//+" + to_string(beneficio);
		money = apuesta + Jugadores[0].getDinero();
		Jugadores[0].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
	else if (pasa == 1)
	{
		
		beneficio = Jugadores[0].getApuesta();
		log = log + "//Algoritmo Pasa//" + "J1LJ2W" + "//-" + to_string(beneficio);
		money = apuesta + Jugadores[1].getDinero();
		Jugadores[1].setDinero(money);
		Jugadores[1].resetApuesta();
		Jugadores[0].resetApuesta();
	}
	registro(log, true);
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
int apostarAlg(Mesa T, Jugador* Jugadores, Algoritmo alg1, Algoritmo alg2)
{
	//Función que controla toda la ronda de apuestas en el modo Maquina vs Maquina
	int pasar = 0;
	float total = 0;
	bool apuesta_ok = false;
	bool apuestaFin = false;
	bool accionprevia = false;
	string acciones_ronda;
	float cantidad_alg = 0;
	float incremento = 0;
	int accion1 = -1, accion2 = -1;
	int conteo_subidas = 0;
	do {

		if (Jugadores[0].turno == 0)
		{
			if (Jugadores[0].getDinero() == 0) //algoritmo no puede apostar
			{
				apuestaFin = true;
				pasar = 0;
				alg1.accion = 1;
				acciones_ronda = acciones_ronda + " J1C";


			}
			else if (Jugadores[1].getDinero() == 0 && Jugadores[1].getApuesta() != 0)
			{

				float diferencia = 0;
				diferencia = Jugadores[1].getApuesta() - Jugadores[0].getApuesta();

				if (diferencia != 0)
				{
					T.actualizarApuesta(Jugadores);
					alg1.accion = alg1.obtenerAccionAct(Jugadores[0], T, 2);

					if (alg1.accion == 0)
					{
						pasar = 1;
						alg1.pasa = true;
						apuestaFin = true;
						acciones_ronda = acciones_ronda + " J1P";

					}
					else
					{
						float subidaalg;

						if (diferencia >= Jugadores[0].getDinero())
						{
							verApuestaAlg(T, Jugadores);
							subidaalg = Jugadores[0].getApuesta();

						}
						else
						{
							cantidad_alg = Jugadores[0].getDinero();
							
							Jugadores[0].setApuesta(cantidad_alg);
							subidaalg = cantidad_alg;
						}

						apuestaFin = true;
						acciones_ronda = acciones_ronda + " J1V" + to_string(subidaalg);

					}
				}


			}
			else
			{
				T.actualizarApuesta(Jugadores);
				if (accionprevia == false)
				{
					alg1.accion = alg1.obtenerAccion(Jugadores[0], T);
				}
				else
				{
					alg1.accion = alg1.obtenerAccionAct(Jugadores[0], T, alg2.accion);
				}
				if (conteo_subidas<=3)
				{
					if (alg1.accion == 0)
					{
						pasar = 1;
						alg1.pasa = true;
						apuestaFin = true;
						acciones_ronda = acciones_ronda + " J1P";

					}
					else if (alg1.accion == 1)
					{
						acciones_ronda = acciones_ronda + " J1V";

						if (accionprevia == false)
						{
							accionprevia = true;


							//actualizarinfoalg2
							accion1 = alg1.accion;
							T.actualizarApuesta(Jugadores);
							alg2.accion = alg2.obtenerAccionSegundo(Jugadores[1], T, alg1.accion);
							accion2 = alg2.accion;

							if (accion2 == 0)
							{
								pasar = 2;
								alg2.pasa = true;
								apuestaFin = true;
								acciones_ronda = acciones_ronda + " J2P";


							}
							else if (accion2 == 1)
							{
								apuestaFin = true;
								verApuestaAlg(T, Jugadores);
								acciones_ronda = acciones_ronda + " J2V";
								alg1.actualizaBayes(T.getIndiceRonda());

							}
							else if (accion2 == 2)
							{
								float cantidad_subida = 0;
								cantidad_subida = alg2.obtenerSubida(Jugadores[0].getApuesta(), Jugadores[0].getApuestaInicial());
								incremento = cantidad_subida - Jugadores[1].getApuesta();
								if (incremento >= Jugadores[1].getDinero())
								{
									cantidad_subida = Jugadores[1].getDinero() + Jugadores[1].getApuesta();
								}
								acciones_ronda = acciones_ronda + " J2S" + to_string(cantidad_subida);

								
								Jugadores[1].setApuesta(cantidad_subida);
								accionprevia = true;
							}

						}
						else
						{
							verApuestaAlg(T, Jugadores);
							apuestaFin = true;
						}
					}
					else if (alg1.accion == 2)
					{
						conteo_subidas++;
						float cantidad_subida2 = 0;
						float apuesta_max = 0;

						if (Jugadores[0].getApuesta() < Jugadores[1].getApuesta())
						{
							apuesta_max = Jugadores[1].getApuesta();
						}
						else
						{
							apuesta_max = Jugadores[0].getApuesta();
						}
						cantidad_subida2 = alg1.obtenerSubida(apuesta_max, Jugadores[1].getApuestaInicial());
						incremento = cantidad_subida2 - Jugadores[1].getApuesta();
						if (incremento >= Jugadores[0].getDinero())
						{
							cantidad_subida2 = Jugadores[0].getDinero() + Jugadores[0].getApuesta();
						}
						Jugadores[0].setApuesta(cantidad_subida2);
						acciones_ronda = acciones_ronda + " J1S" + to_string(cantidad_subida2);

						//actualizarinfoalg2
						accion1 = alg1.accion;
						T.actualizarApuesta(Jugadores);
						if (accionprevia == false)
							alg2.accion = alg2.obtenerAccionSegundo(Jugadores[1], T, accion1);
						else
							alg2.accion = alg2.obtenerAccionAct(Jugadores[1], T, accion1);
						accionprevia = true;
						accion2 = alg2.accion;
						if(conteo_subidas<=3){
							if (accion2 == 0)
							{
								pasar = 2;
								alg2.pasa = true;
								apuestaFin = true;
								acciones_ronda = acciones_ronda + " J2P";


							}
							else if (accion2 == 1)
							{
								apuestaFin = true;
								verApuestaAlg(T, Jugadores);
								acciones_ronda = acciones_ronda + " J2V";
								alg1.actualizaBayes(T.getIndiceRonda());

							}
							else if (accion2 == 2)
							{
								conteo_subidas++;
								float cantidad_subida = 0;
								cantidad_subida = alg2.obtenerSubida(Jugadores[0].getApuesta(), Jugadores[0].getApuestaInicial());
								incremento = cantidad_subida - Jugadores[1].getApuesta();
								if (incremento >= Jugadores[1].getDinero())
								{
									cantidad_subida = Jugadores[1].getDinero() + Jugadores[1].getApuesta();
								}
								acciones_ronda = acciones_ronda + " J2S" + to_string(cantidad_subida);

								
								Jugadores[1].setApuesta(cantidad_subida);
								accionprevia = true;
							}
						}
						else
						{
							if (accion2 == 0)
							{
								pasar = 2;
								alg2.pasa = true;
								apuestaFin = true;
								acciones_ronda = acciones_ronda + " J2P";
								


							}
							else if (accion2 == 1)
							{
								apuestaFin = true;
								verApuestaAlg(T, Jugadores);
								acciones_ronda = acciones_ronda + " J2V";
								alg1.actualizaBayes(T.getIndiceRonda());

							}
							else if (accion2 == 2)
							{
								apuestaFin = true;
								verApuestaAlg(T, Jugadores);
								acciones_ronda = acciones_ronda + " J2VF";
								alg1.actualizaBayes(T.getIndiceRonda());

							}
						}
						


					}

				}
				else
				{
					if (alg1.accion == 0)
					{
						pasar = 1;
						alg1.pasa = true;
						apuestaFin = true;
						acciones_ronda = acciones_ronda + " J1P";

					}
					else if (alg1.accion == 1)
					{
						acciones_ronda = acciones_ronda + " J1V";
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;

					}
					else if (alg1.accion == 2)
					{

						acciones_ronda = acciones_ronda + " J1VF";
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
					}
				}
			}
		}
		else
		{
		
		if (Jugadores[1].getDinero() == 0) //algoritmo 2 no puede apostar
		{
			apuestaFin = true;
			pasar = 0;
			alg2.accion = 1;
			acciones_ronda = acciones_ronda + " J2C";
			

		}
		else if (Jugadores[0].getDinero() == 0 && Jugadores[0].getApuesta() != 0)
		{

			float diferencia = 0;
			diferencia = Jugadores[0].getApuesta() - Jugadores[1].getApuesta();
			
			if (diferencia != 0)
			{
				T.actualizarApuesta(Jugadores);
				alg2.accion = alg2.obtenerAccionSegundo(Jugadores[1],T,2);
				if (alg2.accion == 0)
				{
					pasar = 2;
					alg2.pasa = true;
					apuestaFin = true;
					acciones_ronda = acciones_ronda + " J2P";
					
					
				}
				else
				{
					float subidaalg;

					if (diferencia >= Jugadores[1].getDinero())
					{
						verApuestaAlg(T, Jugadores);
						subidaalg = Jugadores[1].getApuesta();

					}
					else
					{
						cantidad_alg = Jugadores[1].getDinero();
			
						Jugadores[1].setApuesta(cantidad_alg);
						subidaalg = cantidad_alg;
					}

					apuestaFin = true;
					acciones_ronda = acciones_ronda + " J2V" + to_string(subidaalg);
					alg1.actualizaBayes(T.getIndiceRonda());
					
				}
			}


		}
		else
		{
			T.actualizarApuesta(Jugadores);
			if (accionprevia == false)
			{
				alg2.accion = alg2.obtenerAccion(Jugadores[1],T);
			}
			else
			{
				alg2.accion = alg2.obtenerAccionAct(Jugadores[1],T,alg1.accion);
			}
			if(conteo_subidas<=3)
				{ 
				if (alg2.accion == 0)
				{
					pasar = 2;
					alg2.pasa = true;
					apuestaFin = true;
					acciones_ronda = acciones_ronda + " J2P";
					

				}
				else if (alg2.accion == 1)
				{
					acciones_ronda = acciones_ronda + " J2V";

					if (accionprevia == false)
					{
						accionprevia = true;


						//actualizarinfoalg2
						accion2 = alg2.accion;
						T.actualizarApuesta(Jugadores);
						alg1.accion = alg1.obtenerAccionSegundo(Jugadores[0], T, alg2.accion);
						accion1 = alg1.accion;

						if (accion1 == 0)
						{
							pasar = 1;
							alg1.pasa = true;
							apuestaFin = true;
							acciones_ronda = acciones_ronda + " J1P";


						}
						else if (accion1 == 1)
						{
							apuestaFin = true;
							verApuestaAlg(T, Jugadores);
							acciones_ronda = acciones_ronda + " J1V";


						}
						else if (accion1 == 2)
						{
							conteo_subidas++;
							float cantidad_subida = 0;
							cantidad_subida = alg1.obtenerSubida(Jugadores[1].getApuesta(), Jugadores[1].getApuestaInicial());
							incremento = cantidad_subida - Jugadores[0].getApuesta();
							if (incremento >= Jugadores[0].getDinero())
							{
								cantidad_subida = Jugadores[0].getDinero() + Jugadores[0].getApuesta();
							}
							acciones_ronda = acciones_ronda + " J1S" + to_string(cantidad_subida);

						
							Jugadores[0].setApuesta(cantidad_subida);
							accionprevia = true;
						}

					}
					else
					{
						verApuestaAlg(T, Jugadores);
						apuestaFin = true;
						alg1.actualizaBayes(T.getIndiceRonda());
					}
				}
				else if (alg2.accion == 2)
				{
					conteo_subidas++;
					float cantidad_subida2 = 0;
					float apuesta_max = 0;

					if (Jugadores[1].getApuesta() < Jugadores[0].getApuesta())
					{
						apuesta_max = Jugadores[0].getApuesta();
					}
					else
					{
						apuesta_max = Jugadores[1].getApuesta();
					}
					cantidad_subida2 = alg2.obtenerSubida(apuesta_max, Jugadores[1].getApuestaInicial());
					incremento = cantidad_subida2 - Jugadores[0].getApuesta();
					if (incremento >= Jugadores[1].getDinero())
					{
						cantidad_subida2 = Jugadores[1].getDinero() + Jugadores[1].getApuesta();
					}
					Jugadores[1].setApuesta(cantidad_subida2);
					acciones_ronda = acciones_ronda + " J2S" + to_string(cantidad_subida2);

					//actualizarinfoalg2
					accion2 = alg2.accion;
					T.actualizarApuesta(Jugadores);
					if (accionprevia == false)
						alg1.accion = alg1.obtenerAccionSegundo(Jugadores[0], T, accion2);
					else
						alg1.accion = alg1.obtenerAccionAct(Jugadores[0], T, accion2);

					accionprevia = true;
					accion1 = alg1.accion;
					if(conteo_subidas<=3)
					{
						if (accion1 == 0)
						{
							pasar = 1;
							alg1.pasa = true;
							apuestaFin = true;
							acciones_ronda = acciones_ronda + " J1P";


						}
						else if (accion1 == 1)
						{
							apuestaFin = true;
							verApuestaAlg(T, Jugadores);
							acciones_ronda = acciones_ronda + " J1V";

						}
						else if (accion1 == 2)
						{
							conteo_subidas++;
							float cantidad_subida = 0;
							cantidad_subida = alg1.obtenerSubida(Jugadores[1].getApuesta(), Jugadores[1].getApuestaInicial());
							incremento = cantidad_subida - Jugadores[0].getApuesta();
							if (incremento >= Jugadores[0].getDinero())
							{
								cantidad_subida = Jugadores[0].getDinero() + Jugadores[0].getApuesta();
							}
							acciones_ronda = acciones_ronda + " J1S" + to_string(cantidad_subida);

							
							Jugadores[0].setApuesta(cantidad_subida);
							accionprevia = true;
						}
					}
					else
					{
						if (accion1 == 0)
						{
							pasar = 1;
							alg1.pasa = true;
							apuestaFin = true;
							acciones_ronda = acciones_ronda + " J1P";


						}
						else if (accion1 == 1)
						{
							apuestaFin = true;
							verApuestaAlg(T, Jugadores);
							acciones_ronda = acciones_ronda + " J1V";

						}
						else if (accion1 == 2)
						{
							apuestaFin = true;
							verApuestaAlg(T, Jugadores);
							acciones_ronda = acciones_ronda + " J1VF";

						}

					}


				}
			}
			else
			{
			if (alg2.accion == 0)
			{
				pasar = 2;
				alg2.pasa = true;
				apuestaFin = true;
				acciones_ronda = acciones_ronda + " J2P";
				

			}
			else if (alg2.accion == 1)
			{
				acciones_ronda = acciones_ronda + " J2V";
				verApuestaAlg(T, Jugadores);
				apuestaFin = true;
				alg1.actualizaBayes(T.getIndiceRonda());
				
			}
			else if (alg2.accion == 2)
			{
				acciones_ronda = acciones_ronda + " J2VF";
				verApuestaAlg(T, Jugadores);
				apuestaFin = true;
				alg1.actualizaBayes(T.getIndiceRonda());

			}
			}
			
		}
		}

	} while (apuestaFin == false);
	registro(acciones_ronda, false);
	return pasar;
}
int rondaAlg(Mesa T, Mazo c, Jugador* J, Algoritmo alg1, Algoritmo alg2)
{
	// Funcionamiento de cada Ronda para el modo Máquina vs Máquina y lanza la funcion apostar del modo Máquina vs Máquina
	int pasar = 0;
	bool jugador_gana;
	int auxRonda = T.getIndiceRonda();
	int auxTablero = T.getIndiceTablero();
	
	calcularValorjugador(T, J, auxRonda);
	pasar = apostarAlg(T, J, alg1, alg2);
	T.actualizarApuesta(J);
	return pasar;

}

void jugarPartida(Mesa T, Mazo c, Jugador* Jugadores, bool jugador, int elegido, Algoritmo alg, float apuestaInicial) {
	// Funcion que controla el flujo de las rondas de juego

	bool continuar = true;
	int pasar = 15;
	int jugador_gana=-1; //1 jugador gana, 2 oponente gana, 0 empate
	
	float money = 0;
	float apuestainicialjugador0 = Jugadores[0].getApuestaInicial();
	float apuestainicialjugador1 = Jugadores[1].getApuestaInicial();
	bool primeraPartida = true;
	int aux = -1;
	float apuestaaux = 0;
	alg.tipo = 4;
	if (jugador == true)
	{
		T.modoJ = true;
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
				
				if (pasar == -1 || pasar == 1)
					continuar = pasarApuesta(T, Jugadores,c,pasar);
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
						
						pasar = ronda(T, c, Jugadores,alg); //Flop, turn y river
						if (pasar == -1 || pasar == 1)
						{
							continuar = pasarApuesta(T, Jugadores,c,pasar);
						}

					}
				}
				
			} while (pasar == 0 && auxRonda < 4);

			if (continuar == true)
			{
				system("cls");
			} 

			if (continuar == false)
			{
				if (Jugadores[0].getDinero() > 0 && Jugadores[1].getDinero() > 0)
				{
					continuar = true;
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
	T.modoJ = false;
	Algoritmo algOpo; //Jugador[1]
	if (elegido <= 3)
	{
		algOpo.tipo = elegido;
	}
	else
	{
		switch (elegido)
		{
		case 5:
			alg.tipo = 1;
			algOpo.tipo = 2;
			break;
		case 13:
			alg.tipo = 2;
			algOpo.tipo = 3;
			break;
		case 10:
			alg.tipo = 3;
			algOpo.tipo = 1;
			break;
		}
	}
	int n = 0;
	string acciones;
	int n_veces=0;
	cout << "Introducir el numero de iteracciones deseadas:";
	cin >> n_veces;
	cout << endl;
	Carta* manoAux = new Carta[2];
	Carta* mesaAux = new Carta[5];
	string log;
	bool fin_linea;
	char formato[30];
	int status;
	int beneficio_total = 0, victorias = 0;
	string cadena_aux;
	int p = -1;

	
		do {
			p = n;
			n = n + 1;
			
			fin_linea = false;
			
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
			
			log = "It: " + to_string(n) + "//";
			cout << "Iteracion: " << to_string(n) << endl;
			manoAux = Jugadores[0].getMano();
			log = log + "Mano Alg: "+ T.conversorNumero(manoAux[0]) + T.conversorPalo(manoAux[0]) + " " + T.conversorNumero(manoAux[1]) + T.conversorPalo(manoAux[1]);
			manoAux = Jugadores[1].getMano();
			log = log + " Mano patron: " + T.conversorNumero(manoAux[0]) + T.conversorPalo(manoAux[0]) + " " + T.conversorNumero(manoAux[1]) + T.conversorPalo(manoAux[1])+"//";
			log = log + "R0" + acciones + "//";
			registro(log, fin_linea);
			pasar = rondaAlg(T, c, Jugadores, alg,algOpo); // Preflop 
			
			do {
				
				if (pasar != 0)
				{
					if (pasar == 1)
					{
						beneficio_total = beneficio_total - Jugadores[0].getApuesta();
					}
					else if (pasar == 2)
					{
						beneficio_total = beneficio_total + Jugadores[1].getApuesta();
						victorias++;
						int indice_aux = T.getIndiceRonda() + 1;
						alg.pasar(indice_aux);
					}
					continuar = pasarApuestaAlg(T, Jugadores, c, pasar, n, n_veces);
				}
				else {
					T.upIndiceRonda();
					auxRonda++;
					if (T.getIndiceRonda() == 4)
					{
						float beneficio = 0;
						T.actualizarApuesta(Jugadores);
						
						log = "//Showdown//";
						jugador_gana = jugadorGana(T, Jugadores);
						if (jugador_gana == 1)
						{
							beneficio = T.apuesta - Jugadores[0].getApuesta();
							log = log + " " + "J1WJ2L" + "//+" + to_string(beneficio);
							money = T.apuesta + Jugadores[0].getDinero();
							Jugadores[0].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							fin_linea = true;
							beneficio_total = beneficio_total + beneficio;
							victorias++;
							
						}
						else if (jugador_gana == 2)
						{
							beneficio = Jugadores[0].getApuesta();
							log = log + " " + "J1LJ2W" + "//-" + to_string(beneficio);
							money = T.apuesta + Jugadores[1].getDinero();
							Jugadores[1].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							fin_linea = true;
							beneficio_total = beneficio_total - beneficio;
							
						}
						else if (jugador_gana == 0)
						{
							beneficio = T.apuesta * .5 - Jugadores[0].getApuesta();
							log= log + " " + "J1TJ2T" + "//=" + to_string(beneficio);
							float money_jug = 0, money_opo = 0;
							money = T.apuesta / 2;
							money_jug = money + Jugadores[0].getDinero();
							money_opo = money + Jugadores[1].getDinero();
							Jugadores[0].setDinero(money_jug);
							Jugadores[1].setDinero(money_opo);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(c);
							fin_linea = true;
							
						}
						registro(log, fin_linea);
						
					}
					else {
						Carta* array_aux = new Carta[5];
						array_aux = T.Tablero;
						log = "//R" + to_string(T.getIndiceRonda())+"//";
						if (T.getIndiceRonda() == 1)
						{
							log = log + " " + "Mesa: " + T.conversorNumero(array_aux[0]) + T.conversorPalo(array_aux[0]);
							log = log + " " + T.conversorNumero(array_aux[1]) + T.conversorPalo(array_aux[1]);
							log = log + " " + T.conversorNumero(array_aux[2]) + T.conversorPalo(array_aux[2]);
							
						}
						if (T.getIndiceRonda() == 2)
						{
							log = log+ " " + "Mesa: " + T.conversorNumero(array_aux[0]) + T.conversorPalo(array_aux[0]);
							log = log + " " + T.conversorNumero(array_aux[1]) + T.conversorPalo(array_aux[1]);
							log= log + " " +  T.conversorNumero(array_aux[2]) + T.conversorPalo(array_aux[2]);
							log = log + " " + T.conversorNumero(array_aux[3]) + T.conversorPalo(array_aux[3]);
							
						}
						if (T.getIndiceRonda() == 3)
						{
							log = log + " " + "Mesa: " + T.conversorNumero(array_aux[0]) + T.conversorPalo(array_aux[0]);
							log = log + " "  + T.conversorNumero(array_aux[1]) + T.conversorPalo(array_aux[1]);
							log = log + " "  + T.conversorNumero(array_aux[2]) + T.conversorPalo(array_aux[2]);
							log = log + " "  + T.conversorNumero(array_aux[3]) + T.conversorPalo(array_aux[3]);
							log = log + " " + T.conversorNumero(array_aux[4]) + T.conversorPalo(array_aux[4]);

						}
						registro(log, fin_linea);
						pasar = rondaAlg(T, c, Jugadores, alg, algOpo); //Flop, turn y river
						if (pasar !=0)
						{
							
							if (pasar == 1)
							{
								beneficio_total = beneficio_total - Jugadores[0].getApuesta();
							}
							else if (pasar == 2)
							{
								beneficio_total = beneficio_total + Jugadores[1].getApuesta();
								victorias++;
								int indice_aux = T.getIndiceRonda() + 1;
								alg.pasar(indice_aux);
							}
							continuar = pasarApuestaAlg(T, Jugadores, c, pasar, n, n_veces);
						}

					}
				}
				
			} while (pasar == 0 && auxRonda < 4);


			if (continuar == true)
			{
				if (Jugadores[0].getDinero() == 0 || Jugadores[1].getDinero() == 0)
				{
					continuar = false;
					if (Jugadores[0].getDinero() == 0)
					{
					log = "Algoritmo Pierde";
					}
					else if (Jugadores[1].getDinero() == 0)
					{
					log = "Patrón Pierde";
					}
					registro(log, true);
				}
			}

			primeraPartida = false;
			if (n >= n_veces)
			{
				continuar = false;
				log = "Numero de Iteraciones alcanzado";
				registro(log, true);
			}
			
			alg.reseteo();
		} while (continuar == true);
		
		log = "Victorias: " + to_string(victorias) + " Beneficio total: " + to_string(beneficio_total);
		registro(log, true);
		
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
	bidini=apuestaInicial(T, Jugadores);
	return bidini;
}
bool SeleccionarModo()
{ // Funcion para determinar si el algoritmo se va a enfrentar a un jugador o a uno de los algoritmos predefinidos
	char entrada;
	bool ok = false;
	do {
		cout << "¿Desea que el juego sea Jugador vs Maquina (J) o Maquina vs Maquina (M)?" << endl;
		cout << "Introduzca J para Jugador vs Maquina o M para Maquina vs Maquina: ";
		cin >> entrada;
		cout << endl;
		if (entrada == 'J')
		{
			ok = true;
			return true;
			
		}
		else if (entrada == 'M')
		{
			ok = true;
			return false;
			
		}
		else
		{
			cout << "Error. Por favor, introduzca J para Jugador vs Maquina o M para Maquina vs Maquina " << endl;
		}
	} while (ok == false);

};

int SeleccionarAlgoritmo() 
{
	//Funcion para seleccionar el algoritmo contra el que jugará el algoritmo en el modo Algoritmo
	char entrada,entrada_modo;
	bool ok = false, ok_modo = false;
	do{
		cout << "Los patrones son los siguientes:" << endl;
		cout << "1-Maniaco: Jugador agresivo, con fuertes subidas de manos y muchos faroles puros con manos malas" << endl;
		cout << "2-Roca: Jugador pasivo, juega sobre seguro, rara vez hace faroles" << endl;
		cout << "3-Calling Station: Jugador que juega de manera arriesgada, pero pasivamente, viendo apuestas con manos que no deberia" << endl;
		cout << "¿Desea que el algoritmo se enfrente a uno de los patrones (A) o que se enfrenten los patrones entre si (P)?" << endl;
		cout << "Introduzca A para Algoritmo vs Patron o P para Patron vs Patron: ";
		cin >> entrada_modo;
		cout << endl;
		if (entrada_modo == 'A')
		{
			do {
				cout << "Introduzca el numero del patron al que se enfrentara el algoritmo: ";
				cin >> entrada;
				cout << endl;
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
				else
				{
					cout << "Error. Por favor, introduzca uno de los indices de las opciones (1 a 3)" << endl;
				}
			} while (ok == false);
			ok_modo = true;
		}
		else if (entrada_modo == 'P')
		{
			cout << "Las combinaciones de patrones son los siguientes:" << endl;
			cout << "1-Maniaco vs Roca"<< endl;
			cout << "2-Roca vs Calling Station" << endl;
			cout << "3-Calling Station vs Maniaco" << endl;
			do{
				cout << "Introduzca el numero de la combinacion deseada: ";
				cin >> entrada;
				cout << endl;
				if (entrada == '1')
				{
					return 5;
					ok = true;
				}
				else if (entrada == '2')
				{
					return 13;
					ok = true;
				}
				else if (entrada == '3')
				{
					return 10;
					ok = true;
				}
				else
				{
					cout << "Error. Por favor, introduzca uno de los indices de las opciones (1 a 3)" << endl;
				}
			} while (ok == false);
			ok_modo = true;
		}
		else{
			cout << "Error. Por favor, introduzca A para Algoritmo vs Patron o P para Patron vs Patron" << endl;
		}
		
	}while(ok_modo == false);


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
	if (parametro <= 3)
	{
		alg.reseteo();
	}
	bidaux=iniciarPartida(Tablero, deck, Jugadores);
	jugarPartida(Tablero, deck, Jugadores, jugador, parametro, alg, bidaux);

	system("PAUSE");
}
