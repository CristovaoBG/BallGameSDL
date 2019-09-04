#include "Aresta.h"


RETA Aresta::GetReta(){
	return reta;
}

Aresta::Aresta(RETA r){
	reta = r;
	quina = false;
}


void Aresta::Render(){
	DesenhaVecNaPosicao(reta.vec, reta.pos);
}


bool Aresta::GetQuina(){
	return quina;
}

void Aresta::SetReta(RETA r){
	reta = r;
}

VEC2D Aresta::GetVecDistancia(VEC2D ponto){
	VEC2D aux;

	aux = this->GetPontoDeColisao(ponto);

	//vetor reta -> ponto
	ponto = SubtraiVec2D(ponto, reta.pos);

	// aux = vetor ponto -> reta
	aux = SubtraiVec2D(ponto, aux);


	return aux;
}


VEC2D Aresta::GetPontoDeColisao(VEC2D ponto){
	quina = false;
	VEC2D aux;

	// vetor reta.p1->ponto (altera a origem para o inicio da reta)
	ponto = SubtraiVec2D(ponto, reta.pos);

	//aux = projecao
	aux = ProjecaoOrtogonalVec2D(ponto,reta.vec);

	//mantem nos limites da reta
	if ((aux.x > 0 && reta.vec.x <0) || (aux.x < 0 && reta.vec.x >0) ||
	    (aux.y > 0 && reta.vec.y <0) || (aux.y < 0 && reta.vec.y >0)) {
		aux = NuloVec2D();
		quina = true;
	}
	else if (QuadradoDoModuloVec2D(aux) > QuadradoDoModuloVec2D(reta.vec)){
		aux = reta.vec;
		quina = true;
		}

	// aux = vetor ponto -> reta
	//aux = SubtraiVec2D(ponto, aux);


	return aux;
}


ListaAresta::ListaAresta(){

	cabeca = (Lista *) malloc(sizeof(Lista));
	cabeca->prox = NULL;
	cabeca->aresta = NULL;
	fim = cabeca;
	cursor = cabeca;
	
}

void ListaAresta::Add(RETA r){
	fim->aresta = new Aresta(r);
	//ja adiciona o proximo, vazio.
	fim->prox = (Lista *) malloc(sizeof(Lista));
	fim = fim->prox;
	fim->prox = NULL;
	fim->aresta = NULL;
}

void ListaAresta::LiberaLista(Lista * c){

	if (c !=NULL){
		if (c->prox!= NULL)
			this->LiberaLista(c->prox);

		if (c->aresta!=NULL) delete[] c->aresta;
		free(c);
	}
}


void ListaAresta::Reinicia(){
	cursor = cabeca;
}


Aresta* ListaAresta::Prox(){
	Aresta *esta;
	if (cursor != NULL){
		esta = cursor->aresta; 
		cursor = cursor->prox;
	}
	else {
		esta = NULL;
	}
	

	return esta;
}


void ListaAresta::Render(){

	Aresta *aresta;

	this->Reinicia();

	do {	
		aresta = this->Prox();
		if (aresta!=NULL){
			aresta->Render();
		}
	} while (aresta!=NULL);

	this->Reinicia();

}

ListaAresta::~ListaAresta(){
	cursor = cabeca;
	this->LiberaLista(cursor);

}











