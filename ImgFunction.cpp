#include "ImgFunction.h"
#include <iostream>

ImgFunction::ImgFunction()
{
    picture_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
ImgFunction::~ImgFunction()
{
    Free();
}

bool ImgFunction::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface != NULL)
    {
        
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture != NULL)
        {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    picture_ = newTexture;
    return picture_ != NULL;
}

void ImgFunction::Free()
{
    if (picture_ != NULL)
    {
        SDL_DestroyTexture(picture_);
        picture_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void ImgFunction::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(des, picture_, clip, &renderQuad);
}
