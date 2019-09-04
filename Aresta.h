#ifndef _arestaH_
#define _arestaH_

#include <stdio.h>
#include "Render.h"
#include "Linear.h"
#include "Input.h"
#include "math.h"
#include "Geometry.h"

class Aresta{
	public:
		Aresta(RETA r = CriaReta(NuloVec2D(), SetVec2D(200,200)));
		VEC2D GetVecDistancia(VEC2D ponto);
		VEC2D GetPontoDeColisao(VEC2D ponto);
		void SetReta(RETA r);
		void Render();
		bool GetQuina();
		RETA GetReta();
	private:
		bool quina;
		RETA reta;
};



typedef struct Lista{
	Aresta *aresta;
	struct Lista *prox;
}Lista;


class ListaAresta{
	public: 
		ListaAresta();
		~ListaAresta();
		Aresta* Prox();
		void Reinicia();
		void Add(RETA r);
		void LiberaLista(Lista * c);
		void Render();
	private:
		RETA reta;
		Lista* cabeca, *cursor, *fim;

		
};


#endif
