#include "jugador.h"
#include "carta.h"
#include <math.h>

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


//void jugador::calcularValorJugada(carta* c)
//{
//	float jugada = 0.0;
//	int numero_rep[3] = { 0,0,0 };
//	int aux = 0;
//	int palo_rep[3]{ 0,0,0 };
//	int num_aux[3] = { 1,1,1 }, palo_aux[3] = { 1,1,1 };
//	int n_rep = 0, p_rep = 0;
//	int k = 0;
//	bool escalera = false, color = false, segunda_pareja = false, trio = false, pareja = false, poker = false, tercera_pareja = false, segundo_trio = false, escalera_color = false, escalera_real = false;
//
//	for (int i = 0; i < 6; i++)
//	{
//		int j = i + 1;
//		for (j; j < 7; j++)
//		{
//			if (c[i].getNumero() == c[j].getNumero())
//			{
//				k = 0;
//				do {
//					aux = c[i].getNumero();
//					if (c[i].getNumero() == numero_rep[k])
//					{
//						num_aux[k]++;
//					}
//					else if (numero_rep[k] == 0)
//					{
//						numero_rep[k] = c[i].getNumero();
//						num_aux[k]++;
//					}
//					k++;
//				} while (numero_rep[k] != aux);
//
//			}
//			else if (c[i].getPalo() == c[j].getPalo())
//			{
//				k = 0;
//				do {
//					if (c[i].getPalo() == palo_rep[k])
//					{
//						palo_aux[k]++;
//					}
//					else if (palo_rep[k] == 0)
//					{
//						palo_rep[k] = c[i].getPalo();
//						palo_aux[k]++;
//					}
//					k++;
//				} while (palo_rep[k] != c[i].getPalo());
//
//			}
//		}
//
//	}
//	k = 0;
//	do {
//		if (num_aux[k] == 4)
//		{
//			poker = true;
//
//		}
//		else if (num_aux[k] == 3)
//		{
//			if (trio == true)
//			{
//				segundo_trio = true;
//			}
//			else
//			{
//				trio = true;
//			}
//		}
//		else if (num_aux[k] == 2)
//		{
//			if (pareja == true)
//			{
//				if (segunda_pareja == true)
//				{
//					tercera_pareja = true;
//				}
//				else
//				{
//					segunda_pareja = true;
//				}
//			}
//			else
//			{
//				pareja = true;
//			}
//		}
//	} while (num_aux[k] != 1);
//
//	k = 0;
//	do {
//		if (palo_aux[k] == 5)
//		{
//			color = true;
//		}
//	} while (palo_aux[k] != 1);
//
//	bool escalera_imposible = false;
//	int conteo_n_ok = 0, conteo_imp = 0, conteo_palo = 0;
//	for (int i = 0; i < 6; i++)
//	{
//		if (c[i].getNumero() == (c[i + 1].getNumero() - 1))
//		{
//			conteo_n_ok++;
//			if (c[i].getPalo() == c[i + 1].getPalo())
//			{
//				conteo_palo++;
//			}
//			else
//			{
//				conteo_palo = 0;
//			}
//		}
//		else
//		{
//			conteo_n_ok = 0;
//			conteo_imp++;
//			if (conteo_imp == 3)
//			{
//				escalera_imposible = true;
//			}
//		}
//		if (conteo_n_ok == 5)
//		{
//			escalera = true;
//			if (conteo_palo == 5)
//			{
//				escalera_color = true;
//				if (c[i].getNumero() == 10)
//				{
//					escalera_real = true;
//				}
//			}
//
//		}
//		if (c[0].getNumero() == 13)
//		{
//			if (c[3].getNumero() == 5 && c[4].getNumero() == 4 && c[5].getNumero() == 3 && c[6].getNumero() == 2)
//			{
//				escalera = true;
//			}
//		}
//	}
//	bool encontrada = false;
//	if (escalera_real == true)
//		jugada = 9;
//	else if (escalera_color == true)
//	{
//		jugada = 8;
//		for (int i = 0; i < 3; i++)
//		{
//			if (palo_aux[i] == 5)
//			{
//				k = 0;
//				do
//				{
//					if (c[k].getPalo() == palo_aux[i])
//					{
//						jugada = jugada + c[k].getNumero() * 0.01;
//						encontrada = true;
//					}
//					else
//						k++;
//				} while (encontrada == false);
//			}
//		}
//
//	}
//	else if (poker == true)
//	{
//		jugada = 7;
//
//		for (int i = 0; i < 3; i++)
//		{
//			if (num_aux[i] == 4)
//			{
//
//				jugada = jugada + numero_rep[i] * 0.01;
//
//			}
//		}
//	}
//	else if (trio == true && pareja == true) //full house
//	{
//		jugada = 6;
//		for (int i = 0; i < 3; i++)
//		{
//			if (num_aux[i] == 3)
//			{
//
//				jugada = jugada + numero_rep[i] * 0.01;
//
//			}
//
//			else if (num_aux[i] == 2 && segunda_pareja == false)
//			{
//				jugada = jugada + numero_rep[i] * 0.0001;
//			}
//			else if (num_aux[i] == 2 && segunda_pareja == true)
//			{
//				k = 0;
//				do {
//					if (num_aux[k] == 2 && k != i)
//					{
//						if (numero_rep[i] > numero_rep[k])
//						{
//							jugada = jugada + numero_rep[i] * 0.0001;
//						}
//					}
//					else
//						k++;
//				} while (k < 3);
//			}
//		}
//
//	}
//	else if (color == true && escalera_color == false)
//	{
//		jugada = 5;
//		k = 1;
//		for (int i = 0; i < 3; i++)
//		{
//			if (palo_aux[i] == 5)
//			{
//				for (int j = 0; i < 7; i++)
//				{
//					if (c[j].getPalo() == palo_rep[i])
//					{
//						jugada = jugada + c[j].getNumero() * (10 ^ -k);
//						k++;
//					}
//				}
//			}
//		}
//	}
//	else if (escalera == true && color == false)
//	{
//		jugada = 4;
//		encontrada = false;
//		k = 0;
//		do
//		{
//			if (c[k].getNumero() == (c[k + 1].getNumero() - 1) && c[k].getNumero() == (c[k + 2].getNumero() - 2))
//			{
//				jugada = jugada + c[k].getNumero() * .01;
//				encontrada = true;
//			}
//			else
//				k++;
//		} while (encontrada == false);
//
//	}
//	else if (trio == true)
//	{
//		jugada = 3;
//
//		if (segundo_trio == true)
//		{
//			if (numero_rep[0] > numero_rep[1])
//			{
//				jugada = jugada + numero_rep[0] * 0.01;
//			}
//			else
//			{
//				jugada = jugada + numero_rep[1] * 0.01;
//			}
//		}
//
//	}
//	else if (pareja == true && segunda_pareja == true) // doble pareja
//	{
//		jugada = 2;
//
//		if (tercera_pareja == true)
//		{
//			int alta = 0, baja = 0;
//			if (numero_rep[0] > numero_rep[1])
//			{
//				alta = numero_rep[0];
//				baja = numero_rep[1];
//			}
//			else
//			{
//				alta = numero_rep[1];
//				baja = numero_rep[0];
//			}
//
//			if (numero_rep[2] > alta)
//			{
//				jugada = jugada + numero_rep[2] * 0.01 + alta * 0.0001;
//			}
//			else
//			{
//				if (numero_rep[2] > baja)
//					jugada = jugada + alta * 0.01 + numero_rep[2] * 0.0001;
//				else
//					jugada = jugada + alta * 0.01 + baja * 0.0001;
//			}
//
//		}
//		else if (tercera_pareja == false)
//		{
//			if (numero_rep[0] > numero_rep[1])
//			{
//				jugada = jugada + numero_rep[0] * 0.01 + numero_rep[1] * 0.0001;
//			}
//			else
//			{
//				jugada = jugada + numero_rep[1] * 0.01 + numero_rep[0] * 0.0001;
//			}
//		}
//	}
//	else if (pareja == true && segunda_pareja == false)
//	{
//		jugada = 1;
//
//		jugada = jugada + numero_rep[0] * 0.01;
//	}
//	else
//	{
//		jugada = 0;
//
//		for (int i = 0; i < 5; i++)
//		{
//			jugada = jugada + (c[i].getNumero() * 10 ^ -(i + 1));
//		}
//	}
//
//	valor_mano=jugada;
//}

