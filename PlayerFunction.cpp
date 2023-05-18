#include "PlayerFunction.h"
#include "CommonFunction.h"

Player::Player()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_plus = 0;
	y_plus = 0;
	width_frame = 0;
	height_frame = 0;
	jump = 0;
	map_x_ = 0;
	map_y_ = 0;
}

Player::~Player()
{
}

bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = ImgFunction::LoadImg(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w / 8;
		height_frame = rect_.h;
	}
	return ret;
}

void Player::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip_[i].x = i * width_frame;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame;
			frame_clip_[i].h = height_frame;
		}

	}
}

void Player::ShowPlayer(SDL_Renderer* des)
{
		
		LoadImg("img//meo4.png", des);
		frame++;
		if (frame >= 8)
		{
			frame = 0;
		}
		rect_.x = x_pos - map_x_;
		rect_.y = y_pos - map_y_;

		SDL_Rect* currentClip = &frame_clip_[frame];
		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };


		SDL_RenderCopy(des, picture_, currentClip, &renderQuad);
	

}

void Player::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* sound)
{
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_RIGHT)
		{
			jump = 1;
			Mix_PlayChannel(-1, sound, 0);
		}
	}
	if (events.type == SDL_MOUSEBUTTONUP)
		jump = 0;
}

void Player::PlayerMove(Map& map_data)
{
	x_plus = 0;
	y_plus += Gravity_Speed;

	if (y_plus >= Max_Fall_Speed)
	{
		y_plus = Max_Fall_Speed;
	}
	
	x_plus += Player_Speed;

	if (jump == 1)
	{
		y_plus = - PLAYER_JUMP_VAL;
		jump = 0;
	}
}

void Player::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos - (SCREEN_WIDTH /5);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos - (SCREEN_HEIGHT/2);

	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void Player::CheckMap(Map& map_data, int& action, int& ans, Mix_Chunk* point_sound)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_plus) / TILE_SIZE;
	x2 = (x_pos + x_plus + width_frame ) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		
		if ((map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != 1 ) || (map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != 1))
		{				
			action = 1;
		}
		if (map_data.tile[y1][x2] == 1 || map_data.tile[y2][x2] == 1)
		{
			ans++;
			if (ans % 8 == 0 && ans > 0) {
				Mix_PlayChannel(-1, point_sound, 0);
			}
		}
		
	}

	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = (x_pos + 10) / TILE_SIZE;
	x2 = (x_pos + width_min - 10) / TILE_SIZE;

	y1 = (y_pos + y_plus + 10) / TILE_SIZE;
	y2 = (y_pos + y_plus + height_frame - 10) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_plus > 0)
		{
			if ((map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] != 1) || (map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != 1))
			{
				action = 1;
			}
		}
		else if (y_plus < 0)
		{
			if ((map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] != 1) || (map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != 1))
			{
				action = 1;
			}
		}
	}

	x_pos += x_plus;
	y_pos += y_plus;
}