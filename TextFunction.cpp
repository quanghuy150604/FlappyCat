#include "TextFunction.h"

Text::Text()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
}
Text::~Text()
{
  
}

bool Text::LoadFromRenderedText(TTF_Font* font, SDL_Renderer* screen)
{
    FreeText();
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    if (textSurface != NULL)
    {
        texture = SDL_CreateTextureFromSurface(screen, textSurface);
        if (texture != NULL)
        {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return texture != NULL;
}

void Text::FreeText()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Text::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Text::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        text_color = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        text_color = color;
    }
    else
    {
        SDL_Color color = { 0, 0, 0 };
        text_color = color;
    }
}
void Text::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x, y, width, height };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);

}