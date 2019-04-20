#include"head.h"
#include<fstream>


bool checkCollision( SDL_Rect a, Brick b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
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

    //If none of the sides from A are outside B
    return true;
}
//function to turn object into sdl_rect and add to object vector
void addObject(std::list<Brick* >& objects, int x, int y, int w, int h, int hits){
	Brick *r = new Brick(x,y,w,h,hits);
	objects.push_back(r);
}
//creating files 1-5, will follow this format:
//MAX_VEL (of ball)
//x y hits (for all bricks in level)
//might update it so that if hits=-1 its an unbreakble one
void createBricks(std::list<Brick* >& objects, std::list<Brick* >& staticBricks, Ball& Ball, int Level, int w, int h){
    w += 3;
    h += 3;
	int x, y, hits;

	std::ifstream fin;
	std::string line;
	std::istringstream buffer;

	switch(Ball.Level){
		case 1:
			fin.open("Level1.txt");
			break;
		case 2:
			fin.open("Level2.txt");
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
			addObject(staticBricks,x,y,w,h,hits);
		}else{
			addObject(objects,x,y,w,h,hits);
		}
	}
/*
	addObject(objects, 2*w,4*h,w,h,3);
    addObject(objects, 3*w,4*h,w,h,3);
    addObject(objects, 4*w,4*h,w,h,3);
    addObject(objects, 5*w,4*h,w,h,3);
    addObject(objects, 6*w,4*h,w,h,3);
    addObject(objects, 1.5*w,5*h,w,h,3);
    addObject(objects, 2.5*w,5*h,w,h,3);
    addObject(objects, 3.5*w,5*h,w,h,3);
    addObject(objects, 4.5*w,5*h,w,h,3);
    addObject(objects, 5.5*w,5*h,w,h,3);
    addObject(objects, 6.5*w,5*h,w,h,3);
    addObject(objects, 2*w,6*h,w,h,3);
    addObject(objects, 3*w,6*h,w,h,3);
    addObject(objects, 4*w,6*h,w,h,3);
    addObject(objects, 5*w,6*h,w,h,3);
    addObject(objects, 6*w,6*h,w,h,3);
*/    


    
}

void deleteBricks(std::list<Brick* >&objects){
	std::list<Brick* >::iterator lit;
	for(lit=objects.begin();lit!=objects.end();lit++){
		lit = objects.erase(lit);
	}
	
}

void Reset(std::list<Brick* >& objects, std::list<Brick* >& statics, Ball& ball,Paddle& paddle, int w, int h){
	deleteBricks(objects);
	deleteBricks(statics);

	ball.Lives = 3;
	ball.Score = 0;
	ball.Angle = 45;
	ball.Level = 1;

	//ball.setXY(SCREEN_WIDTH/2-ball.OB_WIDTH/2, SCREEN_HEIGHT - ball.OB_HEIGHT);
	paddle.setXY(SCREEN_WIDTH/2-paddle.OB_WIDTH/2, SCREEN_HEIGHT - paddle.OB_HEIGHT);
	
	createBricks(objects, statics, ball, ball.Level,w,h);
}
