#include "Algoritmo.h"
#include <math.h>
#include <cstdlib>
#include "random.h"
#include <curl/curl.h>
#include <iostream>
#include <rapidjson/document.h>

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
	if (tipo == 4)
	{ 
		std::cout << "obtenerAccion ejecutada en ronda: " << M.getIndiceRonda() << std::endl;
		std::cout << "Accion elegida: 2" << std::endl;
		return 2;
	}
	else
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


		const char* url = "http://localhost:8000/error";
		char url_aux[110];

		if (M.getIndiceRonda() == 0)
		{
			strcpy(url_aux, "http://localhost:8000/preflopini?mn1=");
			strcat(url_aux, (char*)mano_aux[0].getNumero());
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mano_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mano_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mano_aux[1].getPalo());
			url = url_aux;
		}
		else if (M.getIndiceRonda() == 1)
		{
			strcpy(url_aux, "http://localhost:8000/flopini?mn1=");
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
			url = url_aux;
		}
		else if (M.getIndiceRonda() == 2)
		{
			strcpy(url_aux, "http://localhost:8000/turnini?mn=");
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

		}
		else if (M.getIndiceRonda() == 3)
		{
			strcpy(url_aux, "http://localhost:8000/riverini?mn=");
			strcat(url_aux, (char*)mesa_aux[4].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[4].getPalo());
			url = url_aux;

		}

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
	switch (tipo)
	{
	case 1:
		if (M.getIndiceRonda() == 1)
		{
			if (J.valor_mano >= 3.5)
			{
				triple[0] = 0.05;
				triple[1] = 0.1;
				triple[2] = 0.85;
			}
			else
			{
				triple[0] = 0.2;
				triple[1] = 0.25;
				triple[2] = 0.55;
			}
		}
		else
		{
			triple[0] = 0.05;
			triple[1] = 0.15;
			triple[2] = 0.8;
		}
		break;
	case 2:
		if (M.getIndiceRonda() == 1)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.1;
				triple[2] = 0.9;
			}
			else if(J.valor_mano>=7)
			{
				triple[0] = 0.05;
				triple[1] = 0.9;
				triple[2] = 0.05;
			}
			else
			{
				triple[0] = 0.9;
				triple[1] = 0.1;
				triple[2] = 0;
			}
		}
		else
		{
			if (J.valor_mano >= 7)
			{
				triple[0] = 0;
				triple[1] = 0.1;
				triple[2] = 0.9;
			}
			else if (J.valor_mano >= 2)
			{
				triple[0] = 0.05;
				triple[1] = 0.9;
				triple[2] = 0.05;
			}
			else
			{
				triple[0] = 0.9;
				triple[1] = 0.1;
				triple[2] = 0;
			}
		}
		break;
	case 3:
		triple[0] = 0.25;
		triple[1] = 0.7;
		triple[2] = 0.05;
		break;
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
	if (tipo == 4)
	{
		std::cout << "obtenerAccionSegundo ejecutada en ronda: " << M.getIndiceRonda() << std::endl;
		std::cout << "Accion elegida: 2" << std::endl;
		return 2;
	}
	else
	{
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

		rapidjson::Document document;
		const char* url = "http://localhost:8000/error";
		char url_aux[110];

		if (M.getIndiceRonda() == 0)
		{
			strcpy(url_aux, "http://localhost:8000/preflop?mn1=");
			strcat(url_aux, (char*)mano_aux[0].getNumero());
			strcat(url_aux, "&mp1=");
			strcat(url_aux, (char*)mano_aux[0].getPalo());
			strcat(url_aux, "&mn2=");
			strcat(url_aux, (char*)mano_aux[1].getNumero());
			strcat(url_aux, "&mp2=");
			strcat(url_aux, (char*)mano_aux[1].getPalo());
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);

			url = url_aux;
		}
		else if (M.getIndiceRonda() == 1)
		{
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

			url = url_aux;
		}
		else if (M.getIndiceRonda() == 2)
		{
			strcpy(url_aux, "http://localhost:8000/turn?mn=");
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
			url = url_aux;

		}
		else if (M.getIndiceRonda() == 3)
		{
			strcpy(url_aux, "http://localhost:8000/river?mn=");
			strcat(url_aux, (char*)mesa_aux[4].getNumero());
			strcat(url_aux, "&mp=");
			strcat(url_aux, (char*)mesa_aux[4].getPalo());
			strcat(url_aux, "&a=");
			strcat(url_aux, (char*)accionprevia);
			url = url_aux;

		}

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
	switch (tipo)
	{
	case 1:
		if (M.getIndiceRonda() == 1)
		{
			if (J.valor_mano >= 3.5)
			{
				triple[0] = 0.05;
				triple[1] = 0.1;
				triple[2] = 0.85;
			}
			else
			{
				triple[0] = 0.2;
				triple[1] = 0.25;
				triple[2] = 0.55;
			}
		}
		else
		{
			triple[0] = 0.05;
			triple[1] = 0.15;
			triple[2] = 0.8;
		}
		break;
	case 2:
		if (M.getIndiceRonda() == 1)
		{
			if (J.valor_mano >= 12)
			{
				triple[0] = 0;
				triple[1] = 0.1;
				triple[2] = 0.9;
			}
			else if (J.valor_mano >= 7)
			{
				triple[0] = 0.05;
				triple[1] = 0.9;
				triple[2] = 0.05;
			}
			else
			{
				triple[0] = 0.9;
				triple[1] = 0.1;
				triple[2] = 0;
			}
		}
		else
		{
			if (J.valor_mano >= 7)
			{
				triple[0] = 0;
				triple[1] = 0.1;
				triple[2] = 0.9;
			}
			else if (J.valor_mano >= 2)
			{
				triple[0] = 0.05;
				triple[1] = 0.9;
				triple[2] = 0.05;
			}
			else
			{
				triple[0] = 0.9;
				triple[1] = 0.1;
				triple[2] = 0;
			}
		}
		break;
	case 3:
		triple[0] = 0.25;
		triple[1] = 0.7;
		triple[2] = 0.05;
		break;
	}
	}
}

