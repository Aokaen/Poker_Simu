// Poker_Simu.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include "carta.h"
#include "Mesa.h"
#include "jugador.h"
#define NUM 2

using namespace std;
int main()
{
	Mesa Tablero;
	carta* mazo = Tablero.crearMazo();

	iniciarPartida(Tablero, mazo);
	jugarPartida(Tablero, mazo);

	system("PAUSE");
}

void iniciarPartida(Mesa T, carta* c)
{
	double dinero=0;
	double apuesta_inicial = 0;

	cout << "Introduce cantidad inicial de dinero para los jugadores:" << endl;
	cin >> dinero;
	T.Jugadores[0].setDinero(dinero);
	T.Jugadores[1].setDinero(dinero);
	T.creaTablero();
}

void jugarPartida(Mesa T, carta* c) {
	bool continuar = true;
	bool pasar = false;
	bool jugador_gana;
	char entrada;
	do {
		T.indiceRonda = 0;
		T.indiceMazo = 0;
		T.barajar(c);
		T.repartirCartas(T.Jugadores[0], c);
		T.repartirCartas(T.Jugadores[1], c);
		T.modificaTablero();
		apuestaInicial(T);
		pasar = apostar(T);
		do {
		if (pasar == true)
			pasarApuesta(T);
		else {
			
				T.indiceRonda++;
				pasar =ronda(T, c);
				if (pasar == false && T.indiceRonda == 4)
				{
					cout << "Show-down" << endl;
						jugador_gana = jugadorGana(T);
						if (jugador_gana == true)
						{
							continuar = T.finRonda(T.Jugadores[0], T.Jugadores[1]);
						}
						else
						{
							continuar = T.finRonda(T.Jugadores[1], T.Jugadores[0]);
						}
						if (T.Jugadores[0].getDinero == 0 || T.Jugadores[1].getDinero == 0)
							continuar == false;
				}
		}
		} while (pasar == false && T.indiceRonda < 4);
	} while (continuar == true);


}


bool apostar(Mesa T)
{
	char entrada, entrada_apuesta;
	bool pasar;
	double entrada_cantidad;
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
				if (T.Jugadores[1].getApuesta() > T.Jugadores[0].getApuesta())
				{
					cout << "¿Desea ver la apuesta (V) o subir la apuesta (S)?" << endl;
				}
				cin >> entrada_apuesta;
				if (entrada_apuesta == 'V')
					verApuesta(T);
				else if (entrada_apuesta == 'S')
				{
					do {
						cout << "Introduzca la nueva apuesta:";
						cin >> entrada_cantidad;
						cout << endl;
						if (entrada_cantidad > T.Jugadores[1].getApuesta())
							subirApuesta(entrada_cantidad, T);
						else
						{
							cout << "Error. Debe introducir una cantidad superior a la apuesta de su oponente" << endl;
						}
					} while (entrada_cantidad<=T.Jugadores[1].getApuesta());

				}
				else
				{
					cout << "Error. Introduzca V si quiere Ver la apuesta o S para subir la apuesta" << endl;
				}


			} while (T.Jugadores[1].getApuesta() != T.Jugadores[0].getApuesta());
		}
		else
		{
			cout << "Error. Introduzca A si quiere Apostar o P si quiere Pasar" << endl;
		}

	} while (entrada != 'Y' && entrada != 'N');
	return pasar;
}
void verApuesta(Mesa T) {
	T.Jugadores[0].setApuesta(T.Jugadores[1].getApuesta());
}

void subirApuesta(double qty, Mesa T) {
	T.Jugadores[0].setApuesta(qty);
	T.Jugadores[1].setApuesta(qty + 50); //A CAMBIAR CON LA NUEVA IMPLEMENTACION
}

bool pasarApuesta(Mesa T) {
	bool continuar;
	cout << "El oponente ha ganado" << endl;
	continuar = T.finRonda(T.Jugadores[1], T.Jugadores[0]);
	return continuar;
}

bool ronda(Mesa T, carta* c) {
	bool pasar = false;
	bool jugador_gana;
	if (T.indiceRonda != 4)
	{
		T.cartaQuemada(c);
		T.cartaTablero(c);
	}
	T.modificaTablero();
	pasar = apostar(T);

	return pasar;

}

void apuestaInicial(Mesa T) {
	double bid;
		cout << "Introduzca el valor inicial de la apuesta:";
		cin >> bid;
		cout << endl;
		if (bid > T.Jugadores[0].getDinero())
		{
			cout << "ALL IN JUGADOR" << endl;
			T.Jugadores[0].setApuesta(T.Jugadores[0].getDinero());//A cambiar con la nueva implementacion (All in)
		}
		else if (bid > T.Jugadores[1].getDinero())
		{
			cout << "ALL IN OPONENTE" << endl;
			T.Jugadores[1].setApuesta(T.Jugadores[1].getDinero());//A cambiar con la nueva implementacion (All in)
		}
		else
		{
			T.Jugadores[0].setApuesta(bid);
			T.Jugadores[1].setApuesta(bid * 2);// A CAMBIAR CON LA NUEVA IMPLEMENTACION
		}
}


bool jugadorGana(Mesa T) {
	double Jug = 0, opo = 0;
	Jug = jugada(T, T.Jugadores[0]);
	opo = jugada(T, T.Jugadores[1]);

	if (Jug > opo)
		return true;
	else
		return false;
}

double jugada(Mesa T, jugador j) {
	double valor_jugada;
	carta* jugada_final = new carta[7];
	carta* mano_final = new carta[2];
	for (int i = 0; i < 4;i++)
	{
		jugada_final[i] = T.Tablero[i];

	}
	mano_final = j.getMano();
	jugada_final[5] = mano_final[0];
	jugada_final[6] = mano_final[1];
	jugada_final = ordenarMano(jugada_final);
	valor_jugada = calcularJugada(jugada_final);
	return valor_jugada;

}

