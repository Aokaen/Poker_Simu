#include "Algoritmo.h"
#include <math.h>
#include <cstdlib>
#include "random.h"
#include <curl/curl.h>
#include <iostream>
#include <rapidjson/document.h>
#include <string>

using namespace std;
struct MemoryStruct {
	char* memory;
	size_t size;
};

static size_t
WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* ptr;
	ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}



int Algoritmo::obtenerAccion(Jugador J, Mesa M)
{
			obtenerTriple(J, M);

			random r;
			float p = 0, v = 0, s = 0, n = 0;
			n = r.nrandomPorcent();
			//n = rand()%(100+1)*0.01;

			p = triple[0];
			v = p + triple[1];
			if (triple[2] != 0)
			{
				s =1;
			}
			else
			{
				s = 0;
			}
			if (n <= p)
			{
				return 0;
			}
			else if (n <= v)
			{
				return 1;
			}
			else
			{
				return 2;
			}
			
	
	

}
void Algoritmo::obtenerTriple(Jugador J, Mesa M)
{
	if (tipo == 4)
	{
		struct MemoryStruct chunk;

		chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
		chunk.size = 0;    /* no data at this point */

		curl_global_init(CURL_GLOBAL_ALL);

		CURL* curl = curl_easy_init();
		CURLcode res;
		rapidjson::Document document;

		Carta* mano_aux = new Carta[2];
		Carta* mesa_aux = new Carta[5];
		mano_aux = J.getMano();
		mesa_aux = M.Tablero;
		for (int i = 0; i < 5; i++)
		{
			if (i < 2)
			{
				if (mano_aux[i].getNumero() == 1)
				{
					mano_aux[i].setNumero(14);
				}
			}
			if (mesa_aux[i].getNumero() == 1)
			{
				mesa_aux[i].setNumero(14);
			}
		}
		

		const char* url = "http://localhost:8000/error";
		string url_aux;

		if (M.getIndiceRonda() == 0)
		{
		/*	strcpy(url_aux, "http://localhost:8000/preflopini?mn1=");
			char* numero = &n1;
			strcat(url_aux,numero);
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mano_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mano_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mano_aux[1].getPalo());
			url = url_aux;*/
			url_aux = "http://localhost:8000/preflopini?mn1=" + to_string(mano_aux[0].getNumero()) + "&mp1=" + to_string(mano_aux[0].getPalo()) + "&mn2=" + to_string(mano_aux[1].getNumero()) + "&mp2=" + to_string(mano_aux[1].getPalo());
			//url = url_aux.c_str();
		}
		else if (M.getIndiceRonda() == 1)
		{
			int aa = J.getApuesta();
			int ao = M.apuesta - aa;
			url_aux = "http://localhost:8000/flopini?mn1=" + to_string(mesa_aux[0].getNumero()) + "&mp1=" + to_string(mesa_aux[0].getPalo()) + "&mn2=" + to_string(mesa_aux[1].getNumero()) + "&mp2=" + to_string(mesa_aux[1].getPalo()) + "&mn3=" + to_string(mesa_aux[2].getNumero()) + "&mp3=" + to_string(mesa_aux[2].getPalo()) + "&aa=" + to_string(aa) + "&ao=" + to_string(ao);
			/*strcpy(url_aux, "http://localhost:8000/flopini?mn1=");
			strcat(url_aux, (char*)mesa_aux[0].getNumero());
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mesa_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mesa_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mesa_aux[1].getPalo());
			strcat(url_aux, "&mn3=");
			strcat(url_aux, (char*)mesa_aux[2].getNumero());
			strcat(url_aux, "&mp3=");
			strcat(url_aux, (char*)mesa_aux[2].getPalo());
			strcat(url_aux, "&aa=");
			char fln[15];
			sprintf_s(fln, "%f", J.getApuesta());
			strcat(url_aux, fln);
			strcat(url_aux, "&ao=");
			char fln2[15];
			double apuestaopo = M.apuesta - J.getApuesta();
			sprintf_s(fln2, "%f", J.getApuesta());
			strcat(url_aux, fln2);
			url = url_aux;*/
		}
		else if (M.getIndiceRonda() == 2)
		{
			int aa = J.getApuesta();
			int ao = M.apuesta - aa;
			url_aux = "http://localhost:8000/turnini?mn=" + to_string(mesa_aux[3].getNumero()) + "&mp=" + to_string(mesa_aux[3].getPalo()) +"&aa=" + to_string(aa) + "&ao=" + to_string(ao);

			/*strcpy(url_aux, "http://localhost:8000/turnini?mn=");
			strcat(url_aux, (char*)mesa_aux[3].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[3].getPalo());
			strcat(url_aux, "&aa=");
			char fln[15];
			sprintf_s(fln, "%f", J.getApuesta());
			strcat(url_aux, fln);
			strcat(url_aux, "&ao=");
			char fln2[15];
			double apuestaopo = M.apuesta - J.getApuesta();
			sprintf_s(fln2, "%f", J.getApuesta());
			strcat(url_aux, fln2);
			url = url_aux;
			*/
		}
		else if (M.getIndiceRonda() == 3)
		{
			url_aux = "http://localhost:8000/riverini?mn=" + to_string(mesa_aux[4].getNumero()) + "&mp=" + to_string(mesa_aux[4].getPalo());
			/*strcpy(url_aux, "http://localhost:8000/riverini?mn=");
			strcat(url_aux, (char*)mesa_aux[4].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[4].getPalo());
			url = url_aux;*/

		}
		url = url_aux.c_str();
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
		res = curl_easy_perform(curl);

		document.Parse(chunk.memory);
		assert(document.IsArray());
		triple[0] = document[0].GetFloat();
		triple[1] = document[1].GetFloat();
		triple[2] = document[2].GetFloat();
		curl_easy_cleanup(curl);
		free(chunk.memory);
		curl_global_cleanup();
	}
	else
	{
	Carta* mano_aux = new Carta[2];
	mano_aux = J.getMano();
	int carta_alta = 0;
	int carta_baja = 0;
	if (mano_aux[0].getNumero() > mano_aux[1].getNumero())
	{
		carta_alta = mano_aux[0].getNumero();
		carta_baja = mano_aux[1].getNumero();
	}
	else if (mano_aux[0].getNumero() < mano_aux[1].getNumero())
	{
		carta_alta = mano_aux[1].getNumero();
		carta_baja = mano_aux[0].getNumero();
	}
	else
	{
		carta_alta = mano_aux[0].getNumero();
		carta_baja = mano_aux[1].getNumero();
	}

	if (carta_baja == 1)
	{
		int aux = carta_alta;
		carta_alta = carta_baja;
		carta_baja = aux;
	}
	switch (tipo)
	{
	case 1:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.05;
				triple[2] = 0.95;
			}
			else if (J.valor_mano >= 10)
			{
				triple[0] = 0.025;
				triple[1] = 0.075;
				triple[2] = 0.9;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.05;
				triple[1] = 0.1;
				triple[2] = 0.85;
			}
			else if (J.valor_mano == 8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{
						triple[0] = 0.05;
						triple[1] = 0.1;
						triple[2] = 0.85;
					}
					else
					{
						triple[0] = 0.075;
						triple[1] = 0.125;
						triple[2] = 0.8;
					}

				}
				else
				{
					triple[0] = 0.075;
					triple[1] = 0.125;
					triple[2] = 0.8;
				}

			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.1;
				triple[1] = 0.15;
				triple[2] = 0.75;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.1;
						triple[1] = 0.15;
						triple[2] = 0.75;
					}
					else
					{
						triple[0] = 0.125;
						triple[1] = 0.175;
						triple[2] = 0.7;
					}
				}
				else
				{
					triple[0] = 0.125;
					triple[1] = 0.175;
					triple[2] = 0.7;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.125;
				triple[1] = 0.175;
				triple[2] = 0.7;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.125;
						triple[1] = 0.175;
						triple[2] = 0.7;
					}
					else
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
					else
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
				}
				else
				{
					if ((14 - carta_baja) > 5)
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
				else
				{
					triple[0] = 0.20;
					triple[1] = 0.25;
					triple[2] = 0.55;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
			}
			else if (J.valor_mano == 3.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
			}
			else
			{
				triple[0] = 0.20;
				triple[1] = 0.25;
				triple[2] = 0.55;
			}
		}
		else
		{
			int value = trunc(J.valor_mano);
			switch (value)
			{
			case 9:
				triple[0] = 0;
				triple[1] = 0.05;
				triple[2] = 0.95;
				break;
			case 8:
				triple[0] = 0.025;
				triple[1] = 0.075;
				triple[2] = 0.9;
				break;
			case 7:
				triple[0] = 0.05;
				triple[1] = 0.1;
				triple[2] = 0.85;
				break;
			case 6:
				triple[0] = 0.075;
				triple[1] = 0.125;
				triple[2] = 0.8;
				break;
			case 5:
				triple[0] = 0.1;
				triple[1] = 0.15;
				triple[2] = 0.75;
				break;
			case 4:
				triple[0] = 0.125;
				triple[1] = 0.175;
				triple[2] = 0.7;
				break;
			case 3:
				triple[0] = 0.15;
				triple[1] = 0.2;
				triple[2] = 0.65;
				break;
			case 2:
				triple[0] = 0.175;
				triple[1] = 0.225;
				triple[2] = 0.6;
				break;
			case 1:
				triple[0] = 0.2;
				triple[1] = 0.25;
				triple[2] = 0.55;
				break;
			case 0:
				triple[0] = 0.225;
				triple[1] = 0.275;
				triple[2] = 0.5;
				break;
			}
			break;
		}

	case 2:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.01;
				triple[2] = 0.99;
			}
			else if (J.valor_mano >= 10)
			{
				triple[0] = 0.01546875;
				triple[1] = 0.2265625;
				triple[2] = 0.75796875;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.061875;
				triple[1] = 0.38125;
				triple[2] = 0.556875;
			}
			else if (J.valor_mano == 8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{
						triple[0] = 0.061875;
						triple[1] = 0.38125;
						triple[2] = 0.556875;
					}
					else
					{
						triple[0] = 0.13921875;
						triple[1] = 0.4740625;
						triple[2] = 0.38671875;
					}

				}
				else
				{
					triple[0] = 0.13921875;
					triple[1] = 0.4740625;
					triple[2] = 0.38671875;
				}

			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.2475;
				triple[1] = 0.505;
				triple[2] = 0.2475;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.2475;
						triple[1] = 0.505;
						triple[2] = 0.2475;
					}
					else
					{
						triple[0] = 0.38671875;
						triple[1] = 0.4740625;
						triple[2] = 0.13921875;
					}
				}
				else
				{
					triple[0] = 0.38671875;
					triple[1] = 0.4740625;
					triple[2] = 0.13921875;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.38671875;
				triple[1] = 0.4740625;
				triple[2] = 0.13921875;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.38671875;
						triple[1] = 0.4740625;
						triple[2] = 0.13921875;
					}
					else
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
					else
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
				}
				else
				{
					if ((14 - carta_baja) > 5)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.75796875;
					triple[1] = 0.2265625;
					triple[2] = 0.01546875;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.75796875;
					triple[1] = 0.2265625;
					triple[2] = 0.01546875;
				}
				else
				{
					triple[0] = 0.99;
					triple[1] = 0.01;
					triple[2] = 0;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else if (J.valor_mano == 3.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else
			{
				triple[0] = 0.99;
				triple[1] = 0.01;
				triple[2] = 0;
			}
		}
		else
		{
			int value = trunc(J.valor_mano);
			switch (value)
			{
			case 9:
				triple[0] = 0;
				triple[1] = 0.01;
				triple[2] = 0.99;
				break;
			case 8:
				triple[0] = 0.01222222;
				triple[1] = 0.20555556;
				triple[2] = 0.78222222;
				break;
			case 7:
				triple[0] = 0.04888889;
				triple[1] = 0.35222222;
				triple[2] = 0.59888889;
				break;
			case 6:
				triple[0] = 0.11;
				triple[1] = 0.45;
				triple[2] = 0.44;
				break;
			case 5:
				triple[0] = 0.19555556;
				triple[1] = 0.49888889;
				triple[2] = 0.30555556;
				break;
			case 4:
				triple[0] = 0.30555556;
				triple[1] = 0.49888889;
				triple[2] = 0.19555556;
				break;
			case 3:
				triple[0] = 0.44;
				triple[1] = 0.45;
				triple[2] = 0.11;
				break;
			case 2:
				triple[0] = 0.59888889;
				triple[1] = 0.35222222;
				triple[2] = 0.04888889;
				break;
			case 1:
				triple[0] = 0.78222222;
				triple[1] = 0.20555556;
				triple[2] = 0.01222222;
				break;
			case 0:
				triple[0] = 0.99;
				triple[1] = 0.01;
				triple[2] = 0;
				break;
			}
			break;
		}
	case 3:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.85;
				triple[2] = 0.15;
			}
			else if (J.valor_mano >= 10)
			{
				triple[0] = 0.0375;
				triple[1] = 0.825;
				triple[2] = 0.1375;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.075;
				triple[1] = 0.8;
				triple[2] = 0.125;
			}
			else if (J.valor_mano == 8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{
						triple[0] = 0.075;
						triple[1] = 0.8;
						triple[2] = 0.125;
					}
					else
					{
						triple[0] = 0.1125;
						triple[1] = 0.775;
						triple[2] = 0.1125;
					}

				}
				else
				{
					triple[0] = 0.1125;
					triple[1] = 0.775;
					triple[2] = 0.1125;
				}

			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.15;
				triple[1] = 0.75;
				triple[2] = 0.1;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.15;
						triple[1] = 0.75;
						triple[2] = 0.1;
					}
					else
					{
						triple[0] = 0.1875;
						triple[1] = 0.725;
						triple[2] = 0.0875;
					}
				}
				else
				{
					triple[0] = 0.1875;
					triple[1] = 0.725;
					triple[2] = 0.0875;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.1875;
				triple[1] = 0.725;
				triple[2] = 0.0875;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.1875;
						triple[1] = 0.725;
						triple[2] = 0.0875;
					}
					else
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
					else
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
				}
				else
				{
					if ((14 - carta_baja) > 5)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.2625;
					triple[1] = 0.675;
					triple[2] = 0.0625;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.2625;
					triple[1] = 0.675;
					triple[2] = 0.0625;
				}
				else
				{
					triple[0] = 0.3;
					triple[1] = 0.65;
					triple[2] = 0.05;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else if (J.valor_mano == 3.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else
			{
				triple[0] = 0.3;
				triple[1] = 0.65;
				triple[2] = 0.05;
			}
		}
		else
		{
			int value = trunc(J.valor_mano);
			switch (value)
			{
			case 9:
				triple[0] = 0;
				triple[1] = 0.85;
				triple[2] = 0.15;
				break;
			case 8:
				triple[0] = 0.0375;
				triple[1] = 0.825;
				triple[2] = 0.1375;
				break;
			case 7:
				triple[0] = 0.075;
				triple[1] = 0.8;
				triple[2] = 0.125;
				break;
			case 6:
				triple[0] = 0.1125;
				triple[1] = 0.775;
				triple[2] = 0.1125;
				break;
			case 5:
				triple[0] = 0.15;
				triple[1] = 0.75;
				triple[2] = 0.1;
				break;
			case 4:
				triple[0] = 0.1875;
				triple[1] = 0.725;
				triple[2] = 0.0875;
				break;
			case 3:
				triple[0] = 0.225;
				triple[1] = 0.7;
				triple[2] = 0.075;
				break;
			case 2:
				triple[0] = 0.2625;
				triple[1] = 0.675;
				triple[2] = 0.0625;
				break;
			case 1:
				triple[0] = 0.3;
				triple[1] = 0.65;
				triple[2] = 0.05;
				break;
			case 0:
				triple[0] = 0.3375;
				triple[1] = 0.625;
				triple[2] = 0.0375;
				break;
			}
			break;
		}
	}
	}
}

