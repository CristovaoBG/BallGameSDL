#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "Linear.h"

#define ASSERT_STUFF

VEC2D SetVec2D(float x, float y)
{
	VEC2D vetor;
	vetor.x = x;
	vetor.y = y;
	return vetor;
}

/*
VEC2D ScanVec2D()
{
	VEC2D vetor;
	float x, y;
	printf("entre x e y:\n");
	scanf("%f", &x);
	getchar();
	scanf("%f", &y);
	vetor = SetVec2D(x, y);
	return vetor;
}
*/

void PrintfVec2D(VEC2D vet)
{
	printf("x = %.2f ;  y = %.2f\n", vet.x, vet.y);
}

	// a + b
VEC2D SomaVec2D(VEC2D a, VEC2D b)
{
	VEC2D c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

	// -a
VEC2D MenosVec2D(VEC2D a)
{
	a.x *= -1;
	a.y *= -1;
	return a;
}

	// a - b
VEC2D SubtraiVec2D(VEC2D a, VEC2D b)
{
	VEC2D c;
	c = SomaVec2D(a, MenosVec2D(b));
	return c;
}

VEC2D EscalarVec2D(float k, VEC2D a)
{
	a.x *= k;
	a.y *= k;
	return a;
}

float ProdutoInternoVec2D(VEC2D v1, VEC2D v2){
return v1.x*v2.x + v1.y*v2.y;
}

float QuadradoDoModuloVec2D(VEC2D v)
{
	float d;
	d = ProdutoInternoVec2D(v,v);
	return d;
}

// proj de v1 em v2
VEC2D ProjecaoOrtogonalVec2D(VEC2D v1, VEC2D v2) {

	float QMod = QuadradoDoModuloVec2D(v2);

	if (QMod == 0) {
		#ifdef ASSERT_STUFF
		assert(0);
		#endif
		return NuloVec2D();
	}

	float k = ProdutoInternoVec2D(v1,v2) / QMod;
	return EscalarVec2D(k,v2);
}

VEC2D GetVersorVec2D(VEC2D vetor){
	float tamanho = sqrt(QuadradoDoModuloVec2D(vetor));

	if (tamanho == 0) { //impede divisao por zero
		#ifdef ASSERT_STUFF
		assert(0);
		#endif
		return NuloVec2D();
	}

	vetor.x/=tamanho;
	vetor.y/=tamanho;
	return vetor;
}

void IncreaseVec2D(VEC2D v1, VEC2D v2){
	v1.x += v2.x;
	v1.y += v2.y;
}

VEC2D NuloVec2D(){
	VEC2D nulo;
	nulo.x = 0;
	nulo.y = 0;
	return nulo;
}

void Teste()
{	// atribui
	VEC2D vetor = SetVec2D(1, 2);
	assert(vetor.x == 1 && vetor.y == 2);	// mata se flag = 0
	// escalar
	vetor = EscalarVec2D(2, vetor);
	assert(vetor.x == 2 && vetor.y == 4);	// mata se flag = 0
	vetor.y--;		// agora y = 3
	// soma
	vetor = SomaVec2D(vetor, vetor);
	assert(vetor.x == 4 && vetor.y == 6);	// mata se flag = 0
	// subtracao
	vetor = SubtraiVec2D(vetor, vetor);
    assert(vetor.x == 0 && vetor.y == 0);
    //produto  interno e quadrado do modulo
    vetor = SetVec2D(3,4);
    assert(QuadradoDoModuloVec2D(vetor) == 25);
    //projecao
    VEC2D vetor2;
    vetor2 = SetVec2D(-3,4);
    vetor = ProjecaoOrtogonalVec2D(vetor, vetor2);
    assert(vetor.x && vetor.y);
    vetor =   SetVec2D(1,1);
    vetor2 = SetVec2D(1,0);
    vetor = ProjecaoOrtogonalVec2D(vetor, vetor2);
    assert(vetor.x==1 && vetor.y==0);
	//tamanho
    vetor = SetVec2D(13,13);
	vetor = GetVersorVec2D(vetor);	
	float tamanho = QuadradoDoModuloVec2D(vetor); //deve ser 1
	assert(tamanho < 1.1f && tamanho >0.9f);
}

VEC2D Soma90GrausVec2D(VEC2D vetor){
	VEC2D aux = NuloVec2D();
	aux.x = -(vetor.y);
	aux.y = vetor.x;
	return aux;
}

/*
int main()
{
	Teste();
	VEC2D a , b;
    a = SetVec2D(9,10);
	b = SetVec2D(8,4);
	a = ProjecaoOrtogonalVec2D(b,a);
	ImprimeVec2D(a);
	return 0;
}
*/







