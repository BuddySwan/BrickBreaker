#include"head.h"

//initializes x,y position and width and height. bricks are represented as essentially a
//SDL_Rect. makes collsion easier adn everything else as well trust me
Brick::Brick(int bx, int by, int bw, int bh, int life){
	x = bx;
	y = by;
	w = bw;
	h = bh;
	hit = false;
	Life = life;
	color = 'b';

	PWRLife = false;
}

//essentialy just changes color to represent health loss
void Brick::takeHealth(){

	Life--;
	if(Life==0){
		hit = true;
	}
	/*
	if(Life==3){
		Life--;
		hit = false;
	}else if(Life==2){
		Life--;
		hit = false;
	}else if(Life==1){
		hit = true;
	}
	*/
}

//renders correct color of brick
void Brick::render(SDL_Renderer* gRenderer, LTexture& gBlueBrick, LTexture& gPurpleBrick, LTexture& gOrangeBrick){
	switch(Life){
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

