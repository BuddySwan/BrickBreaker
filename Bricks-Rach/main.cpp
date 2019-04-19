#include"head.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gBackGround;
LTexture gPaddle;
LTexture gBall;
LTexture gBlueBrick;
LTexture gPurpleBrick;
LTexture gOrangeBrick;
LTexture gTextTexture; //this is what says "Score: "
LTexture gLives;
LTexture gScoreNum;  //actual moving score 
LTexture gLost;
LTexture gFinalScore;

bool init(){
	bool success = true;
	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialize\n");
		success = false;
	}else{
		if(TTF_Init()<0){
			printf("SDL TTF could not initialize\n");
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
/*    if(!gBackGround.loadFromFile("BackGround.png", gRenderer)){
        printf("failed to load background\n");
        success = false;
    }
*/
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
	if(!gLives.loadFromFile("Lives.png", gRenderer)){
		printf("failed to load hearts\n");
		success = false;
	}
	//I added new images so youll have to update those
/*
   if(!gPaddle.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Paddle.png", gRenderer)){
        printf("Failed ot load Me pic\n");
        success = false;
    }
    //PUT BACKGROUND HERE
    if(!gBackGround.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/background.png", gRenderer)){
        printf("failed to load background\n");
        success = false;
    }
    if(!gBall.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Dot.png", gRenderer)){
        printf("failed to load ball\n");
        success = false;
    }
    if(!gBlueBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/BlueBrick.png", gRenderer)){
        printf("failed to load blue\n");
        success = false;
    }
    if(!gPurpleBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/PurpleBrick.png", gRenderer)){
        printf("failed to load purple\n");
        success = false;
    }
    if(!gOrangeBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/OrangeBrick.png", gRenderer)){
        printf("failed to load orange\n");
        success = false;
    }
*/
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

			SDL_Event e;

			bool quit = false, Lose_Life = false, begin = false, GameLost = false, endGame = false;
			int pX = 300, pY = 450, bX = 330, bY = 385, brickW = gBlueBrick.getWidth(), brickH = gBlueBrick.getHeight(), score = 0;
			std::string inputText = "Score: ", scoreNum;

			std::stringstream buffer;

			Paddle Paddle(pX,pY,0,0); 
			Ball Ball(bX,bY,5,-5);
	
			std::list<Brick* > bricks;
			std::list<Brick* >::iterator lit;

			//Lost window, will put image in later
			LWindow gLostWindow;

			//for displaying score
			SDL_Color Black = {0,0,0,0}, White = {255,255,255,255};
			TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf",24);
			gTextTexture.loadText(gRenderer, inputText, font, Black);	
			TTF_Font* finalFont = TTF_OpenFont("Roboto-Black.ttf", 36);



			Paddle.Set_Dimensions(gPaddle.getHeight(), gPaddle.getWidth());
			Ball.Set_Dimensions(gBall.getHeight(), gBall.getHeight());

			createBricks(bricks,brickW,brickH);

			while(!quit){
				
				//turn int score into string so it can be rendered
		        buffer.clear();
                buffer << Ball.Score;
                buffer >> scoreNum;

				//load losing window
				if(Ball.Lives==0 && GameLost==false){
					gLostWindow.init();
					gLost.loadFromFile("lost.png", gLostWindow.mRenderer);
					gFinalScore.loadText(gLostWindow.mRenderer, scoreNum, finalFont, White);
					GameLost = true;
				}

				
				//poll events for correct window
				while(SDL_PollEvent(&e)!=0){
					if(GameLost==true){
						GameLost = gLostWindow.handleEvent(e);
						//reset game
						if(GameLost==false){
							Reset(bricks,Ball,brickW,brickH);
							gLost.free();
							gFinalScore.free();
						}
					}else{
						if(e.type==SDL_QUIT){
							quit = true;
						}
						Paddle.handleEvent(e);
						if(begin==false){
							begin = Ball.begin(e);
						}
					}
					
				}
				//if game is lost a new window pops up. it can be turned into a tutorial window or we can keep it 
				//as is.
				if(GameLost==true){
					gLostWindow.focus();
					SDL_SetRenderDrawColor(gLostWindow.mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear(gLostWindow.mRenderer);
                    gLostWindow.renderImage(gLost,0,0);
                    gLostWindow.renderImage(gFinalScore,150,70);
					SDL_RenderPresent(gLostWindow.mRenderer);
				}else{

					gScoreNum.loadText(gRenderer, scoreNum, font, Black);

					Paddle.move();

					if(Lose_Life==true){
						Ball.setXY(bX, bY);
						Ball.setV(5, -5);
						begin = false;
						Lose_Life = false;
					}

					//move ball when spacebar is pressed, otherwise follow paddle
					if(begin==true){
						Lose_Life = Ball.move(bricks, Paddle);
					}else{
						Ball.setXY(Paddle.getX()+30, Paddle.getY()-35);
					}

		
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);
					SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);


					Paddle.render(gPaddle, gRenderer);
					Ball.render(gBall, gRenderer);


					//render bricks
					for(lit = bricks.begin();lit!=bricks.end();lit++){
						//render pic of brick
						(*lit)->render(gRenderer,gBlueBrick, gPurpleBrick, gOrangeBrick);
					}

					for(int i=0; i<Ball.Lives;i++){
						gLives.render(gRenderer, 10 + gLives.getWidth()*i, 10);
					}
	
					gTextTexture.render(gRenderer, 500, 20);
					gScoreNum.render(gRenderer, 600, 20);

					/*
					if(bricks.empty()){
						createBricks(bricks,brickW,brickH);
					}
					*/

					SDL_RenderPresent(gRenderer);
				}//game over 

			}//while

			deleteBricks(bricks);
		}
	}

	close();
	return 0;

}