//char Algoritmo::conversorAccion()
//{
//	switch (accion)
//	{
//	case 0:
//		return 'P';
//	case 1:
//		return 'V';
//	case 2: 
//		return 'S';
//	default:
//		break;
//	}
//}

int Algoritmo::obtenerAccionSegundo(Jugador J, Mesa M,int accionprevia) {
	
			obtenerTripleAccion(J, M,accionprevia);

			random r;
			float p = 0, v = 0, s = 0, n = 0;
			n = r.nrandomPorcent();
			//n = rand()%(100+1)*0.01;

			p = triple[0];
			v = p + triple[1];
			if (triple[2] != 0)
			{
				s = 1;
			}
			else
			{
				s = 0;
			}
			if (n <= p)
			{
				return 0;
			}
			else if (n <= v)
			{
				return 1;
			}
			else
			{
				return 2;
			}
	
}

void Algoritmo::obtenerTripleAccion(Jugador J, Mesa M, int accionprevia) {
	if (tipo == 4)
	{
		struct MemoryStruct chunk;

		chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
		chunk.size = 0;    /* no data at this point */

		curl_global_init(CURL_GLOBAL_ALL);

		CURL* curl = curl_easy_init();
		CURLcode res;

		Carta* mano_aux = new Carta[2];
		Carta* mesa_aux = new Carta[5];
		mano_aux = J.getMano();
		mesa_aux = M.Tablero;
		for (int i = 0; i < 5; i++)
		{
			if (i < 2)
			{
				if (mano_aux[i].getNumero() == 1)
				{
					mano_aux[i].setNumero(14);
				}
			}
			if (mesa_aux[i].getNumero() == 1)
			{
				mesa_aux[i].setNumero(14);
			}
		}

		rapidjson::Document document;
		const char* url = "http://localhost:8000/error";
		string url_aux;

		if (M.getIndiceRonda() == 0)
		{
			/*strcpy(url_aux, "http://localhost:8000/preflop?mn1=");
			strcat(url_aux, (char*)mano_aux[0].getNumero());
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mano_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mano_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mano_aux[1].getPalo());
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);*/
			url_aux = "http://localhost:8000/preflop?mn1=" + to_string(mano_aux[0].getNumero()) + "&mp1=" + to_string(mano_aux[0].getPalo()) + "&mn2=" + to_string(mano_aux[1].getNumero()) + "&mp2=" + to_string(mano_aux[1].getPalo())+ "&a="+to_string(accionprevia);

			//url = url_aux;
		}
		else if (M.getIndiceRonda() == 1)
		{/*-
			strcpy(url_aux, "http://localhost:8000/flop?mn1=");
			strcat(url_aux, (char*)mesa_aux[0].getNumero());
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mesa_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mesa_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mesa_aux[1].getPalo());
			strcat(url_aux, "&mn3=");
			strcat(url_aux, (char*)mesa_aux[2].getNumero());
			strcat(url_aux, "&mp3=");
			strcat(url_aux, (char*)mesa_aux[2].getPalo());
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);
			strcat(url_aux, "&aa=");
			char fln[15];
			sprintf_s(fln, "%f", J.getApuesta());
			strcat(url_aux, fln);
			strcat(url_aux, "&ao=");
			char fln2[15];
			double apuestaopo = M.apuesta - J.getApuesta();
			sprintf_s(fln2, "%f", J.getApuesta());
			strcat(url_aux, fln2);

			url = url_aux;*/

			int aa = J.getApuesta();
			int ao = M.apuesta - aa;
			url_aux = "http://localhost:8000/flop?mn1=" + to_string(mesa_aux[0].getNumero()) + "&mp1=" + to_string(mesa_aux[0].getPalo()) + "&mn2=" + to_string(mesa_aux[1].getNumero()) + "&mp2=" + to_string(mesa_aux[1].getPalo()) + "&mn3=" + to_string(mesa_aux[2].getNumero()) + "&mp3=" + to_string(mesa_aux[2].getPalo()) + "&a=" +to_string(accionprevia)+ "&aa=" + to_string(aa) + "&ao=" + to_string(ao);

		}
		else if (M.getIndiceRonda() == 2)
		{
			/*strcpy(url_aux, "http://localhost:8000/turn?mn=");
			strcat(url_aux, (char*)mesa_aux[3].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[3].getPalo());
			strcat(url_aux, "&aa=");
			char fln[15];
			sprintf_s(fln, "%f", J.getApuesta());
			strcat(url_aux, fln);
			strcat(url_aux, "&ao=");
			char fln2[15];
			float apuestaopo = M.apuesta - J.getApuesta();
			sprintf_s(fln2, "%f", J.getApuesta());
			strcat(url_aux, fln2);
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);
			url = url_aux;*/
			int aa = J.getApuesta();
			int ao = M.apuesta - aa;
			url_aux = "http://localhost:8000/turn?mn=" + to_string(mesa_aux[3].getNumero()) + "&mp=" + to_string(mesa_aux[3].getPalo()) + "&aa=" + to_string(aa) + "&ao=" + to_string(ao) + "&a=" + to_string(accionprevia);


		}
		else if (M.getIndiceRonda() == 3)
		{
			/*
			strcpy(url_aux, "http://localhost:8000/river?mn=");
			strcat(url_aux, (char*)mesa_aux[4].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[4].getPalo());
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);
			url = url_aux;*/
			url_aux = "http://localhost:8000/river?mn=" + to_string(mesa_aux[4].getNumero()) + "&mp=" + to_string(mesa_aux[4].getPalo()) + "&a=" + to_string(accionprevia);

		}
		url = url_aux.c_str();
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
		res = curl_easy_perform(curl);

		document.Parse(chunk.memory);
		assert(document.IsArray());
		triple[0] = document[0].GetFloat();
		triple[1] = document[1].GetFloat();
		triple[2] = document[2].GetFloat();
		curl_easy_cleanup(curl);
		free(chunk.memory);
		curl_global_cleanup();
	}
	else
	{
	Carta* mano_aux = new Carta[2];
	mano_aux = J.getMano();
	int carta_alta = 0;
	int carta_baja = 0;
	if (mano_aux[0].getNumero() > mano_aux[1].getNumero())
	{
		carta_alta = mano_aux[0].getNumero();
		carta_baja = mano_aux[1].getNumero();
	}
	else if (mano_aux[0].getNumero() < mano_aux[1].getNumero())
	{
		carta_alta = mano_aux[1].getNumero();
		carta_baja = mano_aux[0].getNumero();
	}
	else
	{
		carta_alta = mano_aux[0].getNumero();
		carta_baja = mano_aux[1].getNumero();
	}

	if (carta_baja == 1)
	{
		int aux = carta_alta;
		carta_alta = carta_baja;
		carta_baja = aux;
	}
	switch (tipo)
	{
	case 1:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.05;
				triple[2] = 0.95;
			}
			else if(J.valor_mano >= 10)
			{
				triple[0] = 0.025;
				triple[1] = 0.075;
				triple[2] = 0.9;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.05;
				triple[1] = 0.1;
				triple[2] = 0.85;
			}
			else if (J.valor_mano ==8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if(mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{ 
						triple[0] = 0.05;
						triple[1] = 0.1;
						triple[2] = 0.85;
					}
					else
					{
						triple[0] = 0.075;
						triple[1] = 0.125;
						triple[2] = 0.8;
					}
					
				}
				else
				{
					triple[0] = 0.075;
					triple[1] = 0.125;
					triple[2] = 0.8;
				}
				
			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.1;
				triple[1] = 0.15;
				triple[2] = 0.75;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.1;
						triple[1] = 0.15;
						triple[2] = 0.75;
					}
					else
					{
						triple[0] = 0.125;
						triple[1] = 0.175;
						triple[2] = 0.7;
					}
				}
				else
				{
					triple[0] = 0.125;
					triple[1] = 0.175;
					triple[2] = 0.7;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.125;
				triple[1] = 0.175;
				triple[2] = 0.7;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.125;
						triple[1] = 0.175;
						triple[2] = 0.7;
					}
					else
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
					else
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
				}
				else
				{
					if ((14-carta_baja)>5)
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
				else
				{
					triple[0] = 0.20;
					triple[1] = 0.25;
					triple[2] = 0.55;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.15;
						triple[1] = 0.20;
						triple[2] = 0.65;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
					else
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
				}
			}
			else if (J.valor_mano==3.5)
			{ 
			if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
			{
				if ((carta_alta - carta_baja) == 2)
				{
					triple[0] = 0.15;
					triple[1] = 0.20;
					triple[2] = 0.65;
				}
				else
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
			}
			else
			{
				if ((carta_alta - carta_baja) == 2)
				{
					triple[0] = 0.20;
					triple[1] = 0.25;
					triple[2] = 0.55;
				}
				else
				{
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.60;
				}
			}
			}
			else
			{
				triple[0] = 0.20;
				triple[1] = 0.25;
				triple[2] = 0.55;
			 }
		}
		else
		{
		int value = trunc(J.valor_mano);
		switch (value)
		{
		case 9:
			triple[0] = 0;
			triple[1] = 0.05;
			triple[2] = 0.95;
			break;
		case 8:
			triple[0] = 0.025;
			triple[1] = 0.075;
			triple[2] = 0.9;
			break;
		case 7:
			triple[0] = 0.05;
			triple[1] = 0.1;
			triple[2] = 0.85;
			break;
		case 6:
			triple[0] = 0.075;
			triple[1] = 0.125;
			triple[2] = 0.8;
			break;
		case 5:
			triple[0] = 0.1;
			triple[1] = 0.15;
			triple[2] = 0.75;
			break;
		case 4:
			triple[0] = 0.125;
			triple[1] = 0.175;
			triple[2] = 0.7;
			break;
		case 3:
			triple[0] = 0.15;
			triple[1] = 0.2;
			triple[2] = 0.65;
			break;
		case 2:
			triple[0] = 0.175;
			triple[1] = 0.225;
			triple[2] = 0.6;
			break;
		case 1:
			triple[0] = 0.2;
			triple[1] = 0.25;
			triple[2] = 0.55;
			break;
		case 0:
			triple[0] = 0.225;
			triple[1] = 0.275;
			triple[2] = 0.5;
			break;
		}
		break;
		}
		
	case 2:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.01;
				triple[2] = 0.99;
			}
			else if (J.valor_mano >= 10)
			{
				triple[0] = 0.01546875;
				triple[1] = 0.2265625;
				triple[2] = 0.75796875;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.061875;
				triple[1] = 0.38125;
				triple[2] = 0.556875;
			}
			else if (J.valor_mano == 8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{
						triple[0] = 0.061875;
						triple[1] = 0.38125;
						triple[2] = 0.556875;
					}
					else
					{
						triple[0] = 0.13921875;
						triple[1] = 0.4740625;
						triple[2] = 0.38671875;
					}

				}
				else
				{
					triple[0] = 0.13921875;
					triple[1] = 0.4740625;
					triple[2] = 0.38671875;
				}

			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.2475;
				triple[1] = 0.505;
				triple[2] = 0.2475;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.2475;
						triple[1] = 0.505;
						triple[2] = 0.2475;
					}
					else
					{
						triple[0] = 0.38671875;
						triple[1] = 0.4740625;
						triple[2] = 0.13921875;
					}
				}
				else
				{
					triple[0] = 0.38671875;
					triple[1] = 0.4740625;
					triple[2] = 0.13921875;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.38671875;
				triple[1] = 0.4740625;
				triple[2] = 0.13921875;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.38671875;
						triple[1] = 0.4740625;
						triple[2] = 0.13921875;
					}
					else
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
					else
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
				}
				else
				{
					if ((14 - carta_baja) > 5)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.75796875;
					triple[1] = 0.2265625;
					triple[2] = 0.01546875;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.75796875;
					triple[1] = 0.2265625;
					triple[2] = 0.01546875;
				}
				else
				{
					triple[0] = 0.99;
					triple[1] = 0.01;
					triple[2] = 0;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else if (J.valor_mano == 3.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.556875;
						triple[1] = 0.38125;
						triple[2] = 0.061875;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
					else
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
				}
			}
			else
			{
			triple[0] = 0.99;
			triple[1] = 0.01;
			triple[2] = 0;
			}
		}
		else
		{
			int value = trunc(J.valor_mano);
			switch (value)
			{
			case 9:
				triple[0] = 0;
				triple[1] = 0.01;
				triple[2] = 0.99;
				break;
			case 8:
				triple[0] = 0.01222222;
				triple[1] = 0.20555556;
				triple[2] = 0.78222222;
				break;
			case 7:
				triple[0] = 0.04888889;
				triple[1] = 0.35222222;
				triple[2] = 0.59888889;
				break;
			case 6:
				triple[0] = 0.11;
				triple[1] = 0.45;
				triple[2] = 0.44;
				break;
			case 5:
				triple[0] = 0.19555556;
				triple[1] = 0.49888889;
				triple[2] = 0.30555556;
				break;
			case 4:
				triple[0] = 0.30555556;
				triple[1] = 0.49888889;
				triple[2] = 0.19555556;
				break;
			case 3:
				triple[0] = 0.44;
				triple[1] = 0.45;
				triple[2] = 0.11;
				break;
			case 2:
				triple[0] = 0.59888889;
				triple[1] = 0.35222222;
				triple[2] = 0.04888889;
				break;
			case 1:
				triple[0] = 0.78222222;
				triple[1] = 0.20555556;
				triple[2] = 0.01222222;
				break;
			case 0:
				triple[0] = 0.99;
				triple[1] = 0.01;
				triple[2] = 0;
				break;
			}
			break;
		}
	case 3:
		if (M.getIndiceRonda() == 0)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.85;
				triple[2] = 0.15;
			}
			else if (J.valor_mano >= 10)
			{
				triple[0] = 0.0375;
				triple[1] = 0.825;
				triple[2] = 0.1375;
			}
			else if (J.valor_mano >= 9)
			{
				triple[0] = 0.075;
				triple[1] = 0.8;
				triple[2] = 0.125;
			}
			else if (J.valor_mano == 8)
			{
				if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
				{
					if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
					{
						triple[0] = 0.075;
						triple[1] = 0.8;
						triple[2] = 0.125;
					}
					else
					{
						triple[0] = 0.1125;
						triple[1] = 0.775;
						triple[2] = 0.1125;
					}

				}
				else
				{
					triple[0] = 0.1125;
					triple[1] = 0.775;
					triple[2] = 0.1125;
				}

			}
			else if (J.valor_mano > 6)
			{
				triple[0] = 0.15;
				triple[1] = 0.75;
				triple[2] = 0.1;
			}
			else if (J.valor_mano == 6)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
					{
						triple[0] = 0.15;
						triple[1] = 0.75;
						triple[2] = 0.1;
					}
					else
					{
						triple[0] = 0.1875;
						triple[1] = 0.725;
						triple[2] = 0.0875;
					}
				}
				else
				{
					triple[0] = 0.1875;
					triple[1] = 0.725;
					triple[2] = 0.0875;
				}

			}
			else if (J.valor_mano == 5.5)
			{
				triple[0] = 0.1875;
				triple[1] = 0.725;
				triple[2] = 0.0875;
			}
			else if (J.valor_mano == 5)
			{
				if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
				{
					if (carta_alta == 5)
					{
						triple[0] = 0.1875;
						triple[1] = 0.725;
						triple[2] = 0.0875;
					}
					else
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
				}
				else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if (carta_alta == 9 && carta_baja == 6)
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
					else
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
				}
				else
				{
					if ((14 - carta_baja) > 5)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else if (J.valor_mano == 4.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					triple[0] = 0.2625;
					triple[1] = 0.675;
					triple[2] = 0.0625;
				}
				else if ((carta_alta - carta_baja) == 1)
				{
					triple[0] = 0.2625;
					triple[1] = 0.675;
					triple[2] = 0.0625;
				}
				else
				{
					triple[0] = 0.3;
					triple[1] = 0.65;
					triple[2] = 0.05;
				}
			}
			else if (J.valor_mano == 4)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta + carta_baja) == 20)
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else if (J.valor_mano == 3.5)
			{
				if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.225;
						triple[1] = 0.7;
						triple[2] = 0.075;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
				else
				{
					if ((carta_alta - carta_baja) == 2)
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
					else
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
				}
			}
			else
			{
			triple[0] = 0.3;
			triple[1] = 0.65;
			triple[2] = 0.05;
			}
		}
		else
		{
			int value = trunc(J.valor_mano);
			switch (value)
			{
			case 9:
				triple[0] = 0;
				triple[1] = 0.85;
				triple[2] = 0.15;
				break;
			case 8:
				triple[0] = 0.0375;
				triple[1] = 0.825;
				triple[2] = 0.1375;
				break;
			case 7:
				triple[0] = 0.075;
				triple[1] = 0.8;
				triple[2] = 0.125;
				break;
			case 6:
				triple[0] = 0.1125;
				triple[1] = 0.775;
				triple[2] = 0.1125;
				break;
			case 5:
				triple[0] = 0.15;
				triple[1] = 0.75;
				triple[2] = 0.1;
				break;
			case 4:
				triple[0] = 0.1875;
				triple[1] = 0.725;
				triple[2] = 0.0875;
				break;
			case 3:
				triple[0] = 0.225;
				triple[1] = 0.7;
				triple[2] = 0.075;
				break;
			case 2:
				triple[0] = 0.2625;
				triple[1] = 0.675;
				triple[2] = 0.0625;
				break;
			case 1:
				triple[0] = 0.3;
				triple[1] = 0.65;
				triple[2] = 0.05;
				break;
			case 0:
				triple[0] = 0.3375;
				triple[1] = 0.625;
				triple[2] = 0.0375;
				break;
			}
			break;
		}
	}
	}
}

