#ifndef _geometryH_
#define _geometryH_

#include <stdio.h>
#include "Render.h"
#include "Linear.h"
#include "Input.h"
#include "math.h"

#define PRETO 	  0x00, 0x00, 0x00
#define BRANCO 	  0xFF, 0xFF, 0xFF
#define AZUL  	  0x00, 0x00, 0xFF
#define VERMELHO  0xFF, 0x00, 0x00
#define VERDE 	  0x00, 0xFF, 0x00


typedef struct Circle{
	VEC2D pos;
	float r;
} CIRCULO;


typedef struct reta{

	VEC2D pos; //posicao do vetor reta (origem)
	VEC2D vec; //vetor si
} RETA;

void DesenhaReta (RETA reta);
void DesenhaLinha(VEC2D pt1, VEC2D pt2 );
void DesenhaPonto(VEC2D pt);
void DesenhaPontoNaPosicao(VEC2D pt, VEC2D relativo);
void DesenhaVecNaPosicao(VEC2D vetor, VEC2D relativo);
void DesenhaCirculo(VEC2D pos, float raio, int definicao);

VEC2D   VecDistanciaPontoReta(RETA reta, VEC2D ponto, bool *quina);
CIRCULO CriaCirculo (VEC2D posicao, float raio);
RETA    CriaReta(VEC2D pt1, VEC2D pt2);




#endif
