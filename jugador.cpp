#include "jugador.h"
#include "carta.h"
#include <math.h>
#include <iostream>

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
void jugador::ValorManoR1(Mesa T) {

	carta* jugada = new carta[5];

	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = T.Tablero[0];
	jugada[3] = T.Tablero[1];
	jugada[4] = T.Tablero[2];

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

	for (int i = 0; i<5; i++)
	{
		jugada[i].imprimeCarta();
	}
	valor_mano = calcularValorJugada(jugada,5);

}
void jugador::ValorManoR2(Mesa T) {
	carta* jugada = new carta[6];
	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = T.Tablero[0];
	jugada[3] = T.Tablero[1];
	jugada[4] = T.Tablero[2];
	jugada[5] = T.Tablero[3];
	carta aux;

	for (int i = 0; i < 5; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i + 1; k < 6; k++)
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

	for (int i = 0; i < 6; i++)
	{
		mejor_jugada[i] = jugada[i];
	}

	for (int i = 0; i < 6; i++)
	{
		jugada[i].imprimeCarta();
	}
	valor_mano = calcularValorJugada(jugada,6);

}
void jugador::ValorManoR3(Mesa T) {
	carta* jugada = new carta[7];
	jugada[0] = mano[0];
	jugada[1] = mano[1];
	jugada[2] = T.Tablero[0];
	jugada[3] = T.Tablero[1];
	jugada[4] = T.Tablero[2];
	jugada[5] = T.Tablero[3];
	jugada[6] = T.Tablero[4];
	carta aux;

	for (int i = 0; i < 6; i++)
	{
		if (jugada[i].getNumero() == 1)
		{
			jugada[i].setNumero(14);
		}
		for (int k = i + 1; k < 7; k++)
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

	
	for (int i = 0; i < 7; i++)
	{
		jugada[i].imprimeCarta();
	}

	valor_mano = calcularValorJugada(jugada,7);

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

void jugador::reseteo_obtenidas()
{
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


float jugador::calcularValorJugada(carta* c, int i)
{
	float jugada = 0;
	int tamano = 0;
	int palos[4] = { 1,2,3,4 };
	int n_palos[4] = { 0,0,0,0 };
	int n_rep_n = 0;
	int n_rep_p = 0;
	int p_max = 1;
	int n_rep[3] = { 0,0,0 };
	//int p_rep[3] = { 0,0,0 };
	int n_aparicion[3] = { 1,1,1 };
	//int p_aparicion[3] = { 1,1,1 };
	int k = 0;
	int seguidos = 1;
	bool up = false;
	tamano = i;

	if (tamano == 7)
	{
		c[0].setNumero(14);
		c[1].setNumero(13);
		c[2].setNumero(12);
		c[3].setNumero(11);
		c[4].setNumero(10);
		c[5].setNumero(9);
		c[6].setNumero(5);
		c[0].setPalo(4);
		c[1].setPalo(1);
		c[2].setPalo(1);
		c[3].setPalo(1);
		c[4].setPalo(1);
		c[5].setPalo(1);
		c[6].setPalo(1);
	}

	

	for (int i = 0; i < tamano - 1; i++)
	{
		if (c[i].getNumero() == c[i + 1].getNumero())
		{
			if (n_rep_n == 0)
			{
				n_rep_n = 1;
				n_rep[0] = c[i].getNumero();
				n_aparicion[0] = 2;
			}
			else
			{
				up = false;
				k = 0;
				do
				{
					if (c[i].getNumero() == n_rep[k])
					{
						n_aparicion[k] = n_aparicion[k] + 1;
						up = true;
					}
					else if (n_rep[k] == 0)
					{
						n_rep_n++;
						n_rep[k] = c[i].getNumero();
						n_aparicion[k] = 2;
						up = true;
					}
					else
						k++;
				} while (up==false);

				
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

	
	for (int i = 0; i < tamano; i++)
	{
		if (c[i].getPalo() == palos[0])
		{
			n_palos[0] = n_palos[0] + 1;
		}
		else if (c[i].getPalo() == palos[1])
		{
			n_palos[1] = n_palos[1] + 1;
		}
		else if (c[i].getPalo() == palos[2])
		{
			n_palos[2] = n_palos[2] + 1;
		}
		else if (c[i].getPalo() == palos[3])
		{
			n_palos[3] = n_palos[3] + 1;
		}
	}

	
	//std::cout << "Palo: " << std::endl;
	//for (int i = 0; i < 3; i++)
	//{
	//	std::cout << "Numero: " << n_rep[i] << std::endl;
	//	std::cout << "Veces: " << n_aparicion[i] << std::endl;
	//}

	//std::cout << "Colores: " << std::endl;

	//for (int i = 0; i < 4; i++)
	//{
	//	std::cout << "Palo: " << palos[i] <<std::endl;
	//	std::cout << "veces: " << n_palos[i] <<std::endl;
	//}

	//std::cout << "Cartas seguidas: " << seguidos << std::endl;

	//eliminación de jugadas posibles
	for (int i = 0; i < 4; i++)
	{
		if (n_palos[i] > 1)
		{
			n_rep_p++;
			if (n_palos[i] > p_max)
			{
				p_max = n_palos[i];
			}
		}
	}


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
		else if (n_rep_p == 1 && p_max < 4)
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
			if (p_max < 5)
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
	int c_c[7] = { 0,0,0,0,0,0,0 };
	int c_alta_doble = 0, c_baja_doble = 0;
	int k_c = 0, k_e = 0, c_aux = 0;
	int gap_aux = 0;
	int escalera[7] = { 0,0,0,0,0,0,0 };
	int escalera_real[5] = { 14,13,12,11,10 };
	int conteo = 0, conteo_real = 0;
	reseteo_obtenidas();

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
			pareja_obtenida = false;
			carta_trio = n_rep[0];
		}
		else if (n_aparicion[0] == 4)
		{
			poker_obtenida = true;
			pareja_obtenida = false;
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
				doble_pareja_obtenida = false;
				carta_trio = n_rep[0];
				carta_pareja = n_rep[1];
			}
			else if (n_aparicion[0] == 2 && n_aparicion[1] == 3)
			{
				full_obtenida = true;
				doble_pareja_obtenida = false;
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

	for (int i = 0; i < 4; i++)
	{
		if (n_palos[i] >= 5)
		{
			color_obtenida = true;
			palo_color = palos[i];
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

	if (seguidos >= 5)
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
	else if (c[0].getNumero() == 14)
	{
		if (c[6].getNumero() == 2 && c[5].getNumero() == 3 && c[4].getNumero() == 4 && c[3].getNumero() == 5)
		{
			escalera_obtenida = true;
			escalera[0] = 14;
			escalera[1] = 5;
			escalera[2] = 4;
			escalera[3] = 3;
			escalera[4] = 2;
		}
	}

	if (escalera_obtenida == true && color_obtenida == true)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int k = 0; k < 7; k++)
			{
				if (c_c[k] == escalera[i])
				{
					if(c_c[k]!=0)
					conteo++;
				}
			}
		}
		if (conteo >= 5)
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

	std::cout << "Escalera real: " << Escalera_Real_obtenida << std::endl;
	std::cout << "poker: "<< poker_obtenida << std::endl;
	std::cout << "escalera_color: " << escalera_color_obtenida << std::endl;
	std::cout << "Full: "<<full_obtenida << std::endl;
	std::cout << "Escalera: "<<escalera_obtenida << std::endl;
	std::cout << "Color: "<<color_obtenida << std::endl;
	std::cout << "Trio: "<<trio_obtenida << std::endl;
	std::cout << "Doble Pareja: "<<doble_pareja_obtenida << std::endl;
	std::cout << "Pareja: "<<pareja_obtenida << std::endl;


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

	std::cout << "valor jugada en función: " << jugada << std::endl;
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

