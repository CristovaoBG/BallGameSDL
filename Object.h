#ifndef _objectH_
#define _objectH_

#include <stdio.h>
#include "Render.h"
#include "Linear.h"
#include "Input.h"
#include "math.h"
#include "Geometry.h"
#include "Aresta.h"


class CentreOfMass{
	public:
		CentreOfMass(VEC2D posicao);
		void Render();
		void Step();
		void AddImpulse(VEC2D impulse, VEC2D position);
		VEC2D GetPos();
	private:
		CIRCULO c;
		VEC2D vecVel, prevPos, pos, r;
		float acc, gravidade, jump;
};



class Objeto{
	public:
		Objeto(CIRCULO circulo);
		void Colide(ListaAresta *lsAresta);
		void Step();
		void Render();
		VEC2D GetPos();
		//VEC2D GetPrevPos();
		//void SetPos();
		//void SetVel();


	private:
		//void AjustaPosNaReta(VEC2D vecRetaAnterior, VEC2D vecRetaAtual, VEC2D vecDist);
		VEC2D TangenciaPosicao(Aresta *aresta, VEC2D pos);
		VEC2D TangenciaVelocidade(Aresta *aresta);
		CIRCULO c;
		VEC2D vecVel, prevPos, pos, r;
		float acc, gravidade, jump;
		
};


#endif
