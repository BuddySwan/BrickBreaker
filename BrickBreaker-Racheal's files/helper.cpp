#include"head.h"

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
void addObject(std::list<Brick>& objects, int x, int y, int w, int h){
	Brick r(x,y,w,h);
	objects.push_back(r);
}

void createBricks(std::list<Brick>& objects,int w, int h){
	addObject(objects, 0,0,w,h);
	addObject(objects,w+1,h+1,w,h);
	addObject(objects,2*w+1,2*h+1,w,h);
	addObject(objects, 400, 0, w, h);
	addObject(objects, 400, 100, w, h);
	addObject(objects, 0, 200, w, h);
	addObject(objects, 50, 200, w, h);
	addObject(objects, 50, 0, w, h);
	addObject(objects, 300, 300, w, h);
	addObject(objects, 150, 300, w, h);
}