void jugador::resetear_bool() {

	Escalera_Real_posible = true;
	poker_posible = true;
	escalera_color_posible = true;
	full_posible = true;
	escalera_posible = true;
	color_posible = true;
	trio_posible = true;
	doble_pareja_posible = true;
	pareja_posible = true;
}
void jugador::ValorManoInicial() { // Chen formula
	double aux = 0;
	int c_alta = 0, gap=-1;
	
	if (mano[0].getNumero()==1 || mano[1].getNumero()==1)
	{
		c_alta = 14;
		if (mano[0].getNumero() == 1 && mano[1].getNumero() == 1)
		{
			gap = 0;
		}
		else {
			if (mano[0].getNumero() == 1)
			{
				gap = 14 - mano[1].getNumero();
			}
			else
			{
				gap = 14 - mano[0].getNumero();
			}
		}
	}
	else if (mano[0].getNumero() > mano[1].getNumero())
	{
		c_alta = mano[0].getNumero();
		gap = mano[0].getNumero() - mano[1].getNumero();
	}
	else if (mano[0].getNumero() < mano[1].getNumero())
	{
		c_alta = mano[1].getNumero();
		gap = mano[1].getNumero() - mano[0].getNumero();
	}

	else
	{
		c_alta = mano[0].getNumero();
		gap = 0;
	}

	if (c_alta == 14)
	{
		aux = 10;
	}
	else if (c_alta == 13)
	{
		aux = 8;
	}
	else if (c_alta == 12)
	{
		aux = 7;
	}
	else if (c_alta == 11)
	{
		aux = 6;
	}
	else
	{
		aux = c_alta / 2;
	}


	if (gap == 0)
	{
		aux = aux * 2;
		if (c_alta > 11)
		{
			aux++;
		}
	}
	else if (gap == 1)
	{
		aux = aux - gap;
		if (c_alta > 11)
		{
			aux++;
		}
	}
	else if (gap == 2)
	{
		aux = aux - gap;
	}
	else if (gap == 3)
	{
		aux = aux - 4;
	}
	else
	{
		aux = aux - 5;
	}

	if (mano[0].getPalo() == mano[1].getPalo())
	{
		aux = aux +2;
	}

	aux = roundf(aux);

	valor_mano = aux;
}
void jugador::ValorManoR1(carta* c) {
	
	carta* jugada = new carta[5];
	
	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = c[0];
	jugada[3] = c[1];
	jugada[4] = c[2];
	carta aux;
	int rep_max_n = 1;
	int n_reps = 0;
	int num_rep = 0;
	int rep_max_p = 1;
	int p_reps = 0;
	int pal_rep = 0;
	bool escalera = true;
	bool color = false;
	int gap_max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i+1; k < 5; k++)
		{
			if (jugada[k].getNumero() == 1)
			{
				jugada[k].setNumero(14);
			}

			if (jugada[i].getNumero() < jugada[k].getNumero())
			{
				aux = jugada[i];
				jugada[i] =jugada[k];
				jugada[k] = aux;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		mejor_jugada[i] = jugada[i];
	}

	for (int i = 0; i < 4; i++)
	{
		for (int k = i + 1; k < 5; k++)
		{
			if (mejor_jugada[i].getNumero() == mejor_jugada[k].getNumero())
			{
				if (mejor_jugada[i].getNumero() == num_rep)
				{
					rep_max_n++;
				}
				else
				{
					num_rep = mejor_jugada[i].getNumero();
					n_reps++;

				}


			}
			else if (jugada[i].getPalo() == jugada[k].getPalo())
			{
				if (mejor_jugada[i].getPalo() == pal_rep)
				{
					rep_max_p++;
				}
				else
				{
					pal_rep = mejor_jugada[i].getPalo();
					p_reps++;

				}
			}
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		int gap = 0;
		gap = mejor_jugada[i].getNumero() - mejor_jugada[i + 1].getNumero();
		if (gap != 1)
		{
			if (escalera == true)
			{
				escalera = false;
			}
		}
		if (gap > gap_max)
		{
			gap_max = gap;
		}
	}

	
	//jugadas imposibles genericas
	if (rep_max_n == 1)
	{
		poker_posible = false;
		full_posible = false;
	}
	if (rep_max_p <= 2)
	{
		escalera_color_posible = false;
		Escalera_Real_posible = false;
		color_posible = false;
	}
	else if (rep_max_p == 5)
	{
		color = true;
	}

	// jugadas imposibles condicionales y jugadas peores

	if (rep_max_n == 4)
	{
		 Escalera_Real_posible=false;
		 escalera_color_posible = false;
		 full_posible = false;
		 escalera_posible = false;
		 color_posible = false;
		 trio_posible = false;
		 doble_pareja_posible = false;
		 pareja_posible = false;
		 valor_mano = 7 + (mejor_jugada[0].getNumero() * 0.01);
	}
	else if (rep_max_n == 3)
	{
		doble_pareja_posible = false;
		pareja_posible = false;
		if (gap_max > 4)
		{
			Escalera_Real_posible = false;
			escalera_color_posible = false;
			escalera_posible = false;
		}
		if (rep_max_p == 2)
		{
			color_posible = false;
		}
		if (n_reps == 2)
		{
			Escalera_Real_posible = false;
			escalera_color_posible = false;
			escalera_posible = false;
			color_posible = false;
			trio_posible = false;
			doble_pareja_posible = false;
			pareja_posible = false;
			valor_mano = 6 + (mejor_jugada[0].getNumero() * 0.01)+ (mejor_jugada[3].getNumero() * 0.0001);
		}
		else
		{
			valor_mano = 3 + (mejor_jugada[0].getNumero() * 0.01) + (mejor_jugada[3].getNumero() * 0.0001) + (mejor_jugada[4].getNumero() * 0.000001);
		}

	}
	else if (rep_max_n==2)
	{
		if (n_reps == 2)
		{
			pareja_posible = false;
			valor_mano = 2
		}
	}

	
}
void jugador::ValorManoR2(carta* c) {}
void jugador::ValorManoR3(carta* c) {}

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