int Algoritmo::obtenerAccionAct(Jugador J, Mesa M, int accionprevia)
{
	if (tipo == 4)
	{
		std::cout << "obtenerAccionAct ejecutada en ronda: " << M.getIndiceRonda() << std::endl;
		std::cout << "Accion elegida: 0" << std::endl;
		return 0;
	}
	else
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
		char url_aux[110];

		if (M.getIndiceRonda() == 0)
		{
			strcpy(url_aux, "http://localhost:8000/preflopact?a=");
			strcat(url_aux, (char*)accionprevia);

			url = url_aux;
		}
		else if (M.getIndiceRonda() == 1 || M.getIndiceRonda() == 2)
		{
			strcpy(url_aux, "http://localhost:8000/flopact?a=");
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

			url = url_aux;
		}
		else if (M.getIndiceRonda() == 3)
		{
			strcpy(url_aux, "http://localhost:8000/riveract?a=");
			strcat(url_aux, (char*)accionprevia);
			url = url_aux;

		}


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
		switch (tipo)
		{
		case 1:
			if (M.getIndiceRonda() == 1)
			{
				if (J.valor_mano >= 3.5)
				{
					triple[0] = 0.05;
					triple[1] = 0.1;
					triple[2] = 0.85;
				}
				else
				{
					triple[0] = 0.2;
					triple[1] = 0.25;
					triple[2] = 0.55;
				}
			}
			else
			{
				triple[0] = 0.05;
				triple[1] = 0.15;
				triple[2] = 0.8;
			}
			break;
		case 2:
			if (M.getIndiceRonda() == 1)
			{
				if (J.valor_mano >= 12)
				{
					triple[0] = 0;
					triple[1] = 0.1;
					triple[2] = 0.9;
				}
				else if (J.valor_mano >= 7)
				{
					triple[0] = 0.05;
					triple[1] = 0.9;
					triple[2] = 0.05;
				}
				else
				{
					triple[0] = 0.9;
					triple[1] = 0.1;
					triple[2] = 0;
				}
			}
			else
			{
				if (J.valor_mano >= 7)
				{
					triple[0] = 0;
					triple[1] = 0.1;
					triple[2] = 0.9;
				}
				else if (J.valor_mano >= 2)
				{
					triple[0] = 0.05;
					triple[1] = 0.9;
					triple[2] = 0.05;
				}
				else
				{
					triple[0] = 0.9;
					triple[1] = 0.1;
					triple[2] = 0;
				}
			}
			break;
		case 3:
			triple[0] = 0.25;
			triple[1] = 0.7;
			triple[2] = 0.05;
			break;
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



int Algoritmo::obtenerSubida(float apuesta, float apuesta_ini) 
{
	//Editar
	random r;
	float n = r.nrandomPorcent();
	int salida = apuesta + apuesta_ini * (n+1);
	return salida;
}