//Ball class
#include"head.h"
#include<cmath>

Ball::Ball(double h, double w, double vel_x, double vel_y){
	OB_HEIGHT = h;
	OB_WIDTH = w;
    //Initialize the offsets
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

	Angle = 45;
    longPaddle = false;
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

//maybe my EF days have finally left me bc its not working
/*void Ball::SetAngle(){
	int vY = mVelY, vX = mVelX;
	double tanA = tan((M_PI*Angle)/180);

	//for some reason the tan function is STRUGGLING to calculate tan(90) so I 
	//did it manually
	if(Angle==90){  
		mVelX = 0;
	}else if(Angle==0 || Angle==180){
		mVelY = 0;
	}else{
		mVelY = (vX * tanA);
		mVelX = (vY / tanA);
	}
}

void Ball::ChangeAngle(SDL_Event& e){
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
		if(e.key.keysym.sym == SDLK_q){
			if(Angle>0){
				Angle -= OB_VEL;
			}
		}else if(e.key.keysym.sym == SDLK_w){
			if(Angle<180){
				Angle += OB_VEL;
			}
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat == 0){
		if(e.key.keysym.sym == SDLK_q){
			if(Angle>0){
				Angle -= OB_VEL;
			}
		}else if(e.key.keysym.sym == SDLK_w){
			if(Angle<180){
				Angle += OB_VEL;
			}
		}
	}
//	SetAngle();

}
*/

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
//only handles a 90 degree turn at the moment, will make it better
bool Ball::move(std::list<Brick* >& bricks, std::list<Brick* >& staticBricks, Paddle& paddle){
	std::list<Brick* >::iterator lit;
    bool top = false, lside = false, bottom = false, rside = false;

	//Move the dot left or right
    mPosX += mVelX;

    //up or down
    mPosY += mVelY;
	
	//hits wall horizontalaly
	if((mPosX < 0) || (mPosX + OB_WIDTH > SCREEN_WIDTH)){
		
		mPosX -= mVelX;
		mVelX = -mVelX;

	}else if((mPosY < 70)){   //so it doesnt overlap the lives and score

		mPosY -= mVelY;
		mVelY = -mVelY;

	}else if(checkPaddleHit(paddle,top,lside)){
        if(top){
            adjustAngle(paddle);
        }
        if(lside){
            mPosX -= mVelX;
            mVelX = -mVelX;
        }
	}else if(mPosY + OB_HEIGHT > SCREEN_HEIGHT){
		Lives--;
		return true;

    }else{
		//check if hit with static brick
        for(lit = bricks.begin();lit != bricks.end(); lit++){
            
            if(checkCollide(*(*lit),top,rside,lside,bottom)){
                
                if((*lit)->hit==false){
                    mPosX -=mVelX;
                    mPosY -= mVelY;
                    
                    int m = 0;
                    
                    if(mVelY < 0 && mVelY > -(MAX_VEL)){
                        m = -1;
                    }else if(mVelY > 0 && mVelY < MAX_VEL){
                        m = 1;
                    }
                    
                    if(top==true || bottom == true){
                        mVelY = -(mVelY);
                    }else if(lside == true || rside == true){
                        mVelX = -(mVelX);
                    }
                    
                    //check if brick is a power up
                    if((*lit)->PWRLife==true){
                        Lives++;
                    }
                    if((*lit)->PWRLong){
                        paddle.setLong(true);
                        longCount = 0;
                        longPaddle = true;
                    }else if(longPaddle){
                        longCount++;
                        if(longCount >= 10){
                            paddle.setLong(false);
                            longPaddle = false;
                            longCount = 0;
                        }
                    }
                    
                    
                    
                    (*lit)->takeHealth();
                    
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
        for(lit = staticBricks.begin();lit != staticBricks.end(); lit++){
			if(checkCollide(*(*lit),top,rside,lside,bottom)){
				mPosX -= mVelX;
				mPosY -= mVelY;
				if(top==true || bottom == true){
					mVelY = -(mVelY);
                }else if(lside == true || rside == true){
					mVelX = -(mVelX);
				}
			
				return false;
			}
        }
		 
	}		

    
	
	return false;

}

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
    if(mPosX >= brick.x + brick.w -10 && mPosX <= brick.x + brick.w + 10 && mVelX < 0){
        rside = true;
    }
    if(mPosX + OB_WIDTH <= brick.x + 10 && mPosX + OB_WIDTH >= brick.x - 10 && mVelX > 0){
		lside = true;
    }
    if(mPosY >= brick.y + brick.h -10 && mPosY <= brick.y + brick.h + 10 && mVelY < 0){
        bottom = true;
    }
    if(mPosY + OB_HEIGHT <= brick.y + 10 && mPosY + OB_HEIGHT >= brick.y - 10 && mVelY > 0){
		top = true;
	}
    //If none of the sides from A are outside B
    return true;

}

bool Ball::checkPaddleHit(Paddle pad, bool& top, bool& side){
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
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

if(((mPosX >= pad.getX() + pad.OB_WIDTH -10 && mPosX <= pad.getX() + pad.OB_WIDTH + 10) || (mPosX + OB_WIDTH <= pad.getX() + 10 && mPosX + OB_WIDTH >= pad.getX() - 10))){
        side = true;
    }
else if(((mPosY >= pad.OB_HEIGHT + pad.OB_HEIGHT -10 && mPosY <= pad.getY() + pad.OB_HEIGHT + 10) || (mPosY + OB_HEIGHT <= pad.getY() + 10 && mPosY + OB_HEIGHT >= pad.getY() - 10))){
	top = true;
}
    //If none of the sides from A are outside B
    return true;	
}
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

void Ball::render(LTexture& gBall, SDL_Renderer* gRenderer){
	gBall.render(gRenderer,mPosX,mPosY);
}





