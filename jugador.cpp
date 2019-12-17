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
	Escalera_Real_obtenida = false;
	poker_obtenida = false;
	escalera_color_obtenida = false;
	full_obtenida = false;
	escalera_obtenida = false;
	color_obtenida = false;
	trio_obtenida = false;
	doble_pareja_obtenida = false;
	pareja_obtenida = false;
}
void jugador::ValorManoInicial() { // Chen formula
	float aux = 0;
	float c_alta = 0, gap = -1;

	if (mano[0].getNumero() == 1 || mano[1].getNumero() == 1)
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
		aux = aux ;
		if (c_alta > 11)
		{
			aux++;
		}
	}
	else if (gap == 2)
	{
		aux = aux - 1;
	}
	else if (gap == 3)
	{
		aux = aux - 2;
	}
	else if (gap == 4)
	{
		aux = aux - 4;
	}
	else
	{
		aux = aux - 5;
	}

	if (mano[0].getPalo() == mano[1].getPalo())
	{
		aux = aux + 2;
	}

	aux = roundf(aux);

	valor_mano = aux;
	valorNumericoMano();
}
void jugador::ValorManoR1(carta* c) {

	carta* jugada = new carta[5];

	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = c[0];
	jugada[3] = c[1];
	jugada[4] = c[2];
	carta aux;

	for (int i = 0; i < 4; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i + 1; k < 5; k++)
		{
			if (jugada[k].getNumero() == 1)
			{
				jugada[k].setNumero(14);
			}

			if (jugada[i].getNumero() < jugada[k].getNumero())
			{
				aux = jugada[i];
				jugada[i] = jugada[k];
				jugada[k] = aux;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		mejor_jugada[i] = jugada[i];
	}

	valor_mano = calcularValorJugada(mejor_jugada);

}
void jugador::ValorManoR2(carta* c) {
	carta* jugada = new carta[6];
	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = c[0];
	jugada[3] = c[1];
	jugada[4] = c[2];
	jugada[5] = c[3];
	carta aux;

	for (int i = 0; i < 4; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i + 1; k < 5; k++)
		{
			if (jugada[k].getNumero() == 1)
			{
				jugada[k].setNumero(14);
			}

			if (jugada[i].getNumero() < jugada[k].getNumero())
			{
				aux = jugada[i];
				jugada[i] = jugada[k];
				jugada[k] = aux;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		mejor_jugada[i] = jugada[i];
	}

	valor_mano = calcularValorJugada(mejor_jugada);

}
void jugador::ValorManoR3(carta* c) {
	carta* jugada = new carta[7];
	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = c[0];
	jugada[3] = c[1];
	jugada[4] = c[2];
	jugada[5] = c[3];
	jugada[6] = c[4];
	carta aux;

	for (int i = 0; i < 4; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i + 1; k < 5; k++)
		{
			if (jugada[k].getNumero() == 1)
			{
				jugada[k].setNumero(14);
			}

			if (jugada[i].getNumero() < jugada[k].getNumero())
			{
				aux = jugada[i];
				jugada[i] = jugada[k];
				jugada[k] = aux;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		mejor_jugada[i] = jugada[i];
	}

	valor_mano = calcularValorJugada(mejor_jugada);

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
	
	float diferencia = ap - apuesta;
	apuesta = ap;
	setDinero(dinero - diferencia);
}

void jugador::resetApuesta()
{
	apuesta = 0;
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


float jugador::calcularValorJugada(carta* c)
{
	float jugada = 0;
	int tamano = sizeof(c);
	int n_rep_n = 0;
	int n_rep_p = 0;
	int n_rep[3] = { 0,0,0 };
	int p_rep[3] = { 0,0,0 };
	int n_aparicion[3] = { 1,1,1 };
	int p_aparicion[3] = { 1,1,1 };
	int k = 0;
	int seguidos = 1;

	for (int i = 0; i < tamano - 1; i++)
	{
		for (int j = i + 1; j < tamano; j++)
		{
			if (c[i].getNumero() == c[j].getNumero())
			{
				if (n_rep_n == 0)
				{
					n_rep_n++;
					n_rep[0] = c[i].getNumero();
					n_aparicion[0] = 2;
				}
				else
				{
					for (int l = 0; l <= n_rep_n; l++)
					{
						if (c[i].getNumero() == n_rep[l])
						{
							n_aparicion[l]++;
						}
						else if (n_rep[l] == 0)
						{
							n_rep_n++;
							n_rep[l] = c[i].getNumero();
							n_aparicion[l] = 2;
						}
					}
				}
			}
			else if (c[i].getPalo() == c[j].getPalo())
			{
				if (n_rep_p == 0)
				{
					n_rep_p++;
					p_rep[0] = c[i].getPalo();
					p_aparicion[0] = 2;
				}
				else
				{
					for (int l = 0; l <= n_rep_p; l++)
					{
						if (c[i].getPalo() == p_rep[l])
						{
							p_aparicion[l]++;
						}
						else if (p_rep[l] == 0)
						{
							n_rep_p++;
							p_rep[l] = c[i].getPalo();
							p_aparicion[l] = 2;
						}
					}
				}
			}
		}

		if (c[i].getNumero() == c[i + 1].getNumero() + 1)
		{
			seguidos++;
		}
		else
		{
			if (seguidos < 5)
			{
				seguidos = 1;
			}
		}


	}
	//eliminación de jugadas posibles
	if (tamano == 5)
	{
		if (n_rep_n == 0)
		{
			poker_posible = false;
			full_posible = false;
		}

		if (n_rep_p == 2)
		{
			color_posible = false;
			escalera_color_posible = false;
			Escalera_Real_posible = false;
		}
	}
	else if (tamano == 6)
	{
		if (n_rep_n == 0)
		{
			poker_posible = false;
			full_posible = false;
			trio_posible = false;
			doble_pareja_posible = false;
		}
		else if (n_rep_n == 1)
		{
			if (n_aparicion[0] == 2)
			{
				poker_posible = false;
				full_posible = false;
			}

		}
		else if (n_rep_n == 2)
		{
			if (n_aparicion[0] == 2 && n_aparicion[1] == 2)
			{
				poker_posible = false;
			}
		}
		else if (n_rep_n == 3)
		{
			poker_posible = false;
		}

		if (n_rep_p >= 2)
		{
			color_posible = false;
			escalera_color_posible = false;
			Escalera_Real_posible = false;
		}
		else if (n_rep_p == 1 && p_aparicion[0] < 4)
		{
			color_posible = false;
			escalera_color_posible = false;
			Escalera_Real_posible = false;
		}
	}
	else if (tamano == 7)
	{
		if (seguidos < 5)
		{
			escalera_color_posible = false;
			escalera_posible = false;
			Escalera_Real_posible = false;
		}
		if (n_rep_n == 0)
		{
			pareja_posible = false;
			doble_pareja_posible = false;
			trio_posible = false;
			full_posible = false;
			poker_posible = false;
		}
		else if (n_rep_n == 1)
		{
			doble_pareja_posible = false;
			full_posible = false;
			if (n_aparicion[0] == 2)
			{
				trio_posible = false;
				full_posible = false;
				poker_posible = false;
			}
			else if (n_aparicion[0] == 3)
			{
				poker_posible = false;
			}
		}
		else if (n_rep_n == 3)
		{
			poker_posible = false;
		}

		if (n_rep_p == 3)
		{
			color_posible = false;
			escalera_color_posible = false;
			Escalera_Real_posible = false;
		}
		else
		{
			if (p_aparicion[0] < 5 || p_aparicion[1] < 5)
			{
				color_posible = false;
				escalera_color_posible = false;
				Escalera_Real_posible = false;
			}
		}
	}
	//mejor jugada actual
	int carta_poker = 0;
	int carta_trio = 0;
	int carta_pareja = 0;
	int c_alta_escalera = 0;
	int palo_color = 0;
	int c_c[5] = { 0,0,0,0,0 };
	int c_alta_doble = 0, c_baja_doble = 0;
	int k_c = 0, k_e = 0, c_aux = 0;
	int gap_aux = 0;
	int escalera[5] = { 0,0,0,0,0 };
	int escalera_real[5] = { 14,13,12,11,10 };
	int conteo = 0, conteo_real = 0;

	if (n_rep_n == 1)
	{
		pareja_obtenida = true;
		if (n_aparicion[0] == 2)
		{
			carta_pareja = n_rep[0];
		}
		else if (n_aparicion[0] == 3)
		{
			trio_obtenida = true;
			carta_trio = n_rep[0];
		}
		else if (n_aparicion[0] == 4)
		{
			poker_obtenida = true;
			carta_poker = n_rep[0];
		}
	}
	else if (n_rep_n == 2)
	{
		doble_pareja_obtenida = true;
		{
			if (n_aparicion[0] == 2 && n_aparicion[1] == 2)
			{
				if (n_rep[0] > n_rep[1])
				{
					c_alta_doble = n_rep[0];
					c_baja_doble = n_rep[1];
				}
				else
				{
					c_alta_doble = n_rep[0];
					c_baja_doble = n_rep[1];
				}
			}
			else if (n_aparicion[0] == 3 && n_aparicion[1] == 2)
			{
				full_obtenida = true;
				carta_trio = n_rep[0];
				carta_pareja = n_rep[1];
			}
			else if (n_aparicion[0] == 2 && n_aparicion[1] == 3)
			{
				full_obtenida = true;
				carta_trio = n_rep[1];
				carta_pareja = n_rep[0];
			}
			else if (n_aparicion[0] == 3 && n_aparicion[1] == 3)
			{
				full_obtenida = true;
				if (n_rep[0] > n_rep[1])
				{
					carta_trio = n_rep[0];
					carta_pareja = n_rep[1];
				}
				else
				{
					carta_trio = n_rep[1];
					carta_pareja = n_rep[0];
				}

			}
			else if (n_aparicion[0] == 4 || n_aparicion[1] == 4)
			{
				poker_obtenida = true;
				if (n_aparicion[0] == 4)
				{
					carta_poker = n_rep[0];
				}
				else
				{
					carta_poker = n_rep[1];
				}
			}

		}
	}
	else if (n_rep_n == 3)
	{
		doble_pareja_obtenida = true;
		if (n_aparicion[0] == 3 || n_aparicion[1] == 3 || n_aparicion[2] == 3)
		{
			full_obtenida = true;
			for (int i = 0; i < 3; i++)
			{
				if (n_aparicion[i] == 3)
				{
					carta_trio = n_rep[i];
				}
				else
				{
					if (carta_pareja == 0)
					{
						carta_pareja = n_rep[i];
					}
					else
					{
						if (n_rep[i] > carta_pareja)
						{
							carta_pareja = n_rep[i];
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				if (c_alta_doble == 0)
				{
					c_alta_doble = n_rep[i];
				}
				else
				{
					if (n_rep[i] > c_alta_doble)
					{
						c_baja_doble = c_alta_doble;
						c_alta_doble = n_rep[i];
					}
					else if (n_rep[i] > c_baja_doble)
					{
						c_baja_doble = n_rep[i];
					}
				}
			}
		}
	}

	for (int i = 0; i < n_rep_p; i++)
	{
		if (p_aparicion[i] == 5)
		{
			color_obtenida = true;
			palo_color = p_rep[i];
		}
	}
	if (color_obtenida == true)
	{
		for (int i = 0; i < tamano; i++)
		{
			if (c[i].getPalo() == palo_color)
			{
				c_c[k_c] = c[i].getNumero();
				k_c++;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 5; j++)
			{
				if (c_c[i] < c_c[j])
				{
					c_aux = c_c[i];
					c_c[i] = c_c[j];
					c_c[j] = c_aux;
				}
			}
		}
	}

	if (seguidos == 5)
	{
		escalera_obtenida = true;
		for (int i = 0; i < tamano - 1; i++)
		{
			gap_aux = (c[i].getNumero() - c[i + 1].getNumero());
			if (gap_aux == 1 && k_e < 4)
			{
				escalera[k_e] = c[i].getNumero();
				escalera[k_e + 1] = c[i + 1].getNumero();
				k_e++;
			}
			else
			{
				if (k_e != 4)
				{
					for (int k = 0; k < 5; k++)
					{
						escalera[k] = 0;
					}
					k_e = 0;
				}
			}
		}
		c_alta_escalera = escalera[0];
	}

	if (escalera_obtenida == true && color_obtenida == true)
	{
		for (int i = 0; i < 5; i++)
		{
			if (c_c[i] == escalera[i])
			{
				conteo++;
			}
		}
		if (conteo == 5)
		{
			escalera_color_obtenida = true;
		}
	}

	if (escalera_color_obtenida == true)
	{
		for (int i = 0; i < 5; i++)
		{
			if (escalera[i] == escalera_real[i])
			{
				conteo_real++;
			}
		}
		if (conteo_real == 5)
		{
			Escalera_Real_obtenida = true;
		}
	}



	//calculo de valor de jugada
	if (Escalera_Real_obtenida == true)
	{
		jugada = 9 + valor_num_mano;
	}
	else if (escalera_color_obtenida == true)
	{
		jugada = 8 + c_alta_escalera * 0.01 + valor_num_mano * 0.01;
	}
	else if (poker_obtenida == true)
	{
		jugada = 7 + carta_poker * 0.01 + valor_num_mano * 0.01;
	}
	else if (full_obtenida == true)
	{
		jugada = 6 + carta_trio * 0.01 + carta_pareja * 0.0001 + valor_num_mano * 0.0001;
	}
	else if (color_obtenida == true)
	{
		jugada = 5 + c_c[0] * 0.01 + c_c[1] * 0.0001 + c_c[2] * 0.000001 + c_c[3] * 0.00000001 + c_c[4] * 0.0000000001 + valor_num_mano * 0.0000000001;
	}
	else if (escalera_obtenida == true)
	{
		jugada = 4 + c_alta_escalera * 0.01 + valor_num_mano * 0.01;
	}
	else if (trio_obtenida == true)
	{
		jugada = 3 + carta_trio * 0.01 + valor_num_mano * 0.01;
	}
	else if (doble_pareja_obtenida == true)
	{
		jugada = 2 + c_alta_doble * 0.01 + c_baja_doble * 0.0001 + valor_num_mano * 0.0001;
	}
	else if (pareja_obtenida == true)
	{
		jugada = 1 + carta_pareja * 0.01 + valor_num_mano * 0.01;
	}
	else
	{
		jugada = 0 + valor_num_mano;
	}

	return jugada;
}





void jugador::valorNumericoMano() {
	int c_alta = 0;
	int c_baja = 0;

	if (mano[0].getNumero() == mano[1].getNumero())
	{
		c_alta = mano[0].getNumero();
		c_baja = mano[0].getNumero();
	}
	if (mano[0].getNumero() == 1)
	{
		c_alta = 14;
		c_baja = mano[1].getNumero();
	}
	else if (mano[1].getNumero() == 1)
	{
		c_alta = 14;
		c_baja = mano[0].getNumero();
	}
	else {
		if (mano[0].getNumero() > mano[1].getNumero())
		{
			c_alta = mano[0].getNumero();
			c_baja = mano[1].getNumero();
		}
		else
		{
			c_alta = mano[1].getNumero();
			c_baja = mano[0].getNumero();
		}
	}
	valor_num_mano = c_alta * 0.01 + c_baja * 0.0001;
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

//int rep_max_n = 1;
	//int n_reps = 0;
	//int num_rep = 0;
	//int rep_max_p = 1;
	//int p_reps = 0;
	//int pal_rep = 0;
	//bool escalera = true;
	//bool color = false;
	//int gap_max = 0;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int k = i + 1; k < 5; k++)
	//	{
	//		if (mejor_jugada[i].getNumero() == mejor_jugada[k].getNumero())
	//		{
	//			if (mejor_jugada[i].getNumero() == num_rep)
	//			{
	//				rep_max_n++;
	//			}
	//			else
	//			{
	//				num_rep = mejor_jugada[i].getNumero();
	//				n_reps++;

	//			}


	//		}
	//		else if (jugada[i].getPalo() == jugada[k].getPalo())
	//		{
	//			if (mejor_jugada[i].getPalo() == pal_rep)
	//			{
	//				rep_max_p++;
	//			}
	//			else
	//			{
	//				pal_rep = mejor_jugada[i].getPalo();
	//				p_reps++;

	//			}
	//		}
	//	}
	//}
	//
	//for (int i = 0; i < 4; i++)
	//{
	//	int gap = 0;
	//	gap = mejor_jugada[i].getNumero() - mejor_jugada[i + 1].getNumero();
	//	if (gap != 1)
	//	{
	//		if (escalera == true)
	//		{
	//			escalera = false;
	//		}
	//	}
	//	if (gap > gap_max)
	//	{
	//		gap_max = gap;
	//	}
	//}

	//
	////jugadas imposibles genericas
	//if (rep_max_n == 1)
	//{
	//	poker_posible = false;
	//	full_posible = false;
	//}
	//if (rep_max_p <= 2)
	//{
	//	escalera_color_posible = false;
	//	Escalera_Real_posible = false;
	//	color_posible = false;
	//}
	//else if (rep_max_p == 5)
	//{
	//	color = true;
	//}

	//// jugadas imposibles condicionales y jugadas peores

	//if (rep_max_n == 4)
	//{
	//	 Escalera_Real_posible=false;
	//	 escalera_color_posible = false;
	//	 full_posible = false;
	//	 escalera_posible = false;
	//	 color_posible = false;
	//	 trio_posible = false;
	//	 doble_pareja_posible = false;
	//	 pareja_posible = false;
	//	 valor_mano = 7 + (mejor_jugada[1].getNumero() * 0.01);
	//}
	//else if (rep_max_n == 3)
	//{
	//	doble_pareja_posible = false;
	//	pareja_posible = false;
	//	if (gap_max > 4)
	//	{
	//		Escalera_Real_posible = false;
	//		escalera_color_posible = false;
	//		escalera_posible = false;
	//	}
	//	if (rep_max_p == 2)
	//	{
	//		color_posible = false;
	//	}
	//	if (n_reps == 2)
	//	{
	//		Escalera_Real_posible = false;
	//		escalera_color_posible = false;
	//		escalera_posible = false;
	//		color_posible = false;
	//		trio_posible = false;
	//		doble_pareja_posible = false;
	//		pareja_posible = false;
	//		valor_mano = 6 + (mejor_jugada[0].getNumero() * 0.01)+ (mejor_jugada[3].getNumero() * 0.0001);
	//	}
	//	else
	//	{
	//		//corregir, no es correcto ni garantizado que ese sea el orden
	//		valor_mano = 3 + (mejor_jugada[0].getNumero() * 0.01) + (mejor_jugada[3].getNumero() * 0.0001) + (mejor_jugada[4].getNumero() * 0.000001);
	//	}

	//}
	//else if (rep_max_n==2)
	//{ 
	//	if (n_reps == 2)
	//	{
	//		pareja_posible = false;
	//		int valor1 = 0, valor2 = 0, valorn=0;
	//		for (int i = 0; i < 4; i++)
	//		{
	//			if (mejor_jugada[i].getNumero() == mejor_jugada[i + 1].getNumero())
	//			{
	//				if (valor1 == 0)
	//				{
	//					valor1 = mejor_jugada[i].getNumero();
	//				}
	//				else
	//				{
	//					valor2 = mejor_jugada[i].getNumero();
	//				}
	//			}
	//			else
	//			{
	//				if (mejor_jugada[i].getNumero() != valor1 || mejor_jugada[i].getNumero() != valor1)
	//				{
	//					valorn = mejor_jugada[i].getNumero();
	//				}
	//			}
	//		}
	//		valor_mano = 2 + valor1 * 0.01 + valor2 * 0.0001 + valorn * 0.000001;
	//		
	//	}
	//	else
	//	{
	//		int valorn[3] = { 0,0,0 };
	//		int valorp = 0, k=0;

	//		for (int i = 0; i < 4; i++)
	//		{

	//		}
	//	}
	//}

	//