carta* ordenarMano(carta* c) {
	carta aux;
	for (int i = 0; i < 6; i++)
	{
		if (c[i].getNumero == 1)
		{
			c[i].setNumero(13);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int j = i + 1;
		for (j; j < 6; j++)
		{
			if (c[i].getNumero() < c[j].getNumero())
			{
				aux = c[i];
				c[i] = c[j];
				c[j] = aux;

			}
		}

	}
}

double calcularJugada(carta* c) {
	double jugada=0.0;
	int numero_rep[3] = { 0,0,0 };
	int palo_rep[3]{ 0,0,0 };
	int num_aux[3] = { 1,1,1 }, palo_aux[3] = { 1,1,1 };
	int n_rep = 0, p_rep = 0;
	int k = 0;
	bool escalera = false, color = false, segunda_pareja = false, trio = false, pareja = false, poker = false, tercera_pareja = false, segundo_trio = false, escalera_color=false, escalera_real = false;
	
	for(int i=0; i<5; i++)
	{ 
		int j = i + 1;
		for (j; j < 6; j++)
		{
			if (c[i].getNumero() == c[j].getNumero())
			{
				k = 0;
				do {
					if(c[i].getNumero()==numero_rep[k])
					{ 
						num_aux[k]++;
					}
					else if (numero_rep[k] == 0)
					{
						numero_rep[k]=c[i].getNumero();
						num_aux[k]++;
					}
					k++;
				} while (numero_rep[k]!=c[i].getNumero());

			}
			else if (c[i].getPalo() == c[j].getPalo())
			{
				k = 0;
				do {
					if (c[i].getPalo() == palo_rep[k])
					{
						palo_aux[k]++;
					}
					else if (palo_rep[k] == 0)
					{
						palo_rep[k] = c[i].getPalo();
						palo_aux[k]++;
					}
					k++;
				} while (palo_rep[k] != c[i].getPalo());

			}
		}

	}
	k = 0;
	do {
	if(num_aux[k]==4)
	{
		poker = true;

	}
	else if (num_aux[k] == 3)
	{
		if (trio==true)
		{
			segundo_trio = true;
		}
		else
		{
			trio = true;
		}
	}
	else if (num_aux[k] == 2)
	{
		if (pareja == true)
		{
			if (segunda_pareja == true)
			{
				tercera_pareja = true;
			}
			else
			{
				segunda_pareja = true;
			}
		}
		else
		{
			pareja = true;
		}
	}
	} while (num_aux[k] != 1);

	k = 0;
	do {
		if (palo_aux[k] == 5)
		{
			color = true;
		}
	} while (palo_aux[k] != 1);

	bool escalera_imposible = false;
	int conteo_n_ok = 0, conteo_imp = 0,conteo_palo=0;
	for (int i = 0; i < 5; i++)
	{
		if (c[i].getNumero() == (c[i + 1].getNumero()-1))
		{
			conteo_n_ok++;
			if(c[i].getPalo() == c[i + 1].getPalo())
			{
				conteo_palo++;
			}
			else
			{
				conteo_palo = 0;
			}
		}
		else
		{
			conteo_n_ok = 0;
			conteo_imp++;
			if(conteo_imp==3)
			{
				escalera_imposible = true;
			}
		}
		if (conteo_n_ok == 5)
		{escalera = true;
		if (conteo_palo == 5)
		{
			escalera_color = true;
			if (c[i].getNumero() == 10)
			{
				escalera_real = true;
			}
		}

	}
		if (c[0].getNumero() == 13)
		{
			if (c[3].getNumero() == 5 && c[4].getNumero() == 4 && c[5].getNumero() == 3 && c[6].getNumero() == 2)
			{
				escalera = true;
			}
		}
		bool encontrada = false;
		if (escalera_real == true)
			jugada = 9;
		else if (escalera_color == true)
		{
			jugada = 8;
			for (int i = 0; i < 2; i++)
			{
				if (palo_aux[i] == 5)
				{
					k = 0;
					do
					{
						if (c[k].getPalo() == palo_aux[i])
						{
							jugada = jugada + c[k].getNumero()*0.01;
							encontrada = true;
						}
						else
							k++;
					} while (encontrada == false);
				}
			}

		}
		else if (poker == true)
		{
			jugada = 7;

			for (int i = 0; i < 2; i++)
			{
				if (num_aux[i] == 4)
				{
					
				jugada = jugada + numero_rep[i] * 0.01;

				}
			}
		}
		else if (trio == true && pareja == true) //full house
		{
			jugada = 6;
			for (int i = 0; i < 2; i++)
			{
				if (num_aux[i] == 3)
				{

					jugada = jugada + numero_rep[i] * 0.01;

				}

				else if (num_aux[i] == 2 && segunda_pareja == false)
				{
					jugada = jugada + numero_rep[i] * 0.0001;
				}
				else if (num_aux[i] == 2 && segunda_pareja == true)
				{

				}
			}

		}
		else if (color == true && escalera_color == false)
		{
			jugada = 5;
		}
		else if (escalera == true && color == false)
		{
			jugada = 4;
		}
		else if (trio == true && pareja == false)
		{
			jugada = 3;
		}
		else if (pareja == true && segunda_pareja == true && trio == false)
		{
			jugada = 2;
		}
		else if (pareja == true && segunda_pareja == false && trio == false)
		{
			jugada = 1;
		}
		else
		{
			jugada = 0;
		}

	return jugada;
}
