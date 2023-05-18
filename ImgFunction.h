#pragma once
#include "CommonFunction.h"

class ImgFunction
{
public:

	ImgFunction();
	~ImgFunction();
	
	void Free();

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }

	virtual bool LoadImg(std::string path, SDL_Renderer* screen); 
	
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

protected:

	SDL_Texture* picture_;

	SDL_Rect rect_; 
};
