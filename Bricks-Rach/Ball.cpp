//Ball class
#include"head.h"
#include <iostream>
int number = 0;

Ball::Ball(int x, int y, int vel_x, int vel_y){
	OB_HEIGHT = 0;
	OB_WIDTH = 0;
    //Initialize the offsets
	mPosX = x;
	mPosY = y;

    //Set collision box dimension
    mCollider.w = OB_WIDTH;
    mCollider.h = OB_HEIGHT;

    //Initialize the velocity
    mVelX = vel_x;
    mVelY = vel_y;

	Angle = 90;
}

int Ball::getX(){
	return mPosX;
}

int Ball::getY(){
	return mPosY;
}

void Ball::setXY(int x, int y){
	mPosX = x;
	mPosY = y;
}

//handles reset. ball only starts moving when spacebar is pressed
bool Ball::begin(SDL_Event& e){
	if(e.type == SDL_KEYDOWN && e.key.repeat==0){
		if(e.key.keysym.sym == SDLK_SPACE){
			return true;
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat==0){
		if(e.key.keysym.sym == SDLK_SPACE){
			return true;
		}
	}
	return false;
}

void Ball::Set_Dimensions(int h, int w){
	OB_HEIGHT = h;
	OB_WIDTH = w;

	mCollider.w = OB_WIDTH;
	mCollider.h = OB_HEIGHT;
}

//moves ball and checks for collision. sign changes account for hitting wall or brick, and kept track of in program.
//only handles a 90 degree turn at the moment, will make it better
bool Ball::move(std::list<Brick* >& bricks, Paddle paddle, int& sign_x, int& sign_y){
	std::list<Brick* >::iterator lit;

	//Move the dot left or right
    mPosX += (mVelX*sign_x);
    mCollider.x = mPosX;

    //up or down
    mPosY += (mVelY*sign_y);
    mCollider.y = mPosY;

	//hits wall horizontalaly
	if((mPosX < 0) || (mPosX + OB_WIDTH > SCREEN_WIDTH)){
		
		mPosX -= (mVelX*sign_x);
		mCollider.x = mPosX;
		sign_x = (sign_x*(-1));

	}else if((mPosY < 0)){

		mPosY -= (mVelY*sign_y);
		mCollider.y = mPosY;
		sign_y = (sign_y*(-1));

	}else if(checkPaddleHit(paddle)){ //was checkCollision
		//collides with paddle
		/*mPosY -= (mVelX*sign_y);
		mCollider.y = mPosY;
		sign_y = (sign_y*(-1));
         */

	}else if(mPosY + OB_HEIGHT > SCREEN_HEIGHT){
		return true;

    }else{
		 for(lit = bricks.begin();lit != bricks.end(); lit++){

			//If the dot collided or went too far to the left or right
		    /*if(checkCollision(mCollider,*(*lit))){
		
				if((*lit)->hit==false){ //|| lit==bricks.begin()){
			
					//change direction of x velocity
					mPosX -= (mVelX*sign_x);
					mCollider.x= mPosX;
					sign_x = (sign_x *(-1));
				
					(*lit)->takeHealth();
					if((*lit)->hit==true){
						bricks.erase(lit++);
						break;
					}
				}
			}*/
             
             //checks collision with the brick and adjusts ball velocity
             if(checkCollide(**lit)){
                 break;
             }
             //if the brick has zero lives left it deletes it from the list
             if((*lit)->hitsLeft == 0){
                 delete (*lit);
                 bricks.erase(lit);
             }
		}
	}		

    
	
	return false;

}

//this function checks collision of the ball with a brick
//if it hits a brick it decreases the hits of the brick by one and changes the balls velocity
bool Ball::checkCollide(Brick& brick){
    bool collided = false;
    if(mPosX <= brick.x + brick.w && mPosX + OB_WIDTH >= brick.x && mPosY <= brick.y + brick.h && mPosY + OB_HEIGHT >= brick.y){
        collided = true;
        //std::cout << "Hit " << number << std::endl;
        number++;
    }else{
        brick.hit = false;
        return false;
    }
    if(!brick.hit && brick.hitsLeft > 0 &&((mPosX >= brick.x + brick.w -10 && mPosX <= brick.x + brick.w + 10) || (mPosX + OB_WIDTH <= brick.x + 10 && mPosX + OB_WIDTH >= brick.x - 10))){
        mVelX = -mVelX;
        brick.hit = true;
        brick.hitsLeft--;
    }else if(!brick.hit && brick.hitsLeft > 0 &&((mPosY >= brick.y + brick.h -10 && mPosY <= brick.y + brick.h + 10) || (mPosY + OB_HEIGHT <= brick.y + 10 && mPosY + OB_HEIGHT >= brick.y - 10))){
        mVelY = -mVelY;
        brick.hit = true;
        brick.hitsLeft--;
    }
    return collided;
}

//this function checks if the paddle has been hit.
//if it has the ball inverts its velocity
bool Ball::checkPaddleHit(Paddle pad){
    if((mPosX + OB_WIDTH >= pad.getX() && mPosX <= pad.getX() + pad.OB_WIDTH && mPosY + OB_HEIGHT >= pad.getY() && mPosY + OB_HEIGHT <= pad.getY() + 10)){
        if(!hitPaddle){
            mVelY = -mVelY;
        }
        hitPaddle = true;
        return true;
    }else{
        hitPaddle = false;
        return false;
    }
}


void Ball::render(LTexture& gBall, SDL_Renderer* gRenderer){
	gBall.render(gRenderer,mPosX,mPosY);
}




