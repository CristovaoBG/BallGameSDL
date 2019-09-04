#include <stdio.h>
#include "Render.h"
#include "Linear.h"
#include "Input.h"
//#include "math.h"
#include "Object.h"
#include "Aresta.h"
#include "Geometry.h"
#include "time.h"

void Wait(int milli){
	int ini;
	ini = clock();
	while(clock() - ini < milli * CLOCKS_PER_SEC/1000 );
}


void OldMouseLines(ListaAresta *lista){

	RETA reta;

	static bool durante = false;

	int 	x = 0,
		y = 0;

	static VEC2D	pt1		=     	NuloVec2D(),
			pt2		=     	NuloVec2D(),
			ptDurante	= 	NuloVec2D();



	if (InputState(PRESSED_MOUSE_LEFT)){
		SDL_GetMouseState( &x, &y );
		pt1 = SetVec2D(x,y);
		durante = true;
	}
	else if(InputState(RELEASED_MOUSE_LEFT)){
		SDL_GetMouseState( &x, &y );
		pt2 = SetVec2D(x,y);
		reta = CriaReta(pt1, pt2);
		if(QuadradoDoModuloVec2D(reta.vec) > 4) lista->Add(reta);
		durante = false;
	}
	else{
		SDL_GetMouseState( &x, &y );
		ptDurante = SetVec2D(x,y);
	}

	if (durante){
		reta = CriaReta(pt1, ptDurante);
		DesenhaReta(reta);
	}
	//printf("%d\n", durante);
	
	
}


void MouseLines(ListaAresta *lista){

	RETA reta;

	int 	x = 0,
		y = 0;

	static VEC2D	pt1		=     	NuloVec2D(),
			pt2		= 	NuloVec2D();



	if (InputState(PRESSED_MOUSE_LEFT)){
		SDL_GetMouseState( &x, &y );
		pt1 = SetVec2D(x,y);
	}
	else if(InputState(PRESSING_MOUSE_LEFT)){
		SDL_GetMouseState( &x, &y );
		pt2 = SetVec2D(x,y);
		reta = CriaReta(pt1, pt2);
		if(QuadradoDoModuloVec2D(reta.vec) > 100) {
			lista->Add(reta);
			pt1 = pt2;
		}
		DesenhaReta(reta);

	}
	//printf("%d\n", durante);
	
	
}



void FrameByFrame() {

	static bool frames = false;

	if (InputState(PRESSED_ESC)){
		frames = (frames == true)? false: true;
	}

	while ( !InputState(PRESSED_ENTER) && frames && !InputState(INPUT_QUIT)){
		HandleInput();
		if (InputState(PRESSED_ESC)){
			frames = (frames == true)? false: true;
		}
	}		
}


int main(){

	init();
	
	bool quit = false;

	//pos, raio 
	CIRCULO c = CriaCirculo(SetVec2D(400,200), 22);

/*
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480
*/
	ListaAresta ls;

	Objeto player(c);

/******************************************/
	VEC2D r_pt1 = SetVec2D(0,0);
	VEC2D r_pt2 = SetVec2D(0,480);

	RETA reta = CriaReta(r_pt1,r_pt2);

	ls.Add(reta);

/******************************************/
	r_pt1 = SetVec2D(0,480);
	r_pt2 = SetVec2D(640,480);

	reta = CriaReta(r_pt1,r_pt2);

	ls.Add(reta);
/******************************************/
	r_pt1 = SetVec2D(640,480);
	r_pt2 = SetVec2D(640,0);

	reta = CriaReta(r_pt1,r_pt2);

	ls.Add(reta);
/******************************************/
	r_pt1 = SetVec2D(640,0);
	r_pt2 = SetVec2D(0,0);

	reta = CriaReta(r_pt1,r_pt2);

	ls.Add(reta);
/******************************************
	r_pt1 = SetVec2D(320,0);
	r_pt2 = SetVec2D(320,480);

	reta = CriaReta(r_pt1,r_pt2);

	ls.Add(reta);
******************************************/

/*
	r_pt1 = SetVec2D(100,200);
	r_pt2 = SetVec2D(500,200);
	reta = CriaReta(r_pt1,r_pt2);
	ls.Add(reta);
	r_pt1 = SetVec2D(100,200);
	r_pt2 = SetVec2D(500,100);
	reta = CriaReta(r_pt1,r_pt2);
	ls.Add(reta);
*/	
	while(!quit){

		HandleInput();

		if (InputState(INPUT_QUIT)){
			quit = true;
		}

		MouseLines(&ls);

		FrameByFrame();

		player.Step();

		player.Colide(&ls);

		player.Render();
		ls.Render();

		UpdateScreen();
	}
	
	close();


	return 0;
}


