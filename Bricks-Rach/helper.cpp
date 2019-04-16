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
void addObject(std::list<Brick* >& objects, int x, int y, int w, int h, int hits){
	Brick *r = new Brick(x,y,w,h,hits);
	objects.push_back(r);
}

void createBricks(std::list<Brick* >& objects,int w, int h){
	/*addObject(objects, 0,0,w,h,3);
	addObject(objects,w+1,h+1,w,h,3);
	addObject(objects,2*w+1,2*h+1,w,h,3);
	addObject(objects, 400, 0, w, h,3);
	addObject(objects, 400, 100, w, h,3);
	addObject(objects, 0, 200, w, h,3);
	addObject(objects, 50, 200, w, h,3);
	addObject(objects, w, 0, w, h,3);
	addObject(objects, 300, 300, w, h,3);
	addObject(objects, 150, 300, w, h,3);
     */
    w += 3;
    h += 3;
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
    


    
}

void deleteBricks(std::list<Brick* >&objects){
	std::list<Brick* >::iterator lit;
	for(lit=objects.begin();lit!=objects.end();lit++){
		delete (*lit);
	}
	
}

