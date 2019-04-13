#include"head.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gBackGround;
LTexture gPaddle;
LTexture gBall;
LTexture gBlueBrick;
LTexture gPurpleBrick;
LTexture gOrangeBrick;

bool init(){
	bool success = true;
	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialize\n");
		success = false;
	}else{
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")){
			printf("Warning: linear texture filtering not enabled\n");
		}
		//create window
		gWindow = SDL_CreateWindow("Brick Breaker 1.0\n",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Window could not be created\n");
			success = false;
		}else{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer==NULL){
				printf("Renderer could not be created\n");
				success = false;
			}else{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags)& imgFlags)){
					printf("SDL_image could not initialize\n");
					success = false;
				}
			}

		}
	}
	return success;
}

//these are all MY images which we can change later
bool loadMedia(){
    bool success = true;
    //PUT ME HERE
    if(!gPaddle.loadFromFile("Paddle.png", gRenderer)){
        printf("Failed ot load Me pic\n");
        success = false;
    }
    //PUT BACKGROUND HERE
    if(!gBackGround.loadFromFile("BackGround.png", gRenderer)){
        printf("failed to load background\n");
        success = false;
    }
	if(!gBall.loadFromFile("Dot.png", gRenderer)){
		printf("failed to load ball\n");
		success = false;
	}
	if(!gBlueBrick.loadFromFile("BlueBrick.png", gRenderer)){
		printf("failed to load blue\n");
		success = false;
	}
	if(!gPurpleBrick.loadFromFile("PurpleBrick.png", gRenderer)){
		printf("failed to load purple\n");
		success = false;
	}
	if(!gOrangeBrick.loadFromFile("OrangeBrick.png", gRenderer)){
		printf("failed to load orange\n");
		success = false;
	}
    return success;	
}

void close(){
	gPaddle.free();
	gBall.free();
	gBackGround.free();
	gBlueBrick.free();
	gPurpleBrick.free();
	gOrangeBrick.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[]){
	if(!init()){
		printf("failed to initialize\n");
	}else{
		if(!loadMedia()){
			printf("Failed to load media\n");
		}else{			
			
			bool quit = false, Lose_Life = false, begin = false;
			SDL_Event e;
			std::list<Brick > bricks;
			int pX = 300, pY = 450, bX = 330, bY = 385, sign_x = 1, sign_y = -1, brickW = gBlueBrick.getWidth(), brickH = gBlueBrick.getHeight();
			Paddle Paddle(pX,pY,0,0); 
			Ball Ball(bX,bY,5,5);
			std::list<Brick >::iterator lit;


			//add paddle to objects to collide with
			addObject(bricks, pX, pY, gPaddle.getWidth(), gPaddle.getHeight());

			Paddle.Set_Dimensions(gPaddle.getHeight(), gPaddle.getWidth());
			Ball.Set_Dimensions(gBall.getHeight(), gBall.getHeight());
			
			createBricks(bricks,brickW,brickH);
			
			while(!quit){

				while(SDL_PollEvent(&e)!=0){
					if(e.type==SDL_QUIT){
						quit = true;
					}
					//handle input for the paddle
					Paddle.handleEvent(e);
					if(begin==false){
						begin = Ball.begin(e);
					}
				}
				
				Paddle.move();
				//paddle will always be first element in object vector
				lit = bricks.begin();
				lit->x = Paddle.getX();
				lit->y = Paddle.getY();

				if(Lose_Life==true){
					Ball.setXY(bX, bY);
					sign_x = 1;
					sign_y = -1;
					begin = false;
					Lose_Life = false;
				}
				
				//move ball when spacebar is pressed, otherwise follow paddle
				if(begin==true){
					Lose_Life = Ball.move(bricks, sign_x, sign_y);
				}else{
					Ball.setXY(Paddle.getX()+30, Paddle.getY()-35);
				}

				//clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//render wall
				SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);

				Paddle.render(gPaddle, gRenderer);
				Ball.render(gBall, gRenderer);

		
				//render bricks (starts at paddle bc paddle is element one but it wont do anything)
				lit = bricks.begin();
				lit++;

				//I have it where it only checks collison and renders it if it doesnt have zero health.
				//I keep getting this weird glitch where bricks randomly delete themselves after one hits zero 
				//health when I actually delete them from the list?
				for(lit;lit!=bricks.end();lit++){
					//render pic of brick
					if(lit->hit==false){
						lit->render(gRenderer,gBlueBrick, gPurpleBrick, gOrangeBrick);
					}
				}

			
				//update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;

}

