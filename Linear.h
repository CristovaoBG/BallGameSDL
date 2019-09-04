#ifndef _linearH_
#define _linearH_

typedef struct VEC2D {
	float x;
	float y;
} VEC2D;

//imprime com printf
void PrintfVec2D(VEC2D vet);
// V
VEC2D SetVec2D(float x, float y);
// V1 + V2
VEC2D SomaVec2D(VEC2D a, VEC2D b);
// -V
VEC2D MenosVec2D(VEC2D a);
// V1 - V2
VEC2D SubtraiVec2D(VEC2D a, VEC2D b);
// k * V
VEC2D EscalarVec2D(float k, VEC2D a);
// V1 * V2
float  ProdutoInternoVec2D(VEC2D v1, VEC2D v2);
// V1 * V1
float QuadradoDoModuloVec2D(VEC2D v);
// proj V1 -> V2
VEC2D ProjecaoOrtogonalVec2D(VEC2D v1, VEC2D v2);
// V / |V|
VEC2D GetVersorVec2D(VEC2D vetor);
// V1 += V2;
void IncreaseVec2D(VEC2D v1, VEC2D v2);
// vetor nulo
VEC2D NuloVec2D();
// vetor distancia entre ponto e reta
VEC2D PontoRetaVEC2D(VEC2D pReta1, VEC2D pReta2, VEC2D ponto);
// Rotaciona 90 grus
VEC2D Soma90GrausVec2D(VEC2D vetor);




#endif
