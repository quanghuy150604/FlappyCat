#pragma once
#include "CommonFunction.h"

class ImgFunction
{
public:

	ImgFunction();
	~ImgFunction();
	
	void Free();

	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }// set kich thuoc anh

	virtual bool LoadImg(std::string path, SDL_Renderer* screen); // load anh len p_object_ toi dua len man hinh 
	
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

protected:

	SDL_Texture* picture_;// luu tru anh

	SDL_Rect rect_; //kich thuoc anh
};
