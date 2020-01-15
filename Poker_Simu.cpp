// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"
#define NUM 2

using namespace std;

void AllIn(Jugador j, float qty) {

	// Funcion para determinar si el jugador puede apostar o no (ALL IN)

	float dinero = j.getDinero();
	float apuesta = j.getApuesta();
	float diferencia = qty - apuesta;
	if (dinero <= diferencia)
	{
		j.setAllIn(true);
	}
	else
	{
		j.setAllIn(false);
	}
}

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


bool pasarApuesta(Mesa T, Jugador* Jugadores) {

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
	T.finRonda();
	cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
	cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
	continuar = T.continuar();
	return continuar;
}
void subirApuesta(float qty, Mesa T, Jugador* Jugadores) {
	// //Funcion que efectua la accion de "Subir" la apuesta
	//AllIn(Jugadores[0], qty);
	//AllIn(Jugadores[1], qty);
	bool AllInJugador = Jugadores[0].getAllIn();
	bool AllInOponente = Jugadores[1].getAllIn();

	if (AllInJugador==true)
	{
		cout << "ALL IN JUGADOR" << endl;
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(qty);
	}
	
	
	
	//codigo a cambiar con la nueva implementacion
	if (AllInOponente == true)
	{
		cout << "ALL IN OPONENTE" << endl;
		Jugadores[1].setApuesta(Jugadores[1].getDinero());
	}
	else
	{
		Jugadores[1].setApuesta(qty);
	}
	
}
void verApuesta(Mesa T, Jugador* Jugadores) { // A retocar con la implementacion de R

	//Funcion que efectua la accion de "Ver" la apuesta

	//float qty = Jugadores[1].getApuesta();
	//AllIn(Jugadores[0], qty);
	bool AllInJugador = Jugadores[0].getAllIn();
	
	if (Jugadores[0].getDinero() == 0)
	{
		cout << "Jugador no puede apostar, está en All In" << endl;
	}
	else if (AllInJugador==true)
	{
		cout << "ALL IN JUGADOR" << endl;
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(Jugadores[1].getApuesta());
	}
	
}
bool apostar(Mesa T, Jugador* Jugadores)
{
	// Función que gestiona la ronda de apuestas y el funcionamiento de las apuestas

	char entrada, entrada_apuesta;
	bool pasar=false;
	float entrada_cantidad;
	float total = 0;
	bool apuesta_ok = false;
	bool AllInJugador = Jugadores[0].getAllIn();
	bool AllInOponente = Jugadores[1].getAllIn();
	
	
	do { 

		cout << "¿Desea Apostar (A) o Pasar (P)?" << endl;
		cin >> entrada;
		if (entrada == 'P')
		{
			pasar = true;
		}
		else if (entrada == 'A')
		{
			pasar = false;
			do {
				if (AllInJugador == true)
				{
					cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
					apuesta_ok = comprobarDinero(Jugadores);
				}
				else if (AllInOponente == true)
				{
					cout << "El jugador no puede apostar, ya que el oponente ha hecho All In" << endl;
					verApuesta(T, Jugadores);
					apuesta_ok = comprobarDinero(Jugadores);
				}
				else{
					if (Jugadores[1].getApuesta() > Jugadores[0].getApuesta())
					{

						cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
					}
					cin >> entrada_apuesta;
					if (entrada_apuesta == 'V')
					{
						AllIn(Jugadores[0], T.apuesta);
						AllIn(Jugadores[1], T.apuesta); //EDITAR
						verApuesta(T, Jugadores);
						apuesta_ok = comprobarDinero(Jugadores);
					}
					else if (entrada_apuesta == 'S')
					{
						do {
							if (AllInJugador== true)
							{
								cout << "El jugador no puede apostar, ya que ha hecho All In" << endl;
								apuesta_ok = comprobarDinero(Jugadores);
							}
							else if (AllInOponente == true)
							{
								cout << "El jugador no puede apostar, ya que el oponente ha hecho All In" << endl;
								verApuesta(T, Jugadores);
								apuesta_ok = comprobarDinero(Jugadores);
								
							}
							else
							{
								cout << "Introduzca la nueva apuesta:";
								cin >> entrada_cantidad;
								cout << endl;
								if (entrada_cantidad > Jugadores[1].getApuesta())
								{
									AllIn(Jugadores[0], entrada_cantidad);
									//AllIn(Jugadores[1], entrada_cantidad); //EDITAR
									subirApuesta(entrada_cantidad, T, Jugadores);
									apuesta_ok = comprobarDinero(Jugadores);
								}
								else
								{
									cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
								}
							}
						} while (apuesta_ok == false);

					}

					else
					{
						cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
					}

				}
				
			} while (apuesta_ok==false);
			
			
		}
		else
		{
			cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
		}

	} while (entrada != 'P' && entrada != 'A');
	
	int auxRonda = T.getIndiceRonda();
	if (auxRonda != 0 && auxRonda != 4)
	{
		float apuesta = Jugadores[1].getApuesta();
		apuesta = apuesta + 50;
		Jugadores[1].setApuesta(apuesta);
	}
	
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
bool ronda(Mesa T, Carta* c, Jugador* J) {
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

	pasar = apostar(T,J);

	return pasar;

}
void jugarPartida(Mesa T, Carta* c, Jugador* Jugadores, bool jugador, int algoritmo) {
	// Funcion que controla el flujo de las rondas de juego

	bool continuar = true;
	bool pasar = false;
	int jugador_gana=-1; //1 jugador gana, 2 oponente gana, 0 empate
	char entrada;
	float money = 0;
	float apuestainicialjugador = Jugadores[0].getApuestaInicial();
	float apuestainicialoponente = Jugadores[1].getApuestaInicial();
	if (jugador == true)
	{
		do {
			T.resetIndiceRonda();
			T.resetIndiceMazo();
			c = T.barajar(c);
			int auxRonda = T.getIndiceRonda(), auxMazo = T.getIndiceMazo();
			Jugadores[0].setApuesta(apuestainicialjugador);
			Jugadores[1].setApuesta(apuestainicialoponente);
			T.repartirCartas(Jugadores, c, T.Tablero, T.Quemada);

			T.modificaTablero(Jugadores);
			T.actualizarApuesta(Jugadores);
			pasar = ronda(T, c, Jugadores); // Preflop 
			do {
				
				if (pasar == true)
					continuar = pasarApuesta(T, Jugadores);
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
							T.finRonda();
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							continuar = T.continuar();
						}
						else if (jugador_gana == 2)
						{
							cout << "Oponente Gana" << endl;
							money = T.apuesta + Jugadores[1].getDinero();
							Jugadores[1].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda();
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							continuar = T.continuar();
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
							T.finRonda();
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							continuar = T.continuar();
						}
						if (Jugadores[0].getDinero() <= 0 || Jugadores[1].getDinero() <= 0)
							continuar = false;

					}
					else {
						{

						}
						pasar = ronda(T, c, Jugadores); //Flop, turn y river
						if (pasar == true)
						{
							continuar = pasarApuesta(T, Jugadores);
						}

					}
				}

			} while (pasar == false && auxRonda < 4);

			system("cls");
		} while (continuar == true);

		cout << "Fin de la partida" << endl;
		if (Jugadores[0].getDinero() <= 0)
		{
			cout << "El jugador ha perdido" << endl;
		}
		else if (Jugadores[1].getDinero() <= 0)
		{
			cout << "El jugador ha perdido" << endl;
		}
	}
	else
	{
		//EDITAR
		cout << "CODIGO EN PROCESO" << endl;
		cout << "Algorimo elegido" << endl;
		if (algoritmo == 1)
		{
			cout << "Maniaco" << endl;
		}
		else if (algoritmo == 2)
		{
			cout << "Roca" << endl;
		}
		else if (algoritmo == 3)
		{
			cout << "Calling Stations" << endl;
		}
		else
		{
			cout << "Random" << endl;
		}
	}

}
void apuestaInicial(Mesa T, Jugador* Jugadores) {

	//Funcion para determinar la apuesta que se va a definir como Ciega Grande y, por tanto, a ciega pequeña

	float bid = 0;
	cout << "Introduzca el valor inicial de la apuesta (Ciega Grande):" << ' ';
	cin >> bid;
	cout << endl;
	Jugadores[0].setApuestaInicial(bid / 2);
	Jugadores[1].setApuestaInicial(bid);
}
void iniciarPartida(Mesa T, Carta* c, Jugador* Jugadores)
{
	// Funcion de iniciar los valores de la partida: introduccion del valor del dinero inicial,
	// la apuesta inicial e inicializa el tablero de juego

	float dinero = 0;

	cout << "Introduce cantidad inicial de dinero para los jugadores:" << endl;
	cin >> dinero;
	Jugadores[0].setDinero(dinero);
	Jugadores[1].setDinero(dinero);
	T.creaTablero();
	apuestaInicial(T, Jugadores);

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
			return true;
			ok = true;
		}
		else if (entrada == 'A')
		{
			return false;
			ok = true;
		}
		else
		{
			cout << "Error. Por favor, introduzca J para Jugador o A para algoritmo " << endl;
		}
	} while (ok == false);

};

