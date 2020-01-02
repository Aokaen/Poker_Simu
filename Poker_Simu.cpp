// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"
#define NUM 2

using namespace std;

carta* ordenarMano(carta* c) {
	carta aux;
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
float jugada(Mesa T, jugador j) {
	float valor_jugada = 0;
	valor_jugada = j.getValor();
	return valor_jugada;
}

bool jugadorGana(Mesa T, jugador* Jugadores) {
	float Jug = 0, opo = 0;
	Jug = jugada(T, Jugadores[0]);
	opo = jugada(T, Jugadores[1]);

	if (Jug > opo)
		return true;
	else
		return false;
}
void apuestaInicial(Mesa T, jugador* Jugadores) {
	float bid;
	cout << "Introduzca el valor inicial de la apuesta:";
	cin >> bid;
	cout << endl;
	if (bid > Jugadores[0].getDinero())
	{
		cout << "ALL IN JUGADOR" << endl;
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else if (bid > Jugadores[1].getDinero())
	{
		cout << "ALL IN OPONENTE" << endl;
		Jugadores[1].setApuesta(Jugadores[1].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(bid);
		Jugadores[1].setApuesta(bid * 2);// A CAMBIAR CON LA NUEVA IMPLEMENTACION
	}
}
bool pasarApuesta(Mesa T, jugador* Jugadores) {
	bool continuar;
	float money = 0;
	float apuesta = 0;
	cout << "El oponente ha ganado" << endl;
	apuesta = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
	money = apuesta + Jugadores[1].getDinero();
	Jugadores[1].setDinero(money);
	Jugadores[1].resetApuesta();
	Jugadores[0].resetApuesta();
	T.finRonda(Jugadores[1], Jugadores[0]);
	cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
	cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
	continuar = T.continuar();
	return continuar;
}

bool comprobarDinero(jugador* J)
{
	if (J[0].getApuesta() == J[1].getApuesta())
		
	{
		return true;
	}
	else if (J[0].getDinero() == 0 || J[1].getDinero() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}


}
void subirApuesta(float qty, Mesa T, jugador* Jugadores) {
	if (qty >= Jugadores[0].getDinero())
	{
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(qty);
	}
	//codigo a cambiar con la nueva implementacion
	Jugadores[1].setApuesta(qty);
	
}
void verApuesta(Mesa T, jugador* Jugadores) {
	if (Jugadores[1].getApuesta() > Jugadores[0].getDinero())
	{
		Jugadores[0].setApuesta(Jugadores[0].getDinero());
	}
	else
	{
		Jugadores[0].setApuesta(Jugadores[1].getApuesta());
	}
	
}
bool apostar(Mesa T, jugador* Jugadores)
{

	char entrada, entrada_apuesta;
	bool pasar=false;
	float entrada_cantidad;
	float total = 0;
	bool apuesta_ok = false;
	
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
				if (Jugadores[1].getApuesta() > Jugadores[0].getApuesta())
				{

					cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
				}
				cin >> entrada_apuesta;
				if (entrada_apuesta == 'V')
				{
					verApuesta(T, Jugadores);
					apuesta_ok = comprobarDinero(Jugadores);
				}
				else if (entrada_apuesta == 'S')
				{
					do {
						cout << "Introduzca la nueva apuesta:";
						cin >> entrada_cantidad;
						cout << endl;
						if (entrada_cantidad > Jugadores[1].getApuesta())
						{
							subirApuesta(entrada_cantidad, T, Jugadores);
							apuesta_ok = comprobarDinero(Jugadores);
						}
						else
						{
							cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
						}
					} while (apuesta_ok==false);

				}

				else
				{
					cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
				}
			

			} while (apuesta_ok==false);
			
			
		}
		else
		{
			cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
		}

	} while (entrada != 'P' && entrada != 'A');
	
	return pasar;
	int auxRonda = T.getIndiceRonda();
	if (auxRonda != 0 && auxRonda != 4)
	{
		float apuesta = Jugadores[1].getApuesta();
		apuesta = apuesta + 50;
		Jugadores[1].setApuesta(apuesta);
	}
}

