#include <math.h>
#include "Object.h"

Objeto::Objeto(CIRCULO circulo){
	c = circulo;
	r = c.pos;
	pos = SomaVec2D(c.pos, r);
	prevPos = pos;
	vecVel = NuloVec2D();
	jump = 15;
	acc = 0.5;
	gravidade = 0.5;
}

void Objeto::Colide(ListaAresta *lsAresta){

	VEC2D   aux = NuloVec2D(),
			vecDist = NuloVec2D(),
			vecDeslocamento = NuloVec2D(),
			vecPrevDist = NuloVec2D(),
			novaPos = NuloVec2D();

	bool querDeslizar = true;
		
	int colisao = 0;

	float distancia = 0;

	Aresta *aresta = NULL;

	lsAresta->Reinicia();

	do {
		aresta = lsAresta->Prox();

		//if (colisoes > 2) break;
		if (aresta != NULL ){

			// vetor reta -> ponto
			vecDist = aresta->GetVecDistancia(c.pos);

			// Delocamento entre os frames
			vecDeslocamento = SubtraiVec2D(c.pos, prevPos);

			// distancia do ponto e da reta ao quadrado
			distancia = QuadradoDoModuloVec2D(vecDist);

			//componente do deslocamento na direcao da normal da reta\/

			if(distancia >= c.r*c.r){
				aux = ProjecaoOrtogonalVec2D(vecDeslocamento, aresta->GetReta().vec); 
				aux = SubtraiVec2D(vecDeslocamento, aux); 
				//caso em que ha a possibilidade de atravessar
				if ( QuadradoDoModuloVec2D(aux) > c.r*c.r ){
					vecPrevDist = aresta->GetVecDistancia(prevPos);
					//se atravessou, esses versores serao opostos, portanto a soma deve ser zero 
					aux = SomaVec2D (GetVersorVec2D(vecDist),GetVersorVec2D(vecPrevDist));
					if(QuadradoDoModuloVec2D(aux) < 0.1) {			//significa que atravessou
						colisao++;
						c.pos = SubtraiVec2D(c.pos, vecDeslocamento);	//volta
						c.pos = TangenciaPosicao(aresta, c.pos);
						vecVel = TangenciaVelocidade(aresta);
						printf("atravessou cara\n");
						if (!aresta->GetQuina() && querDeslizar == true){
							querDeslizar = true;	
							novaPos = c.pos;
							novaPos = SomaVec2D(novaPos,vecVel);
						}
						else{
							querDeslizar = false;
						}
						
					}
				}
			}
			//se distancia < c.r*c.r
			else{
				//caso critico
				if(distancia < c.r*c.r*1/3){
					colisao++;
					c.pos = SubtraiVec2D(c.pos, vecDeslocamento);	//volta
					c.pos = TangenciaPosicao(aresta, c.pos);
					vecVel = TangenciaVelocidade(aresta);

					if (!aresta->GetQuina() && querDeslizar == true){
						querDeslizar = true;	
						novaPos = c.pos;
						novaPos = SomaVec2D(novaPos,vecVel);
					}
					else{
							querDeslizar = false;
					}	
				}
				// caso natural
				else {
					querDeslizar = false;
					colisao++;
					c.pos = TangenciaPosicao(aresta, c.pos);
					vecVel = TangenciaVelocidade(aresta);
				}

			}

		} // fim se aresta diferente de null

	} while(aresta!=NULL);

	if(colisao == 1 && querDeslizar) {
		c.pos = novaPos;
		printf(":)\n");
		}

	lsAresta->Reinicia();

}



VEC2D Objeto::TangenciaPosicao(Aresta *aresta, VEC2D pos){

	VEC2D   vecDist = NuloVec2D(),
		aux = NuloVec2D();
	

	vecDist = aresta->GetVecDistancia(c.pos);	//recalcula distancia ponto reta (nao deveria pertencer a essa funcao)
	aux = GetVersorVec2D(vecDist);			
	aux = EscalarVec2D(c.r,aux);			//vetor do raio (circ -> centro)
	aux = SubtraiVec2D(aux, vecDist);		//vetor da distancia entre reta e a circunf. (circ -> reta)
	return SomaVec2D(aux,c.pos);			//ajusta à tangente
}

VEC2D Objeto::TangenciaVelocidade(Aresta *aresta){
	VEC2D aux = NuloVec2D();
	if ( !aresta->GetQuina() ) {
		//mais preciso, mas nao funcina nas quinas
		return ProjecaoOrtogonalVec2D (vecVel, aresta->GetReta().vec);
	}
	//else
	//menos preciso, mas nas quinas eh suficiente
	//calcula a nova velocidade projetando-a no vetor dPos/dt (teoricamente)
	aux = SubtraiVec2D(c.pos,prevPos);
	if(ProdutoInternoVec2D(vecVel,aux) != 0){
		return ProjecaoOrtogonalVec2D (vecVel, aux);
	}
	return NuloVec2D();		
}

VEC2D Objeto::GetPos(){
	return c.pos;
}

void Objeto::Step(){
	prevPos = c.pos;

	vecVel.y += gravidade;

	if (InputState(PRESSING_LEFT))
		vecVel.x -= acc;
	if (InputState(PRESSING_RIGHT))
		vecVel.x += acc;
	if (InputState(PRESSED_UP))
		vecVel.y -= jump;
	if (InputState(PRESSING_DOWN))
		vecVel.y += acc;


	c.pos = SomaVec2D(c.pos, vecVel);
}

void Objeto::Render(){
	DesenhaCirculo(c.pos, c.r, 16);
}

/************************************************/


CentreOfMass::CentreOfMass(VEC2D posicao){
		vecVel = NuloVec2D();
		prevPos = posicao;
		pos = posicao;
		acc = 0.5;
		gravidade = 0.4;
		jump = 15;
		c = CriaCirculo(pos, 15);

}

void CentreOfMass::Step(){
	prevPos = c.pos;

	vecVel.y += gravidade;

	if (InputState(PRESSING_LEFT))
		vecVel.x -= acc;
	if (InputState(PRESSING_RIGHT))
		vecVel.x += acc;
	if (InputState(PRESSED_UP))
		vecVel.y -= jump;
	if (InputState(PRESSING_DOWN))
		vecVel.y += acc;


	c.pos = SomaVec2D(c.pos, vecVel);
}


void CentreOfMass::Render(){
	DesenhaCirculo(pos, c.r, 16);
}










