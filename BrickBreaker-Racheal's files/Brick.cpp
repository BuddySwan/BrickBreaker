#include"head.h"

//initializes x,y position and width and height. bricks are represented as essentially a
//SDL_Rect. makes collsion easier adn everything else as well trust me
Brick::Brick(int bx, int by, int bw, int bh){
	x = bx;
	y = by;
	w = bw;
	h = bh;
	hit = false;
	color = 'b';
}

//essentialy just changes color to represent health loss
void Brick::takeHealth(){
	
	if(color=='b'){
		color = 'p';
	}else if(color=='p'){
		color = 'o';
	}else if(color=='o'){
		hit = true;
	}
}

//renders correct color of brick
void Brick::render(SDL_Renderer* gRenderer, LTexture& gBlueBrick, LTexture& gPurpleBrick, LTexture& gOrangeBrick){
	switch(color){
		case 'b':
			gBlueBrick.render(gRenderer,x,y);
			break;
		case 'p':
			gPurpleBrick.render(gRenderer,x,y);
			break;
		case 'o':
			gOrangeBrick.render(gRenderer,x,y);
			break;
	}
}
