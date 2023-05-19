#pragma once
#include "General.h"
#include "ImgFunction.h"

#define Gravity_Speed  5
#define Max_Fall_Speed  14
#define Player_Speed  8
#define PLAYER_JUMP_VAL 18


class Player : public ImgFunction
{
public:

	Player();
	~Player();

	bool LoadImg(std::string path, SDL_Renderer* screen);

	void ShowPlayer(SDL_Renderer* des);

	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* sound);

	void set_clips();

	void PlayerMove(Map& map_data);

	void CheckMap(Map& map_data, int& dead, int& ans, Mix_Chunk* point_sound);

	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }

	void CenterEntityOnMap(Map& map_data);
 
private:

	float x_plus;
	float y_plus;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	SDL_Rect frame_clip_[8];

	int jump;
	int frame;

	int map_x_;
	int map_y_;

};

