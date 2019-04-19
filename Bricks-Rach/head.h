#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<cstdio>
#include<string>
#include<vector>
#include<list>
#include<sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//this is so multiple windows can pop up
//i.e tutorial window, end game window
//idk looks cool
class LWindow
{
    public:
        //Intializes internals
        LWindow();

        //Creates window
        bool init();

        //Handles window events
        bool handleEvent( SDL_Event& e );

        //Focuses on window
        void focus();

        //Shows windows contents
        void render();
		void renderImage(class LTexture&, int x, int y);

        //Deallocates internals
        void free();

        //Window dimensions
        int getWidth();
        int getHeight();


        //Window focii
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
        bool isShown();

		SDL_Renderer* mRenderer;

    private:
        //Window data
        SDL_Window* mWindow;
       // SDL_Renderer* mRenderer;
        int mWindowID;

        //Window dimensions
        int mWidth;
        int mHeight;

        //Window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;
        bool mShown;
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
	void setV(int, int);

	//resets X and Y position 
	void setXY(int x, int y);

	bool begin(SDL_Event &e); //controlls spacebar press that makes ball move
	bool move(std::list<Brick* >& wall, Paddle paddle);
	void render(LTexture& obj, SDL_Renderer*);
	void Set_Dimensions(int h, int w);

	bool checkPaddleHit(Paddle);
	bool checkCollide(Brick brick);

	int Angle; 
	int OB_HEIGHT;
	int OB_WIDTH;
	int Score;
	int Lives;

 private:
	int mPosX, mPosY;
	int mVelX, mVelY;

	SDL_Rect mCollider;
};


void addObject(std::list<Brick* >&, int, int, int, int);
void createBricks(std::list<Brick* >&, int, int);
void deleteBricks(std::list<Brick* >&);
bool init();
bool loadMedia();
void close();
bool checkCollision(SDL_Rect a, Brick b);
void Reset(std::list<Brick* >& bricks, Ball& ball, int w, int h);
