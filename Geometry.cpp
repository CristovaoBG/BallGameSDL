#include "Geometry.h"


void DesenhaReta (RETA reta){
	DesenhaVecNaPosicao(reta.vec, reta.pos);
}

void DesenhaLinha(VEC2D pt1, VEC2D pt2 ){
	SDL_SetRenderDrawColor( gRenderer, BRANCO, 0xFF );		
	SDL_RenderDrawLine( gRenderer, pt1.x, pt1.y, pt2.x, pt2.y );
}

void DesenhaPonto(VEC2D pt){
	SDL_SetRenderDrawColor( gRenderer, VERMELHO, 0xFF );		
	SDL_RenderDrawPoint( gRenderer, pt.x, pt.y );
}

void DesenhaPontoNaPosicao(VEC2D pt, VEC2D relativo){
	DesenhaCirculo(SomaVec2D(relativo, pt), 5, 8);
}

void DesenhaVecNaPosicao(VEC2D vetor, VEC2D relativo){

	DesenhaLinha(relativo, SomaVec2D(relativo, vetor) );
}

void DesenhaCirculo(VEC2D pos, float raio, int definicao){

	VEC2D v1,v2;

	int i;

	for (i=0; i<definicao; i++){

		v1.x = raio*cos(2*M_PI*i/definicao);
		v1.y = raio*sin(2*M_PI*i/definicao);
		
		v1 = SomaVec2D(pos, v1);

		v2.x = raio*cos(2*M_PI*(i+1)/definicao);
		v2.y = raio*sin(2*M_PI*(i+1)/definicao);

		v2 = SomaVec2D(pos, v2);

		DesenhaLinha(v1,v2);
	
	}
}

VEC2D VecDistanciaPontoReta(RETA reta, VEC2D ponto, bool *quina){
	*quina = false;
	VEC2D aux;
	// vetor reta.p1->ponto (altera a origem para o inicio da reta)
	ponto = SubtraiVec2D(ponto, reta.pos);
	//aux = projecao
	aux = ProjecaoOrtogonalVec2D(ponto,reta.vec);

	if (QuadradoDoModuloVec2D(aux) > QuadradoDoModuloVec2D(reta.vec)){
		aux = reta.vec;
		*quina = true;
		}
	else if ((aux.x > 0 && reta.vec.x <0) || (aux.x < 0 && reta.vec.x >0) ||
	    (aux.y > 0 && reta.vec.y <0) || (aux.y < 0 && reta.vec.y >0)) {
		aux = NuloVec2D();
		*quina = true;
	}

	// aux = vetor ponto -> reta
	aux = SubtraiVec2D(ponto, aux);

	return aux;
	
}

CIRCULO CriaCirculo (VEC2D posicao, float raio){
	CIRCULO novo;
	novo.pos = posicao;
	novo.r = raio;
	return novo;
}

RETA CriaReta(VEC2D pt1, VEC2D pt2){
	RETA reta;
	reta.pos = pt1;
	reta.vec = SubtraiVec2D(pt2,pt1);
	return reta;
}

