//Paddle class
#include"head.h"

Paddle::Paddle(int h, int w, int lh, int lw, int vel_x, int vel_y){
	OB_HEIGHT = h;
	OB_WIDTH = w;
    nHeight = h;
    nWidth = w;
    lHeight = lh;
    lWidth = lw;
    //Initialize the offsets
	mPosX = SCREEN_WIDTH/2 - w/2;
	mPosY = SCREEN_HEIGHT-h;

    //Initialize the velocity
    mVelX = vel_x;
    mVelY = vel_y;
    
    isLong = false;
}

int Paddle::getX(){
	return mPosX;
}

int Paddle::getY(){
	return mPosY;
}

void Paddle::setXY(int x, int y){
	mPosX = x;
	mPosY = y;
}
void Paddle::setVel(int x, int y){
    mVelX = x;
    mVelY = y;
}
int Paddle::getXVel(){
    return mVelX;
}


//controlls paddle with arrow keys
void Paddle::handleEvent(SDL_Event& e){
	//if a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat==0){
		//adjust velocity
		switch(e.key.keysym.sym){
			case SDLK_UP:
				mVelY -= OB_VEL;
				break;
			case SDLK_DOWN:
				mVelY += OB_VEL;
				break;
			case SDLK_LEFT:
				mVelX -= OB_VEL;
				break;
			case SDLK_RIGHT:
				mVelX += OB_VEL;
				break;
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat==0){
		switch(e.key.keysym.sym){
			case SDLK_UP:
				mVelY += OB_VEL;
				break;
			case SDLK_DOWN:
				mVelY -= OB_VEL;
				break;
			case SDLK_LEFT:
				mVelX += OB_VEL;
				break;
			case SDLK_RIGHT:
				mVelX -= OB_VEL;
				break;
		}
	}
}

void Paddle::move(){
    //Move the dot left or right
    mPosX += mVelX;
    
	//for(int i=0;i<wall.size();i++){
	    //If the dot collided or went too far to the left or right
	    if( ( mPosX < 0 ) || ( mPosX + OB_WIDTH > SCREEN_WIDTH ))
	    {
			//Move back
		    mPosX -= mVelX;
		}
	
}
void Paddle::setLong(bool makeLong){
    if(makeLong){
        OB_WIDTH = lWidth;
        OB_HEIGHT = lHeight;
        isLong = makeLong;
        if(mPosX > .5 * (lWidth - nWidth) && mPosX + lWidth < SCREEN_WIDTH - .5 * (lWidth - nWidth)){
            mPosX -= .5 * (lWidth - nWidth);
        }else if(mPosX <= .5 * (lWidth - nWidth)){
            mPosX = 5;
        }else{
            mPosX = SCREEN_WIDTH - lWidth;
        }
    }else{
        OB_WIDTH = nWidth;
        OB_HEIGHT = nHeight;
        isLong = makeLong;
        
    }
}

//I put the renderer in manually in case we want to do multiple windows for some reason 
void Paddle::render(LTexture& gPaddle, SDL_Renderer* gRenderer){
	gPaddle.render(gRenderer,mPosX,mPosY);
}



