#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Input.h"
#include "Render.h"
//#include "Player.h"

static bool keyState[INPUT_TOTAL];

int HandleInput(){
	int i;
	bool quit = false;
	static bool flagIsBegin = false;
	SDL_Event e;

	//se for a primeira vez, inicia o estado de cada elemento do vetor como falso (gambiarra?)
	if (flagIsBegin == false){
		for (i=0; i<INPUT_TOTAL; i++) keyState[i] = false;
		flagIsBegin = true; 
		}
	
	//limpa estado anterior das teclas de estado momentaneo
	for (i=PRESSED_UP; i <= RELEASED_MOUSE_LEFT; i++) keyState[i] = false;

	while( SDL_PollEvent( &e ) != 0 ) {	//Handle events on queue
		if( e.type == SDL_QUIT ) {
			keyState[INPUT_QUIT] = true;
		}

		else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
			switch( e.key.keysym.sym ) {
				case SDLK_UP: 
					keyState[PRESSING_UP] = true;
					keyState[PRESSED_UP] = true;
					break;
				case SDLK_DOWN:
					keyState[PRESSING_DOWN] = true; 
					keyState[PRESSED_DOWN] = true; 
					break;
				case SDLK_LEFT: 
					keyState[PRESSING_LEFT] = true; 
					keyState[PRESSED_LEFT] = true;
					break;
				case SDLK_RIGHT: 
					keyState[PRESSING_RIGHT] = true;
					keyState[PRESSED_RIGHT] = true; 
					break;
				case SDLK_ESCAPE: 
					keyState[PRESSING_ESC] = true; 
					keyState[PRESSED_ESC] = true;
					break;
				case SDLK_RETURN: 
					keyState[PRESSING_ENTER] = true;
					keyState[PRESSED_ENTER] = true; 
					break;
				case SDLK_SPACE: 
					keyState[PRESSING_SPACE] = true;
					keyState[PRESSED_SPACE] = true; 
					break;
				case SDLK_k:
					keyState[PRESSING_K] = true;
					keyState[PRESSED_K] = true; 
			}
		    }
		else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
			switch( e.key.keysym.sym ) {
				case SDLK_UP:
					keyState[PRESSING_UP] = false;
					keyState[RELEASED_UP] = true;
					break;
				case SDLK_DOWN:
					keyState[PRESSING_DOWN] = false;
					keyState[RELEASED_DOWN] = true; 
					break;
				case SDLK_LEFT:
					keyState[PRESSING_LEFT] = false;
					keyState[RELEASED_LEFT] = true;
					break;
				case SDLK_RIGHT: 
					keyState[PRESSING_RIGHT] = false;
					keyState[RELEASED_RIGHT] = true;
					break;
				case SDLK_ESCAPE: 
					keyState[PRESSING_ESC] = false;
					keyState[RELEASED_ESC] = true;
					break;
				case SDLK_RETURN: 
					keyState[PRESSING_ENTER] = false;
					keyState[RELEASED_ENTER] = true;
					break;
				case SDLK_SPACE: 
					keyState[PRESSING_SPACE] = false;
					keyState[RELEASED_SPACE] = true;
					break;
				case SDLK_k: 
					keyState[PRESSING_K] = false;
					keyState[RELEASED_K] = true;
					break;
			}
		}
		//se for evento no botao do mouse
		else if (e.type == SDL_MOUSEBUTTONDOWN){
			if (e.button.button == SDL_BUTTON_LEFT){
				keyState[PRESSING_MOUSE_LEFT] = true;
				keyState[PRESSED_MOUSE_LEFT] = true;
			}
		
		}
		else if (e.type == SDL_MOUSEBUTTONUP){
			if (e.button.button == SDL_BUTTON_LEFT){
				keyState[PRESSING_MOUSE_LEFT] = false;
				keyState[RELEASED_MOUSE_LEFT] = true;			
			}
		}

	}
	return quit;
}

bool InputState(int input){
	return keyState[input];	
} 

























