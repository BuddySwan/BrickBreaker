#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<cstdio>
#include<string>
#include<vector>
#include<list>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture{
 public:
	 LTexture();
	 ~LTexture();
	 bool loadFromFile(std::string path, SDL_Renderer*);
#ifdef _SDL_TTF_H
	 //creates image from font string
	 bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif
	 void free();
	 void setColor(Uint8 red, Uint8 gree, Uint8 blue);
	 void setBlendMode(SDL_BlendMode blending);
	 void setAlpha(Uint8 alpha);
	 void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	 int getWidth();
	 int getHeight();

 private:
	 SDL_Texture* mTexture;
	 int mWidth;
	 int mHeight;

};

class Brick{
 public:
	Brick(int,int,int,int); //initializes x, y, width, height

	void takeHealth(); //takes health/changes color
	void render(SDL_Renderer*, LTexture& Blue, LTexture& Purple, LTexture& Orange);
	int x,y,w,h;
	bool hit; //keeps track if hit
	char color;
};

class Paddle{
 public:
	 static const int OB_VEL = 12;
	 Paddle(int, int, int, int);
	 int getX();
	 int getY();

	 //resets coordinates
	 void setXY(int x, int y);

	 void handleEvent(SDL_Event& e);
	 void move(); //makes sure it only moves it left or right
	 void render(LTexture& obj, SDL_Renderer*);
	 void Set_Dimensions(int h, int w);
	
	 int Angle;
	 int OB_HEIGHT;
	 int OB_WIDTH;

 private:
	 int mPosX, mPosY;
	 int mVelX, mVelY;

	 SDL_Rect mCollider;
};

class Ball{
 public:
	//arbitary num I just set; same for Paddle
	static const int OB_VEL = 12;
	Ball(int, int, int, int);

	//get x and y positions
	int getX();
	int getY();

	//resets X and Y position 
	void setXY(int x, int y);

	bool begin(SDL_Event &e); //controlls spacebar press that makes ball move
	bool move(std::list<Brick>& wall, int& x, int& y);
	void render(LTexture& obj, SDL_Renderer*);
	void Set_Dimensions(int h, int w);

	int Angle; //I havent done anything with this yet but if we wanted to calc real angle
	int OB_HEIGHT;
	int OB_WIDTH;

 private:
	int mPosX, mPosY;
	int mVelX, mVelY;

	SDL_Rect mCollider;
};


void addObject(std::list<Brick>&, int, int, int, int);
void createBricks(std::list<Brick>&, int, int);
//void deleteBricks(std::list<Brick >&);
bool init();
bool loadMedia();
void close();
bool checkCollision(SDL_Rect a, Brick b);


