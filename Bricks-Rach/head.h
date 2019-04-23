#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
//#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_ttf.h>
//#include<SDL2_ttf/SDL_ttf.h>
#include<cstdio>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 600;

//this is so multiple windows can pop up
//i.e tutorial window, end game window
//idk looks cool lost.png
class LWindow
{
    public:
        //Intializes internals
        LWindow();

        //Creates window
        bool init();

        //Handles window events
        bool handleEvent( SDL_Event& e );

		void renderImage(class LTexture&, int x, int y);

        //Deallocates internals
        void free();

        //Window dimensions
        int getWidth();
        int getHeight();


        //Window focii
		SDL_Renderer* mRenderer;

    private:
        //Window data
        SDL_Window* mWindow;
       // SDL_Renderer* mRenderer;
        int mWindowID;

        //Window dimensions
        int mWidth;
        int mHeight;

};

class LTexture{
 public:
	 LTexture();
	 ~LTexture();
	 bool loadFromFile(std::string path, SDL_Renderer*);
	 bool loadText(SDL_Renderer* gRenderer, std::string,TTF_Font* font, SDL_Color color);
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
	Brick(int,int,int,int,int); //initializes x, y, width, height

	void takeHealth(); //takes health/changes color
	void render(SDL_Renderer*, LTexture& Blue, LTexture& Purple, LTexture& Orange);
	int x,y,w,h;
	int Life;
	bool hit;
	
	//power ups
	bool PWRLife; //extra life
	bool PWRExp; //exploading
    bool PWRLong; //long paddle
	bool PWRFast;
};

class Paddle{
 public:
	 static const int OB_VEL = 12;
	 Paddle(int, int, int, int, int, int);
	 int getX();
	 int getY();
    int getXVel();
	 //resets coordinates
	 void setXY(int x, int y);
    void setVel(int x, int y);

	 void handleEvent(SDL_Event& e);
	 void move(); //makes sure it only moves it left or right
	 void render(LTexture&, SDL_Renderer*);
     void setLong(bool);

	 int OB_HEIGHT;
	 int OB_WIDTH;
    bool isLong;

 private:
	 int mPosX, mPosY;
	 int mVelX, mVelY;
    int nHeight, nWidth;
    int lHeight, lWidth;

};

class Ball{
 public:
	//arbitary num I just set; same for Paddle
	static const int OB_VEL = 12;
	Ball(double, double, double, double);

	//get x and y positions
	double getX();
	double getY();
	void setV(double, double); //set velocity
	//resets X and Y position 
	void setXY(double x, double y);
	
//	void SetAngle();  //actively changes the velocity based on angle
//	void ChangeAngle(SDL_Event& e); //handles event to change control with Q and W

	bool begin(SDL_Event &e); //controlls spacebar press that makes ball move
	bool move(std::list<Brick* >& wall, std::list<Brick* >& statics, Paddle& paddle);
	void render(LTexture& obj, SDL_Renderer*);

	bool checkPaddleHit(Paddle, bool&, bool&);
	bool checkCollide(Brick brick, bool&, bool&, bool&, bool&);
    void adjustAngle(Paddle pad);

	int Angle; 
	int OB_HEIGHT;
	int OB_WIDTH;
	int Score;
	int Lives;
	int HighScore;
	int Level;
	int MAX_VEL;
    int longCount;
    bool longPaddle;
	bool faster;
	bool fastCount;


 private:
	double mPosX, mPosY;
	double mVelX, mVelY;
    double vel;

//	bool Bounce;
//	int Combo;

};


void addObject(std::list<Brick* >&, int, int, int, int, std::string);
void createBricks(std::list<Brick* >&, std::list<Brick* >&, Ball&, int, int, int);
void deleteBricks(std::list<Brick* >&);
bool init();
bool loadMedia();
void close();
bool start(SDL_Event &e);

void Reset(std::list<Brick* >& bricks, std::list<Brick* >& statics, Ball& ball,Paddle& paddle, int w, int h);
