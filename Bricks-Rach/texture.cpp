//texture class
#include"head.h"

LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer){
	//get rid of preexisting texture
	free();
	//the final texture
	SDL_Texture* newTexture = NULL;
	//load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface==NULL){
		printf("Unable to load image!\n");
	}else{
		//color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF,0xFF));
				//create texture from surface pixels
				newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
				if(newTexture==NULL){
					printf("Unable to create texture\n");
				}else{
					mWidth = loadedSurface->w;
					mHeight = loadedSurface->h;
				}
				SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;

}

bool LTexture::loadText(SDL_Renderer* gRenderer, std::string text, TTF_Font* font){
	bool success = true;

	free();
	if(font==NULL){
		printf("couldn't open font");
		success = false;
	}else{
		SDL_Color Black = {0,0,0,0};
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), Black);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	
		if(Message==NULL){
			printf("Message is NUll\n");
			success = false;
		}else{

			mTexture = Message;
			mWidth = surfaceMessage->w;
			mHeight = surfaceMessage->h;

			SDL_FreeSurface(surfaceMessage);
		}
	}
	return success;
}


void LTexture::free(){
	if(mTexture!=NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}



void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}



void LTexture::setBlendMode( SDL_BlendMode blending ){
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );

}
		

void LTexture::setAlpha( Uint8 alpha ){
	//Modulate texture alpha	
	SDL_SetTextureAlphaMod( mTexture, alpha );
}



void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}



int LTexture::getWidth(){
	return mWidth;
}



int LTexture::getHeight(){
	return mHeight;
}