int SeleccionarAlgoritmo() 
{
	//Funcion para seleccionar el algoritmo a jugar contra en caso de seleccionar el modo algoritmo
	char entrada;
	bool ok = false;
	do {
		cout << "Algoritmos" << endl;
		cout << "1-Maniaco: Jugador agresivo, con fuertes subidas de manos y muchos faroles puros con manos malas" << endl;
		cout << "2-Roca: Jugador pasivo, juega sobre seguro, rara vez hace faroles" << endl;
		cout << "3- Calling Station: Jugador que juega de manera arriesgada, pero pasivamente, viendo apuestas con manos que no deberia" << endl;
		cout << "4-Aleatorio: Se elige aleatoriamente uno de los otros 3" << endl;
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
		else
		{
			cout << "Error. Por favor, introduzca uno de los indices de los algoritmos (1 a 4)" << endl;
		}
	} while (ok == false);
}

int main()
{

	Mesa Tablero ;
	Carta* mazo = Tablero.crearMazo();
	Jugador* Jugadores = new Jugador[NUM];
	bool jugador = true;
	int parametro = 0;
	jugador = SeleccionarModo();
	if (jugador == false)
	{
		parametro = SeleccionarAlgoritmo();
	}

	iniciarPartida(Tablero, mazo, Jugadores);
	jugarPartida(Tablero, mazo, Jugadores, jugador, parametro);

	system("PAUSE");
}





















