//Ball class
#include"head.h"
#include<cmath>

Ball::Ball(double h, double w, double vel_x, double vel_y){
	OB_HEIGHT = h;
	OB_WIDTH = w;
    //the initial position of the ball
	mPosX = SCREEN_WIDTH/2 - w/2;
	mPosY = SCREEN_HEIGHT - h;

    //Initialize the velocity
    mVelX = vel_x;
    mVelY = vel_y;
    vel = sqrt(vel_x * vel_x + vel_y * vel_y);
	Lives = 3;
	Score = 0;
	HighScore = 0;
	Level = 1;
	MAX_VEL = 6;

    longPaddle = false;
	faster = false;

}

double Ball::getX(){
	return mPosX;
}

double Ball::getY(){
	return mPosY;
}

void Ball::setV(double x,double y){
	mVelX = x;
	mVelY = y;
    vel = sqrt(x * x + y * y);
}

void Ball::setXY(double x, double y){
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

//moves ball and checks for collision. sign changes account for hitting wall or brick, and kept track of in program.
//handles bouncing off of the paddle with velocity split into x and y components based on angle
bool Ball::move(std::list<Brick* >& bricks, std::list<Brick* >& staticBricks, std::list<Brick* >& powerUps, Paddle& paddle){
	std::list<Brick* >::iterator lit;
    bool top = false, lside = false, bottom = false, rside = false;

	//Move ball left or right
    mPosX += mVelX;

    //move ball up or down
    mPosY += mVelY;
	
	//hits wall horizontalaly
	if((mPosX < 0) || (mPosX + OB_WIDTH > SCREEN_WIDTH)){
		
		mPosX -= mVelX;
		mVelX = -mVelX;

	}else if((mPosY < 70)){   //hits top wall below score and lives

		mPosY -= mVelY;
		mVelY = -mVelY;

	}else if(checkPaddleHit(paddle,top)){ //if it hits the paddle run the adjust angle function
        if(top){
            adjustAngle(paddle);
        }
	}else if(mPosY + OB_HEIGHT > SCREEN_HEIGHT){  //if it hits the bottom wall
		Lives--;
		return true;

    }else{
		//checks if it hits a power up
        for(lit = powerUps.begin(); lit != powerUps.end(); lit++){
            if(checkCollide(*(*lit),top,rside,lside,bottom)){
                if((*lit)->hit==false){
                    mPosX -=mVelX;
                    mPosY -= mVelY;
                    
                    if(top==true || bottom == true){    //if it hits top or bottom wall flip y velocity
                        mVelY = -(mVelY);
                    }else if(lside == true || rside == true){ //if hits right or left flip x velocity
                        mVelX = -(mVelX);
                    }
                    if((*lit)->PWRLife==true){ //if powerup was life increase lives
                        Lives++;
                    }
                    //if powerup was fast increase the max velocity and set faster flag to true
                    if((*lit)->PWRFast==true){
                        if(mVelX < 0){
                            mVelX -= 1.3;
                        }else if(mVelX > 0){
                            mVelX += 1.3;
                        }
                        if(mVelY < 0){
                            mVelY -= 1.3;
                        }else if(mVelY > 0){
                            mVelY += 1.3;
                        }
                        vel += 2;
                        fastCount = 0;
                        
                        faster = true;
                    //slows back down after it hits 6 bricks resets velocity after next paddle hit
                    }else if(faster){
                        fastCount++;
                        if(fastCount > 6){
                            vel -= 2;
                            faster = false;
                            fastCount = 0;
                        }
                    }
                    //if power up is long change the paddle to long
                    if((*lit)->PWRLong){
                        paddle.setLong(true);
                        longCount = 0;
                        longPaddle = true;
                    //after 10 brick hits the paddle goes back to normal
                    }else if(longPaddle){
                        longCount++;
                        if(longCount >= 10){
                            paddle.setLong(false);
                            longPaddle = false;
                            longCount = 0;
                        }
                    }
                    //remove a life of the brick
                    (*lit)->takeHealth();
                    
                    //give extra points for breaking a brick
                    if((*lit)->hit==true){
                        Score += 20;
                        delete (*lit);
                        lit = powerUps.erase(lit);
                    }else{
                        Score += 5;
                    }
                    break; //break out of the loop so it only checks collision once in case of two bricks both being hit
                }
            }
        }
        //loops through normal bricks and checks collisions
        for(lit = bricks.begin();lit != bricks.end(); lit++){
            if(checkCollide(*(*lit),top,rside,lside,bottom)){
                if((*lit)->hit==false){
                    mPosX -=mVelX;
                    mPosY -= mVelY;
                    
                    if(top==true || bottom == true){  //flip y velocity
                        mVelY = -(mVelY);
                    }else if(lside == true || rside == true){ //flip x velocity
                        mVelX = -(mVelX);
                    }
                    //decrease the health of the brick
                    (*lit)->takeHealth();
                    //if the paddle is long increase the count of hits taken
                    if(longPaddle){
                        longCount++;
                        if(longCount >= 10){
                            paddle.setLong(false);
                            longPaddle = false;
                            longCount = 0;
                        }
                    }
                    //if it is moving faster increase the counter
                    if(faster){
                        fastCount++;
                        if(fastCount > 6){
                            vel -= 2;
                            faster = false;
                            fastCount = 0;
                        }
                    }
                    
                    //extra points if broken
                    if((*lit)->hit==true){
                        Score += 10;
                        delete (*lit);
                        lit = bricks.erase(lit);
                    }else{
                        Score += 5;
                    }
                    break;
                }
            }
        }
        //check collision with the unbreakable bricks
        for(lit = staticBricks.begin();lit != staticBricks.end(); lit++){
			if(checkCollide(*(*lit),top,rside,lside,bottom)){
				mPosX -= mVelX;
				mPosY -= mVelY;
				if(top==true || bottom == true){ //flip y velocity
					mVelY = -(mVelY);
                }else if(lside == true || rside == true){ //flip xvelocity
					mVelX = -(mVelX);
				}
                //if paddle is long increase the number of hits taken
                if(longPaddle){
                    longCount++;
                    if(longCount >= 10){
                        paddle.setLong(false);
                        longPaddle = false;
                        longCount = 0;
                    }
                }
				return false;
			}
        }
		 
	}		

    
	
	return false;

}
//this function checks collision with a brick returns true if collided
//Changes the four booleans to represent which side was hit
bool Ball::checkCollide(Brick brick, bool &top, bool &rside, bool &lside, bool &bottom){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = brick.x;
    rightA = brick.x + brick.w;
    topA = brick.y;
    bottomA = brick.y + brick.h;

    //Calculate the sides of rect B
    leftB = getX();
    rightB = getX() + OB_WIDTH;
    topB = getY();
    bottomB = getY() + OB_HEIGHT;
    //If any of the sides from A are outside of B
    if( bottomA <= topB ){
        return false;
    }
    if( topA >= bottomB ){
		return false;
    }
    if( rightA <= leftB ){
		return false;
    }
    if( leftA >= rightB ){
		return false;
    }
    //if it hit the right side
    if(mPosX >= brick.x + brick.w -10 && mPosX <= brick.x + brick.w + 10 && mVelX < 0){
        rside = true;
    }
    //if it hit the left side
    if(mPosX + OB_WIDTH <= brick.x + 10 && mPosX + OB_WIDTH >= brick.x - 10 && mVelX > 0){
		lside = true;
    }
    //if it hit the bottom
    if(mPosY >= brick.y + brick.h -10 && mPosY <= brick.y + brick.h + 10 && mVelY < 0){
        bottom = true;
    }
    //if it hit the top
    if(mPosY + OB_HEIGHT <= brick.y + 10 && mPosY + OB_HEIGHT >= brick.y - 10 && mVelY > 0){
		top = true;
	}
    //If it collided with the brick
    return true;

}
//this function checks for collision with the paddle
bool Ball::checkPaddleHit(Paddle pad, bool& top){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = pad.getX();
    rightA = pad.getX() + pad.OB_WIDTH;
    topA = pad.getY();
    bottomA = pad.getY() + pad.OB_HEIGHT;

    //Calculate the sides of rect B
    leftB = getX();
    rightB = getX() + OB_WIDTH;
    topB = getY();
    bottomB = getY() + OB_HEIGHT;
    //If any of the sides from A are outside of B
    if( bottomA <= topB ){
        return false;
    }
    if( topA >= bottomB ){
        return false;
    }
    if( rightA <= leftB ){
        return false;
    }
    if( leftA >= rightB ){
        return false;
    }
    //if the top of the paddle was hit (sides don't matter)
    if(((mPosY + OB_HEIGHT <= pad.getY() + 15 && mPosY + OB_HEIGHT >= pad.getY() - 15))){
        top = true;
    }
    //If none of the sides from A are outside B
    return true;	
}
//this function causes the ball to bounce at a non 90 degree angle off of the paddle
//if the ball hits closer to the edges the angle will be shallower
//if ball and paddle go same direction shallower angle else steeper angle
void Ball::adjustAngle(Paddle pad){
    mPosY -= mVelY;
    double ballMid = mPosX + (OB_WIDTH / 2);
    double paddleMid = pad.getX() + (pad.OB_WIDTH / 2);
    double angle = 55 - (40 * (fabs(paddleMid - ballMid)/pad.OB_WIDTH)); //max 55 min 35
    int xDir = mVelX / fabs(mVelX);
    if(pad.getXVel() / mVelX > 0){
        angle -= 10;
    }else{
        angle += 10;
    }
    angle = angle * M_PI / 180;
    mVelX = xDir * cos(angle) * vel;
    mVelY = -1 * sin(angle) * vel;
}
//renders the ball
void Ball::render(LTexture& gBall, SDL_Renderer* gRenderer){
	gBall.render(gRenderer,mPosX,mPosY);
}





