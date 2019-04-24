#include"head.h"
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gBackGround;
LTexture gPaddle;
LTexture gLongPaddle;
LTexture gBall;
LTexture gBlueBrick;
LTexture gPurpleBrick;
LTexture gOrangeBrick;
LTexture gStaticBrick;
LTexture gLifeBrick;
LTexture gLongBrick; //to add the long paddle powerup
LTexture gFastBrick;
LTexture gTextTexture; //this is what says "Score: "
LTexture gLives;    //heart image
LTexture gScoreNum;  //actual moving score 
LTexture gLost;
LTexture gStartWindow;


LTexture gFinalScore;
LTexture gAngleLine;
LTexture gHighScore;

//the function to initialize SDL create the renderer and make the window
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
			gWindow = SDL_CreateWindow("Brick Breaker 2.0 IN SPACE\n",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

//function to load all the images
bool loadMedia(){
    bool success = true;

	if(!gStartWindow.loadFromFile("Start.png",gRenderer)){
		printf("Failed to load start screen\n");
		success = false;
	}
    if(!gPaddle.loadFromFile("Paddle.png", gRenderer)){
        printf("Failed ot load Me pic\n");
        success = false;
    }
     if(!gLongPaddle.loadFromFile("PaddleLong.png", gRenderer)){
     printf("Failed ot load Me pic\n");
     success = false;
     }
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
	if(!gLifeBrick.loadFromFile("LifeBrick.png", gRenderer)){
		printf("failed to load life brick\n");
		success = false;
	}
	if(!gStaticBrick.loadFromFile("StaticBrick.png",gRenderer)){
		printf("failed to load static\n");
		success = false;
	}
	if(!gLives.loadFromFile("Lives.png", gRenderer)){
		printf("failed to load hearts\n");
		success = false;
	}
	if(!gAngleLine.loadFromFile("Line.png", gRenderer)){
		printf("failed to load line\n");
		success = false;
	}
    if(!gLongBrick.loadFromFile("greenBrick.png", gRenderer)){
        printf("failed to load long\n");
        success = false;
    }
	if(!gFastBrick.loadFromFile("fastBrick.png", gRenderer)){
		printf("failed to load fast brick\n");
		success = false;
	}
/*
 if(!gStartWindow.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Start.png",gRenderer)){
 printf("Failed to load start screen\n");
 success = false;
 }
 if(!gPaddle.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Paddle.png", gRenderer)){
 printf("Failed ot load Me pic\n");
 success = false;
 }
if(!gLongPaddle.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/PaddleLong.png", gRenderer)){
    printf("Failed ot load Me pic\n");
    success = false;
}
 if(!gBackGround.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/BackGround.png", gRenderer)){
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
 if(!gLifeBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/LifeBrick.png", gRenderer)){
 printf("failed to load life brick\n");
 success = false;
 }
 if(!gStaticBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/StaticBrick.png",gRenderer)){
 printf("failed to load static\n");
 success = false;
 }
 if(!gLives.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Lives.png", gRenderer)){
 printf("failed to load hearts\n");
 success = false;
 }
 if(!gAngleLine.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Line.png", gRenderer)){
 printf("failed to load line\n");
 success = false;
 }
 if(!gLongBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/greenBrick.png", gRenderer)){
    printf("failed to load long\n");
    success = false;
 }
 if(!gFastBrick.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/fastBrick.png",gRenderer)){
	printf("failed to load fast brick\n");
	success = false;
 }
*/
    return success;	
}
//frees all the memory used when the program closes
void close(){
	
	gBackGround.free();
	gPaddle.free();
    gLongPaddle.free();
	gBall.free();
	gBlueBrick.free();
	gPurpleBrick.free();
	gOrangeBrick.free();
	gStaticBrick.free();
	gLifeBrick.free();
    gLongBrick.free();
	gFastBrick.free();
	gTextTexture.free();
	gLives.free();
	gScoreNum.free();
	gLost.free();
	gFinalScore.free();
	gAngleLine.free();
	gHighScore.free();
	gStartWindow.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

//the main game loop
int main(int argc, char* argv[]){
    bool paused = false;
    bool spacePressed = false;
	
	if(!init()){
		printf("failed to initialize\n");
	}else{
		if(!loadMedia()){
			printf("Failed to load media\n");
		}else{			

			SDL_Event e;

            bool StartWindow = true, quit = false, Lose_Life = false, begin = false, GameLost = false;
            int brickW = gBlueBrick.getWidth(), brickH = gBlueBrick.getHeight();
			std::string inputText = "Score: ", scoreNum, highScore;

			std::stringstream buffer;
	
            std::list<Brick* > bricks, staticBricks, powerUps;
			std::list<Brick* >::iterator lit;

			//window that pops up when the user loses
			LWindow gLostWindow;

			//for displaying score
			SDL_Color White = {255,255,255,255};
			TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf",24);
            //TTF_Font* font = TTF_OpenFont("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Roboto-Black.ttf",24);
			TTF_Font* finalFont = TTF_OpenFont("Roboto-Black.ttf", 30);
            //TTF_Font* finalFont = TTF_OpenFont("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Roboto-Black.ttf", 30);

			gTextTexture.loadText(gRenderer,inputText,font, White);
	

			Paddle Paddle(gPaddle.getHeight(),gPaddle.getWidth(),gLongPaddle.getHeight(),gLongPaddle.getWidth(),0,0);
			Ball Ball(gBall.getHeight(),gBall.getWidth(), 6, -6);
            
            //fill the bricks lists
			createBricks(bricks, staticBricks, powerUps, Ball, Ball.Level, brickW,brickH);
            //while the window is open
			while(!quit){
				
					buffer.clear();
					buffer << Ball.Score;
					buffer >> scoreNum;


				//load losing window
				if(Ball.Lives==0 && GameLost==false){
					gLostWindow.init();

					gLost.free();
					gFinalScore.free();

					gLost.loadFromFile("lost.png", gLostWindow.mRenderer);
                    //gLost.loadFromFile("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/lost.png", gLostWindow.mRenderer);
					gFinalScore.loadText(gLostWindow.mRenderer, scoreNum, finalFont, White);

					//set high score
					if(Ball.Score > Ball.HighScore){
						Ball.HighScore = Ball.Score;
					}

					buffer.clear();
					buffer << Ball.HighScore;
					buffer >> highScore;


					gHighScore.loadText(gLostWindow.mRenderer, highScore, finalFont, White);
		
					GameLost = true;
				}

				
				//poll events for correct window
				while(SDL_PollEvent(&e)!=0){
					if(GameLost==true){
						GameLost = gLostWindow.handleEvent(e);
						//reset game
						if(GameLost==false){
							Reset(bricks,staticBricks,powerUps,Ball,Paddle,brickW,brickH);
							gLost.free();
							gFinalScore.free();
							gHighScore.free();
						}
					}else{
						if(e.type==SDL_QUIT){
							quit = true;
						}
						
						//start window/tutorial
						if(StartWindow==true){
							StartWindow = start(e);	
						}else{
							Paddle.handleEvent(e);
                            
							if(begin==false){
								begin = Ball.begin(e);
							}else if(e.type == SDL_KEYDOWN && e.key.repeat==0){
                                if(e.key.keysym.sym == SDLK_SPACE && !spacePressed){
                                    paused = !paused;
                                    spacePressed = true;
                                }
                            }else if(e.type == SDL_KEYUP && e.key.repeat==0){
                                if(e.key.keysym.sym == SDLK_SPACE){
                                    spacePressed = false;
                                }
                            }
						}
					}
					
				}
				if(StartWindow==true){
					SDL_RenderClear(gRenderer);
					gStartWindow.render(gRenderer, 0,0);
					SDL_RenderPresent(gRenderer);
				}
				else{
					//if game is lost a window pops up
					if(GameLost==true){
                        Paddle.setLong(false);
                        Ball.longCount = 0;
                        Ball.longPaddle = false;
						SDL_SetRenderDrawColor(gLostWindow.mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
						SDL_RenderClear(gLostWindow.mRenderer);

						gLostWindow.renderImage(gLost,0,0);
		                gLostWindow.renderImage(gFinalScore,120,85);
						gLostWindow.renderImage(gHighScore,127,120);
						
						SDL_RenderPresent(gLostWindow.mRenderer);

					}else if(!paused){
						gScoreNum.free();
						gScoreNum.loadText(gRenderer, scoreNum, font, White);

						Paddle.move();
                        //runs when a life has been lost
						if(Lose_Life==true){
							Ball.setV(6, -6);
                            Paddle.setLong(false);
                            Ball.longCount = 0;
                            Ball.longPaddle = false;
							begin = false;
							Lose_Life = false;
						}
	
						//move ball when spacebar is pressed, otherwise follow paddle
						if(begin==true){
							Lose_Life = Ball.move(bricks, staticBricks, powerUps, Paddle);
						}else{
							Ball.setXY(Paddle.getX()+35, Paddle.getY()-30);
						}

						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);

						gBackGround.render(gRenderer,0,0);
                        //renders the correct paddle
                        if(Paddle.isLong){
                            Paddle.render(gLongPaddle,gRenderer);
                        }else{
                            Paddle.render(gPaddle,gRenderer);
                        }
                        
						Ball.render(gBall, gRenderer);
                        //if all the bricks have been destroyed it moves to the next level
                        if(bricks.empty()){
                            deleteBricks(staticBricks);
                            deleteBricks(powerUps);
                            Ball.Level++;
                            //starts over if all levels have been beaten
                            if(Ball.Level>5){
                                Ball.Level = 1;
                            }
                            begin = false;
                            //fills the lists with new bricks
                            createBricks(bricks, staticBricks, powerUps, Ball, Ball.Level, brickW, brickH);
                        }
                        
						//render bricks
						for(lit = bricks.begin();lit!=bricks.end();lit++){
                            (*lit)->render(gRenderer,gBlueBrick, gPurpleBrick, gOrangeBrick);
						}
                        //render powerups
                        for(lit = powerUps.begin(); lit != powerUps.end(); lit++){
                            if((*lit)->PWRLife){
                                gLifeBrick.render(gRenderer,(*lit)->x,(*lit)->y);
                            }else if((*lit)->PWRLong){
                                gLongBrick.render(gRenderer,(*lit)->x,(*lit)->y);
                            }else if((*lit)->PWRFast){
                                gFastBrick.render(gRenderer,(*lit)->x,(*lit)->y);
                            }
                        }
                        //render static bricks
						for(lit = staticBricks.begin();lit!=staticBricks.end();lit++){
							gStaticBrick.render(gRenderer,(*lit)->x, (*lit)->y);
						}
                        //render the hearts
						for(int i=0; i<Ball.Lives;i++){
							gLives.render(gRenderer, 10 + gLives.getWidth()*i, 10);
						}
	
						gTextTexture.render(gRenderer, 500, 20);
						gScoreNum.render(gRenderer, 600, 20);

					
					

						SDL_RenderPresent(gRenderer);
					}//game over 
				}
			}//while

			font = NULL;
			finalFont = NULL;
            //clear all the bricks
			deleteBricks(bricks);
			deleteBricks(staticBricks);
            deleteBricks(powerUps);
		}
	}

	close();
	return 0;

}