void calcularValorjugador(Mesa T, jugador* J, int Ronda)
	{
	if (Ronda == 0)
	{
		J[0].ValorManoInicial();
		J[1].ValorManoInicial();
	}
	else if (Ronda == 1)
	{
		cout << " jugador: " << endl;
		J[0].ValorManoR1(T);
		cout << " oponente: " << endl;
		J[1].ValorManoR1(T);
	}
	else if (Ronda == 2)
	{
		cout << " jugador: " << endl;
		J[0].ValorManoR2(T);
		cout << " oponente: " << endl;
		J[1].ValorManoR2(T);
	}
	else if (Ronda == 3)
	{
		cout << " jugador: " << endl;
		J[0].ValorManoR3(T);
		cout << " oponente: " << endl;
		J[1].ValorManoR3(T);
	}

}
bool ronda(Mesa T, carta* c, jugador* J) {
	bool pasar = false;
	bool jugador_gana;
	int auxRonda = T.getIndiceRonda();
	int auxTablero = T.getIndiceTablero();
	T.modificaTablero(J);
	T.imprimirTablero(J);
	calcularValorjugador(T,J,auxRonda);
	cout << "Dinero actual jugador: " << J[0].getDinero() << endl;
	cout << "Dinero actual oponente: " << J[1].getDinero() << endl;
	cout << "Valor Jugada: "<<J->getValor() << endl;

	pasar = apostar(T,J);

	return pasar;

}
void jugarPartida(Mesa T, carta* c, jugador* Jugadores) {
	bool continuar = true;
	bool pasar = false;
	bool jugador_gana;
	char entrada;
	float money = 0;
	
	do {
		T.resetIndiceRonda();
		T.resetIndiceMazo();
		c= T.barajar(c);
		int auxRonda = T.getIndiceRonda(), auxMazo = T.getIndiceMazo();
		T.repartirCartas(Jugadores, c, T.Tablero, T.Quemada);
		for (int i = 0; i < 2; i++)
		{
			cout << "jugador" << i << endl;
			Jugadores[i].imprimeMano();
		}

		T.modificaTablero(Jugadores);
		apuestaInicial(T,Jugadores);
		pasar = ronda(T, c, Jugadores);
		do {
			//money = Jugadores[0].getApuesta() + Jugadores[1].getApuesta();
			//T.apuesta = money;
			if (pasar == true)
				continuar = pasarApuesta(T,Jugadores);
			else {
				T.upIndiceRonda();
				auxRonda++;
				if (T.getIndiceRonda() == 4)
				{
						
						T.modificaTablero(Jugadores);
						T.imprimirTablero(Jugadores);
						cout << "Show-down" << endl;
						jugador_gana = jugadorGana(T, Jugadores);
						if (jugador_gana == true)
						{
							cout << "Jugador Gana" << endl;
							money = T.apuesta + Jugadores[0].getDinero();
							Jugadores[0].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(Jugadores[0], Jugadores[1]);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							continuar = T.continuar();
						}
						else
						{
							cout << "Oponente Gana" << endl;
							money = T.apuesta + Jugadores[1].getDinero();
							Jugadores[1].setDinero(money);
							Jugadores[0].resetApuesta();
							Jugadores[1].resetApuesta();
							T.finRonda(Jugadores[1], Jugadores[0]);
							cout << "Dinero actual jugador: " << Jugadores[0].getDinero() << endl;
							cout << "Dinero actual oponente: " << Jugadores[1].getDinero() << endl;
							continuar = T.continuar();
						}
						if (Jugadores[0].getDinero() == 0 || Jugadores[1].getDinero() == 0)
							continuar = false;

				}
				else {
					{

					}
					pasar = ronda(T, c, Jugadores);
				    if (pasar == true)
					{
						continuar = pasarApuesta(T, Jugadores);
					}
					
				}
			}

		} while (pasar == false && auxRonda < 4);

		system("cls");
	} while (continuar == true);


}
void iniciarPartida(Mesa T, carta* c, jugador* Jugadores)
{
	float dinero = 0;

	cout << "Introduce cantidad inicial de dinero para los jugadores:" << endl;
	cin >> dinero;
	Jugadores[0].setDinero(dinero);
	Jugadores[1].setDinero(dinero);
	T.creaTablero();

}


int main()
{

	Mesa Tablero ;
	carta* mazo = Tablero.crearMazo();
	jugador* Jugadores = new jugador[NUM];


	iniciarPartida(Tablero, mazo, Jugadores);
	jugarPartida(Tablero, mazo, Jugadores);

	system("PAUSE");
}





















