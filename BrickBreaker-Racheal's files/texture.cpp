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

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText,SDL_Color textCOlor){
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str();textColor);
	if(textSurface!=NULL){
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if(mTexture==NULL){
			printf("Unable to create texture from rendered text\n");
		}else{
			mWidth = textSurface->w;
			mHeight = text->Surface->h;
		}
		SDL_FreeSurface(textSurface);
	}else{
		printf("Unable to render text surface\n");
	}
	return mTexture != NULL;
}
#endif

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
