#include"head.h"


//Our custom windows
LWindow::LWindow(){
	//Initialize non-existant window
	mWindow = NULL;
	mRenderer = NULL;
}

bool LWindow::init(){
	//Create window
	mWindow = SDL_CreateWindow( "GAME OVER Brick Breaker 2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if(mWindow != NULL){

		//Create renderer for window
		mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if(mRenderer == NULL){
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( mWindow );
			mWindow = NULL;
        }else{
			//Initialize renderer color
			SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			mWindowID = SDL_GetWindowID( mWindow );
		}
	}else{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return mWindow != NULL && mRenderer != NULL;
}

bool LWindow::handleEvent( SDL_Event& e ){
	if(e.type == SDL_WINDOWEVENT){
        if(e.window.event == SDL_WINDOWEVENT_CLOSE){
			SDL_HideWindow( mWindow );
			free();
			return false;
		}
	}
	return true;
}

void LWindow::renderImage(LTexture& image,int x, int y){
	image.render(mRenderer, x, y);	
}

void LWindow::free(){
	if( mWindow != NULL ){
		SDL_DestroyWindow( mWindow );
	}
}


