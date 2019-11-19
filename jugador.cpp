#include "jugador.h"
#include "carta.h"

jugador::jugador()
{

}
jugador::~jugador()
{

}

void jugador::setMano(carta c1, carta c2)
{
	mano[0] = c1;
	mano[1] = c2;
}

void jugador::setDinero(float d)
{
	dinero = d;
}


void jugador::calcularValorJugada(carta* c)
{
	float jugada = 0.0;
	int numero_rep[3] = { 0,0,0 };
	int aux = 0;
	int palo_rep[3]{ 0,0,0 };
	int num_aux[3] = { 1,1,1 }, palo_aux[3] = { 1,1,1 };
	int n_rep = 0, p_rep = 0;
	int k = 0;
	bool escalera = false, color = false, segunda_pareja = false, trio = false, pareja = false, poker = false, tercera_pareja = false, segundo_trio = false, escalera_color = false, escalera_real = false;

	for (int i = 0; i < 6; i++)
	{
		int j = i + 1;
		for (j; j < 7; j++)
		{
			if (c[i].getNumero() == c[j].getNumero())
			{
				k = 0;
				do {
					aux = c[i].getNumero();
					if (c[i].getNumero() == numero_rep[k])
					{
						num_aux[k]++;
					}
					else if (numero_rep[k] == 0)
					{
						numero_rep[k] = c[i].getNumero();
						num_aux[k]++;
					}
					k++;
				} while (numero_rep[k] != aux);

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
		if (num_aux[k] == 4)
		{
			poker = true;

		}
		else if (num_aux[k] == 3)
		{
			if (trio == true)
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
	int conteo_n_ok = 0, conteo_imp = 0, conteo_palo = 0;
	for (int i = 0; i < 6; i++)
	{
		if (c[i].getNumero() == (c[i + 1].getNumero() - 1))
		{
			conteo_n_ok++;
			if (c[i].getPalo() == c[i + 1].getPalo())
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
			if (conteo_imp == 3)
			{
				escalera_imposible = true;
			}
		}
		if (conteo_n_ok == 5)
		{
			escalera = true;
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
	}
	bool encontrada = false;
	if (escalera_real == true)
		jugada = 9;
	else if (escalera_color == true)
	{
		jugada = 8;
		for (int i = 0; i < 3; i++)
		{
			if (palo_aux[i] == 5)
			{
				k = 0;
				do
				{
					if (c[k].getPalo() == palo_aux[i])
					{
						jugada = jugada + c[k].getNumero() * 0.01;
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

		for (int i = 0; i < 3; i++)
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
		for (int i = 0; i < 3; i++)
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
				k = 0;
				do {
					if (num_aux[k] == 2 && k != i)
					{
						if (numero_rep[i] > numero_rep[k])
						{
							jugada = jugada + numero_rep[i] * 0.0001;
						}
					}
					else
						k++;
				} while (k < 3);
			}
		}

	}
	else if (color == true && escalera_color == false)
	{
		jugada = 5;
		k = 1;
		for (int i = 0; i < 3; i++)
		{
			if (palo_aux[i] == 5)
			{
				for (int j = 0; i < 7; i++)
				{
					if (c[j].getPalo() == palo_rep[i])
					{
						jugada = jugada + c[j].getNumero() * (10 ^ -k);
						k++;
					}
				}
			}
		}
	}
	else if (escalera == true && color == false)
	{
		jugada = 4;
		encontrada = false;
		k = 0;
		do
		{
			if (c[k].getNumero() == (c[k + 1].getNumero() - 1) && c[k].getNumero() == (c[k + 2].getNumero() - 2))
			{
				jugada = jugada + c[k].getNumero() * .01;
				encontrada = true;
			}
			else
				k++;
		} while (encontrada == false);

	}
	else if (trio == true)
	{
		jugada = 3;

		if (segundo_trio == true)
		{
			if (numero_rep[0] > numero_rep[1])
			{
				jugada = jugada + numero_rep[0] * 0.01;
			}
			else
			{
				jugada = jugada + numero_rep[1] * 0.01;
			}
		}

	}
	else if (pareja == true && segunda_pareja == true) // doble pareja
	{
		jugada = 2;

		if (tercera_pareja == true)
		{
			int alta = 0, baja = 0;
			if (numero_rep[0] > numero_rep[1])
			{
				alta = numero_rep[0];
				baja = numero_rep[1];
			}
			else
			{
				alta = numero_rep[1];
				baja = numero_rep[0];
			}

			if (numero_rep[2] > alta)
			{
				jugada = jugada + numero_rep[2] * 0.01 + alta * 0.0001;
			}
			else
			{
				if (numero_rep[2] > baja)
					jugada = jugada + alta * 0.01 + numero_rep[2] * 0.0001;
				else
					jugada = jugada + alta * 0.01 + baja * 0.0001;
			}

		}
		else if (tercera_pareja == false)
		{
			if (numero_rep[0] > numero_rep[1])
			{
				jugada = jugada + numero_rep[0] * 0.01 + numero_rep[1] * 0.0001;
			}
			else
			{
				jugada = jugada + numero_rep[1] * 0.01 + numero_rep[0] * 0.0001;
			}
		}
	}
	else if (pareja == true && segunda_pareja == false)
	{
		jugada = 1;

		jugada = jugada + numero_rep[0] * 0.01;
	}
	else
	{
		jugada = 0;

		for (int i = 0; i < 5; i++)
		{
			jugada = jugada + (c[i].getNumero() * 10 ^ -(i + 1));
		}
	}

	valor_mano=jugada;
}

carta* jugador::getMano()
{
	return mano;
}

float jugador::getDinero()
{
	return dinero;
}

float jugador::getValor()
{
	return valor_mano;
}

void jugador::setApuesta(float ap)
{
	apuesta =  ap;
	setDinero(dinero - ap);
}

float jugador::getApuesta()
{
	return apuesta;
}

void jugador::imprimeMano()

{
	mano[0].imprimeCarta();
	mano[1].imprimeCarta();

}