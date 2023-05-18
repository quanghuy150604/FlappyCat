#pragma once
#include "CommonFunction.h"
#include "ImgFunction.h"

class Menu : public ImgFunction
{
	
public:
	Menu() { };
	~Menu() { };

	int ShowMenu(SDL_Renderer* screen, TTF_Font* font, std::string path,
				int xt, int yt, std::string path1, std::string path2, 
				int result, int high_score);
	
private:
};