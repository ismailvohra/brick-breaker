#include"LTexture.h"

LTexture::LTexture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    Free();
}

bool LTexture::LoadFromFile( std::string path , SDL_Renderer* gRenderer)
{
    //Get rid of preexisting texture
    Free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    texture = newTexture;
    return texture != NULL;
}

void LTexture::Free()
{
    //Free texture if it exists
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void LTexture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( texture, red, green, blue );
}

void LTexture::SetBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( texture, blending );
}

void LTexture::SetAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( texture, alpha );
}

int LTexture::GetWidth()
{
    return width;
}

int LTexture::GetHeight()
{
    return height;
}

void LTexture::Render( int x, int y, SDL_Rect* clip , double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, texture, clip, &renderQuad, angle, center, flip );
}
