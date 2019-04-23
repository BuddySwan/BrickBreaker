#include"head.h"
#include<fstream>


//function to turn object into sdl_rect and add to object vector
void addObject(std::list<Brick* >& objects, int x, int y, int w, int h, int hits, std::string PowerUp){
	Brick *r = new Brick(x,y,w,h,hits);

	if(PowerUp=="PWRLife"){
		r->PWRLife = true;
	}else if(PowerUp=="PWRExp"){
		r->PWRExp = true;
    }else if(PowerUp == "PWRLong"){
        r->PWRLong = true;
    }else if(PowerUp == "PWRFast"){
		r->PWRFast = true;
	}
	objects.push_back(r);
}


//creating files 1-5, will follow this format:
//MAX_VEL (of ball)
//x y hits (for all bricks in level)
//might update it so that if hits=-1 its an unbreakble one
void createBricks(std::list<Brick* >& objects, std::list<Brick* >& staticBricks, std::list<Brick* >& powerUps, Ball& Ball, int Level, int w, int h){
    w += 3;
    h += 3;
	int x, y, hits;

	std::ifstream fin;
	std::string line;
	std::istringstream buffer;

	switch(Level){
		case 1:
			fin.open("Level1.txt");
            //fin.open("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Level1.txt");
			break;
		case 2:
			fin.open("Level2.txt");
            //fin.open("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Level2.txt");
			break;
		case 3:
			fin.open("Level3.txt");
            //fin.open("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Level3.txt");
			break;
        case 4:
            fin.open("Level4.txt");
            //fin.open("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Level4.txt");
            break;
        case 5:
            fin.open("Level5.txt");
            //fin.open("/Users/buddy/Desktop/BrickBreakerProject/BrickBreakerGame/Bricks-Rach/Level5.txt");
            break;
	}
	getline(fin,line);
	buffer.clear();
	buffer.str(line);
	buffer >> Ball.MAX_VEL;

	while(getline(fin,line)){
		buffer.clear();
		buffer.str(line);
		buffer >> x >> y >> hits;
		if(hits==-1){
			addObject(staticBricks,x,y,w,h,hits,"");
		}else if(hits==-2){
			addObject(powerUps,x,y,w,h,1,"PWRLife");
		}else if(hits==-3){
			addObject(powerUps,x,y,w,h,1,"PWRExp");
        }else if(hits == -4){
            addObject(powerUps,x,y,w,h,1,"PWRLong");
		}else if(hits==-5){
			addObject(powerUps,x,y,w,h,1,"PWRFast");
		}else{
			addObject(objects,x,y,w,h,hits,"");
		}
	}

	fin.close();
    
}

void deleteBricks(std::list<Brick* >&objects){
	std::list<Brick* >::iterator lit;
	for(lit=objects.begin();lit!=objects.end();lit++){
		delete (*lit);
		lit = objects.erase(lit);
	}
    objects.clear();
}

void Reset(std::list<Brick* >& objects, std::list<Brick* >& statics, std::list<Brick* >& powerUps, Ball& ball,Paddle& paddle, int w, int h){
	deleteBricks(objects);
	deleteBricks(statics);
    deleteBricks(powerUps);

	ball.Lives = 3;
	ball.Score = 0;
	ball.Angle = 45;
	ball.Level = 1;

	paddle.setXY(SCREEN_WIDTH/2-paddle.OB_WIDTH/2, SCREEN_HEIGHT - paddle.OB_HEIGHT);
    paddle.setVel(0,0);
	
	createBricks(objects, statics, powerUps, ball, ball.Level,w,h);
}

bool start(SDL_Event& e){
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
		if(e.key.keysym.sym == SDLK_RETURN){
			return false;
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat == 0){
		if(e.key.keysym.sym == SDLK_RETURN){
			return false;
		}
	}

	return true;
}