int Algoritmo::obtenerAccionAct(Jugador J, Mesa M, int accionprevia)
{
	obtenerTripleAct(J, M,  accionprevia);

	random r;
	float p = 0, v = 0, s = 0, n = 0;
	n = r.nrandomPorcent();
	//n = rand()%(100+1)*0.01;

	p = triple[0];
	v = p + triple[1];
	if (triple[2] != 0)
	{
		s = 1;
	}
	else
	{
		s = 0;
	}
	if (n <= p)
	{
		return 0;
	}
	else if (n <= v)
	{
		return 1;
	}
	else
	{
		return 2;
	}

}

void Algoritmo::obtenerTripleAct(Jugador J, Mesa M, int accionprevia)
{
	if (tipo == 4)
	{
		struct MemoryStruct chunk;

		chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
		chunk.size = 0;    /* no data at this point */

		curl_global_init(CURL_GLOBAL_ALL);

		CURL* curl = curl_easy_init();
		CURLcode res;

		rapidjson::Document document;
		const char* url = "http://localhost:8000/error";
		//char url_aux[110];
		string url_aux;

		if (M.getIndiceRonda() == 0)
		{
			/*strcpy(url_aux, "http://localhost:8000/preflopact?a=");
			strcat(url_aux, (char*)accionprevia);

			url = url_aux;*/
			url_aux = "http://localhost:8000/preflopact?a=" + to_string(accionprevia);
		}
		else if (M.getIndiceRonda() == 1 || M.getIndiceRonda() == 2)
		{
			/*strcpy(url_aux, "http://localhost:8000/flopact?a=");
			strcat(url_aux, (char*)accionprevia);
			strcat(url_aux, "&aa=");
			char fln[15];
			sprintf_s(fln, "%f", J.getApuesta());
			strcat(url_aux, fln);
			strcat(url_aux, "&ao=");
			char fln2[15];
			float apuestaopo = M.apuesta - J.getApuesta();
			sprintf_s(fln2, "%f", J.getApuesta());
			strcat(url_aux, fln2);

			url = url_aux;*/
			int aa = J.getApuesta();
			int ao = M.apuesta - aa;
			url_aux = "http://localhost:8000/flopact?a=" + to_string(accionprevia) + "&aa=" + to_string(aa) + "&ao=" + to_string(ao);

		}
		else if (M.getIndiceRonda() == 3)
		{
			/*
			strcpy(url_aux, "http://localhost:8000/riveract?a=");
			strcat(url_aux, (char*)accionprevia);
			url = url_aux;*/
			url_aux = "http://localhost:8000/riveract?a=" + to_string(accionprevia);

		}

		url = url_aux.c_str();
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
		res = curl_easy_perform(curl);

		document.Parse(chunk.memory);
		assert(document.IsArray());
		triple[0] = document[0].GetFloat();
		triple[1] = document[1].GetFloat();
		triple[2] = document[2].GetFloat();
		curl_easy_cleanup(curl);
		free(chunk.memory);
		curl_global_cleanup();
	}
	else
	{
		Carta* mano_aux = new Carta[2];
		mano_aux = J.getMano();
		int carta_alta = 0;
		int carta_baja = 0;
		if (mano_aux[0].getNumero() > mano_aux[1].getNumero())
		{
			carta_alta = mano_aux[0].getNumero();
			carta_baja = mano_aux[1].getNumero();
		}
		else if (mano_aux[0].getNumero() < mano_aux[1].getNumero())
		{
			carta_alta = mano_aux[1].getNumero();
			carta_baja = mano_aux[0].getNumero();
		}
		else
		{
			carta_alta = mano_aux[0].getNumero();
			carta_baja = mano_aux[1].getNumero();
		}

		if (carta_baja == 1)
		{
			int aux = carta_alta;
			carta_alta = carta_baja;
			carta_baja = aux;
		}
		switch (tipo)
		{
		case 1:
			if (M.getIndiceRonda() == 0)
			{
				if (J.valor_mano >= 12)
				{
					triple[0] = 0;
					triple[1] = 0.05;
					triple[2] = 0.95;
				}
				else if (J.valor_mano >= 10)
				{
					triple[0] = 0.025;
					triple[1] = 0.075;
					triple[2] = 0.9;
				}
				else if (J.valor_mano >= 9)
				{
					triple[0] = 0.05;
					triple[1] = 0.1;
					triple[2] = 0.85;
				}
				else if (J.valor_mano == 8)
				{
					if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
					{
						if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
						{
							triple[0] = 0.05;
							triple[1] = 0.1;
							triple[2] = 0.85;
						}
						else
						{
							triple[0] = 0.075;
							triple[1] = 0.125;
							triple[2] = 0.8;
						}

					}
					else
					{
						triple[0] = 0.075;
						triple[1] = 0.125;
						triple[2] = 0.8;
					}

				}
				else if (J.valor_mano > 6)
				{
					triple[0] = 0.1;
					triple[1] = 0.15;
					triple[2] = 0.75;
				}
				else if (J.valor_mano == 6)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
						{
							triple[0] = 0.1;
							triple[1] = 0.15;
							triple[2] = 0.75;
						}
						else
						{
							triple[0] = 0.125;
							triple[1] = 0.175;
							triple[2] = 0.7;
						}
					}
					else
					{
						triple[0] = 0.125;
						triple[1] = 0.175;
						triple[2] = 0.7;
					}

				}
				else if (J.valor_mano == 5.5)
				{
					triple[0] = 0.125;
					triple[1] = 0.175;
					triple[2] = 0.7;
				}
				else if (J.valor_mano == 5)
				{
					if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
					{
						if (carta_alta == 5)
						{
							triple[0] = 0.125;
							triple[1] = 0.175;
							triple[2] = 0.7;
						}
						else
						{
							triple[0] = 0.15;
							triple[1] = 0.20;
							triple[2] = 0.65;
						}
					}
					else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (carta_alta == 9 && carta_baja == 6)
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
						else
						{
							triple[0] = 0.15;
							triple[1] = 0.20;
							triple[2] = 0.65;
						}
					}
					else
					{
						if ((14 - carta_baja) > 5)
						{
							triple[0] = 0.20;
							triple[1] = 0.25;
							triple[2] = 0.55;
						}
						else
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
					}
				}
				else if (J.valor_mano == 4.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
					else if ((carta_alta - carta_baja) == 1)
					{
						triple[0] = 0.175;
						triple[1] = 0.225;
						triple[2] = 0.60;
					}
					else
					{
						triple[0] = 0.20;
						triple[1] = 0.25;
						triple[2] = 0.55;
					}
				}
				else if (J.valor_mano == 4)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta + carta_baja) == 20)
						{
							triple[0] = 0.15;
							triple[1] = 0.20;
							triple[2] = 0.65;
						}
						else
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.20;
							triple[1] = 0.25;
							triple[2] = 0.55;
						}
						else
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
					}
				}
				else if (J.valor_mano == 3.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.15;
							triple[1] = 0.20;
							triple[2] = 0.65;
						}
						else
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.20;
							triple[1] = 0.25;
							triple[2] = 0.55;
						}
						else
						{
							triple[0] = 0.175;
							triple[1] = 0.225;
							triple[2] = 0.60;
						}
					}
				}
				else
				{
					triple[0] = 0.20;
					triple[1] = 0.25;
					triple[2] = 0.55;
				}
			}
			else
			{
				int value = trunc(J.valor_mano);
				switch (value)
				{
				case 9:
					triple[0] = 0;
					triple[1] = 0.05;
					triple[2] = 0.95;
					break;
				case 8:
					triple[0] = 0.025;
					triple[1] = 0.075;
					triple[2] = 0.9;
					break;
				case 7:
					triple[0] = 0.05;
					triple[1] = 0.1;
					triple[2] = 0.85;
					break;
				case 6:
					triple[0] = 0.075;
					triple[1] = 0.125;
					triple[2] = 0.8;
					break;
				case 5:
					triple[0] = 0.1;
					triple[1] = 0.15;
					triple[2] = 0.75;
					break;
				case 4:
					triple[0] = 0.125;
					triple[1] = 0.175;
					triple[2] = 0.7;
					break;
				case 3:
					triple[0] = 0.15;
					triple[1] = 0.2;
					triple[2] = 0.65;
					break;
				case 2:
					triple[0] = 0.175;
					triple[1] = 0.225;
					triple[2] = 0.6;
					break;
				case 1:
					triple[0] = 0.2;
					triple[1] = 0.25;
					triple[2] = 0.55;
					break;
				case 0:
					triple[0] = 0.225;
					triple[1] = 0.275;
					triple[2] = 0.5;
					break;
				}
				break;
			}

		case 2:
			if (M.getIndiceRonda() == 0)
			{
				if (J.valor_mano >= 12)
				{
					triple[0] = 0;
					triple[1] = 0.01;
					triple[2] = 0.99;
				}
				else if (J.valor_mano >= 10)
				{
					triple[0] = 0.01546875;
					triple[1] = 0.2265625;
					triple[2] = 0.75796875;
				}
				else if (J.valor_mano >= 9)
				{
					triple[0] = 0.061875;
					triple[1] = 0.38125;
					triple[2] = 0.556875;
				}
				else if (J.valor_mano == 8)
				{
					if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
					{
						if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
						{
							triple[0] = 0.061875;
							triple[1] = 0.38125;
							triple[2] = 0.556875;
						}
						else
						{
							triple[0] = 0.13921875;
							triple[1] = 0.4740625;
							triple[2] = 0.38671875;
						}

					}
					else
					{
						triple[0] = 0.13921875;
						triple[1] = 0.4740625;
						triple[2] = 0.38671875;
					}

				}
				else if (J.valor_mano > 6)
				{
					triple[0] = 0.2475;
					triple[1] = 0.505;
					triple[2] = 0.2475;
				}
				else if (J.valor_mano == 6)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
						{
							triple[0] = 0.2475;
							triple[1] = 0.505;
							triple[2] = 0.2475;
						}
						else
						{
							triple[0] = 0.38671875;
							triple[1] = 0.4740625;
							triple[2] = 0.13921875;
						}
					}
					else
					{
						triple[0] = 0.38671875;
						triple[1] = 0.4740625;
						triple[2] = 0.13921875;
					}

				}
				else if (J.valor_mano == 5.5)
				{
					triple[0] = 0.38671875;
					triple[1] = 0.4740625;
					triple[2] = 0.13921875;
				}
				else if (J.valor_mano == 5)
				{
					if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
					{
						if (carta_alta == 5)
						{
							triple[0] = 0.38671875;
							triple[1] = 0.4740625;
							triple[2] = 0.13921875;
						}
						else
						{
							triple[0] = 0.556875;
							triple[1] = 0.38125;
							triple[2] = 0.061875;
						}
					}
					else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (carta_alta == 9 && carta_baja == 6)
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
						else
						{
							triple[0] = 0.556875;
							triple[1] = 0.38125;
							triple[2] = 0.061875;
						}
					}
					else
					{
						if ((14 - carta_baja) > 5)
						{
							triple[0] = 0.99;
							triple[1] = 0.01;
							triple[2] = 0;
						}
						else
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
					}
				}
				else if (J.valor_mano == 4.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
					else if ((carta_alta - carta_baja) == 1)
					{
						triple[0] = 0.75796875;
						triple[1] = 0.2265625;
						triple[2] = 0.01546875;
					}
					else
					{
						triple[0] = 0.99;
						triple[1] = 0.01;
						triple[2] = 0;
					}
				}
				else if (J.valor_mano == 4)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta + carta_baja) == 20)
						{
							triple[0] = 0.556875;
							triple[1] = 0.38125;
							triple[2] = 0.061875;
						}
						else
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.99;
							triple[1] = 0.01;
							triple[2] = 0;
						}
						else
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
					}
				}
				else if (J.valor_mano == 3.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.556875;
							triple[1] = 0.38125;
							triple[2] = 0.061875;
						}
						else
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.99;
							triple[1] = 0.01;
							triple[2] = 0;
						}
						else
						{
							triple[0] = 0.75796875;
							triple[1] = 0.2265625;
							triple[2] = 0.01546875;
						}
					}
				}
				else
				{
					triple[0] = 0.99;
					triple[1] = 0.01;
					triple[2] = 0;
				}
			}
			else
			{
				int value = trunc(J.valor_mano);
				switch (value)
				{
				case 9:
					triple[0] = 0;
					triple[1] = 0.01;
					triple[2] = 0.99;
					break;
				case 8:
					triple[0] = 0.01222222;
					triple[1] = 0.20555556;
					triple[2] = 0.78222222;
					break;
				case 7:
					triple[0] = 0.04888889;
					triple[1] = 0.35222222;
					triple[2] = 0.59888889;
					break;
				case 6:
					triple[0] = 0.11;
					triple[1] = 0.45;
					triple[2] = 0.44;
					break;
				case 5:
					triple[0] = 0.19555556;
					triple[1] = 0.49888889;
					triple[2] = 0.30555556;
					break;
				case 4:
					triple[0] = 0.30555556;
					triple[1] = 0.49888889;
					triple[2] = 0.19555556;
					break;
				case 3:
					triple[0] = 0.44;
					triple[1] = 0.45;
					triple[2] = 0.11;
					break;
				case 2:
					triple[0] = 0.59888889;
					triple[1] = 0.35222222;
					triple[2] = 0.04888889;
					break;
				case 1:
					triple[0] = 0.78222222;
					triple[1] = 0.20555556;
					triple[2] = 0.01222222;
					break;
				case 0:
					triple[0] = 0.99;
					triple[1] = 0.01;
					triple[2] = 0;
					break;
				}
				break;
			}
		case 3:
			if (M.getIndiceRonda() == 0)
			{
				if (J.valor_mano >= 12)
				{
					triple[0] = 0;
					triple[1] = 0.85;
					triple[2] = 0.15;
				}
				else if (J.valor_mano >= 10)
				{
					triple[0] = 0.0375;
					triple[1] = 0.825;
					triple[2] = 0.1375;
				}
				else if (J.valor_mano >= 9)
				{
					triple[0] = 0.075;
					triple[1] = 0.8;
					triple[2] = 0.125;
				}
				else if (J.valor_mano == 8)
				{
					if (mano_aux[0].getNumero() == 1 || mano_aux[1].getNumero() == 1)
					{
						if (mano_aux[0].getPalo() == mano_aux[1].getPalo())
						{
							triple[0] = 0.075;
							triple[1] = 0.8;
							triple[2] = 0.125;
						}
						else
						{
							triple[0] = 0.1125;
							triple[1] = 0.775;
							triple[2] = 0.1125;
						}

					}
					else
					{
						triple[0] = 0.1125;
						triple[1] = 0.775;
						triple[2] = 0.1125;
					}

				}
				else if (J.valor_mano > 6)
				{
					triple[0] = 0.15;
					triple[1] = 0.75;
					triple[2] = 0.1;
				}
				else if (J.valor_mano == 6)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (mano_aux[1].getNumero() == 12 || mano_aux[0].getNumero() == 12)
						{
							triple[0] = 0.15;
							triple[1] = 0.75;
							triple[2] = 0.1;
						}
						else
						{
							triple[0] = 0.1875;
							triple[1] = 0.725;
							triple[2] = 0.0875;
						}
					}
					else
					{
						triple[0] = 0.1875;
						triple[1] = 0.725;
						triple[2] = 0.0875;
					}

				}
				else if (J.valor_mano == 5.5)
				{
					triple[0] = 0.1875;
					triple[1] = 0.725;
					triple[2] = 0.0875;
				}
				else if (J.valor_mano == 5)
				{
					if (mano_aux[1].getNumero() == mano_aux[0].getNumero())
					{
						if (carta_alta == 5)
						{
							triple[0] = 0.1875;
							triple[1] = 0.725;
							triple[2] = 0.0875;
						}
						else
						{
							triple[0] = 0.225;
							triple[1] = 0.7;
							triple[2] = 0.075;
						}
					}
					else if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if (carta_alta == 9 && carta_baja == 6)
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
						else
						{
							triple[0] = 0.225;
							triple[1] = 0.7;
							triple[2] = 0.075;
						}
					}
					else
					{
						if ((14 - carta_baja) > 5)
						{
							triple[0] = 0.3;
							triple[1] = 0.65;
							triple[2] = 0.05;
						}
						else
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
					}
				}
				else if (J.valor_mano == 4.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
					else if ((carta_alta - carta_baja) == 1)
					{
						triple[0] = 0.2625;
						triple[1] = 0.675;
						triple[2] = 0.0625;
					}
					else
					{
						triple[0] = 0.3;
						triple[1] = 0.65;
						triple[2] = 0.05;
					}
				}
				else if (J.valor_mano == 4)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta + carta_baja) == 20)
						{
							triple[0] = 0.225;
							triple[1] = 0.7;
							triple[2] = 0.075;
						}
						else
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.3;
							triple[1] = 0.65;
							triple[2] = 0.05;
						}
						else
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
					}
				}
				else if (J.valor_mano == 3.5)
				{
					if (mano_aux[1].getPalo() == mano_aux[0].getPalo())
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.225;
							triple[1] = 0.7;
							triple[2] = 0.075;
						}
						else
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
					}
					else
					{
						if ((carta_alta - carta_baja) == 2)
						{
							triple[0] = 0.3;
							triple[1] = 0.65;
							triple[2] = 0.05;
						}
						else
						{
							triple[0] = 0.2625;
							triple[1] = 0.675;
							triple[2] = 0.0625;
						}
					}
				}
				else
				{
					triple[0] = 0.3;
					triple[1] = 0.65;
					triple[2] = 0.05;
				}
			}
			else
			{
				int value = trunc(J.valor_mano);
				switch (value)
				{
				case 9:
					triple[0] = 0;
					triple[1] = 0.85;
					triple[2] = 0.15;
					break;
				case 8:
					triple[0] = 0.0375;
					triple[1] = 0.825;
					triple[2] = 0.1375;
					break;
				case 7:
					triple[0] = 0.075;
					triple[1] = 0.8;
					triple[2] = 0.125;
					break;
				case 6:
					triple[0] = 0.1125;
					triple[1] = 0.775;
					triple[2] = 0.1125;
					break;
				case 5:
					triple[0] = 0.15;
					triple[1] = 0.75;
					triple[2] = 0.1;
					break;
				case 4:
					triple[0] = 0.1875;
					triple[1] = 0.725;
					triple[2] = 0.0875;
					break;
				case 3:
					triple[0] = 0.225;
					triple[1] = 0.7;
					triple[2] = 0.075;
					break;
				case 2:
					triple[0] = 0.2625;
					triple[1] = 0.675;
					triple[2] = 0.0625;
					break;
				case 1:
					triple[0] = 0.3;
					triple[1] = 0.65;
					triple[2] = 0.05;
					break;
				case 0:
					triple[0] = 0.3375;
					triple[1] = 0.625;
					triple[2] = 0.0375;
					break;
				}
				break;
			}
		}
	}
}
void Algoritmo::reseteo()
{
	CURL* curl = curl_easy_init();
	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000/reset");
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);


}

void Algoritmo::pasar(int ronda)
{
	if (tipo == 4)
	{
		CURL* curl = curl_easy_init();
		CURLcode res;
		string url_aux;
		const char* url;
		url_aux = "http://localhost:8000/pass?r=" + to_string(ronda);
		url = url_aux.c_str();
		curl_easy_setopt(curl, CURLOPT_URL, url);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	
}

int Algoritmo::obtenerSubida(float apuesta, float apuesta_ini) 
{
	//Editar
	random r;
	float n = r.nrandomPorcent();
	int salida = apuesta + apuesta_ini * (n+1);
	return salida;
}

void Algoritmo::actualizaBayes(int ronda)
{
	if (tipo == 4)
	{
		CURL* curl = curl_easy_init();
	CURLcode res;
	string url_aux;
	const char* url;
	url_aux = "http://localhost:8000/check?r=" + to_string(ronda);
	url = url_aux.c_str();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	}
}