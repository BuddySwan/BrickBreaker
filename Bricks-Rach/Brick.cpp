#include"head.h"

//initializes x,y position and width and height. bricks are represented as essentially a
//SDL_Rect. makes collsion easier adn everything else as well trust me
Brick::Brick(int bx, int by, int bw, int bh, int hits){
	x = bx;
	y = by;
	w = bw;
	h = bh;
	hit = false;
    hitsLeft = hits;
	color = 'b';
}

//essentialy just changes color to represent health loss
void Brick::takeHealth(){
	
	if(color=='b'){
		color = 'p';
		hit = false;
	}else if(color=='p'){
		color = 'o';
		hit = false;
	}else if(color=='o'){
		hit = true;
	}
}

//renders correct color of brick
void Brick::render(SDL_Renderer* gRenderer, LTexture& gBlueBrick, LTexture& gPurpleBrick, LTexture& gOrangeBrick){
	switch(hitsLeft){
		case 3:
			gBlueBrick.render(gRenderer,x,y);
			break;
		case 2:
			gPurpleBrick.render(gRenderer,x,y);
			break;
		case 1:
			gOrangeBrick.render(gRenderer,x,y);
			break;
	}
}

