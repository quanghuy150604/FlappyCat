#include "CommonFunction.h"
#include "ImgFunction.h"
#include "GameMap.h"
#include "PlayerFunction.h"
#include "Timer.h"
#include <iostream>
#include "TextFunction.h"
#include "MenuFunction.h"


ImgFunction gBackground;
TTF_Font* font_time = NULL;

bool init()

{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
			if (TTF_Init() == -1)
			{
				success = false;
			}
			font_time = TTF_OpenFont("font//dlxfont_.ttf",15);
			if (font_time == NULL)
			{
				success = false;
			}
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
				return 1;

			g_sound_put = Mix_LoadWAV("audio//sfx_wing.wav");
			g_sound_point = Mix_LoadWAV("audio//sfx_point.wav");
			g_sound_hit = Mix_LoadWAV("audio//sfx_hit.wav");
			g_sound_meomeo = Mix_LoadMUS("audio//meomeo.wav");

			if (g_sound_put == NULL || g_sound_hit == NULL || g_sound_point == NULL || g_sound_meomeo == NULL)
			{
				return false;
			}

		}
	}

	return success;
}

void close()
{
	gBackground.Free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	IMG_Quit();
	SDL_Quit();
}

bool LoadBackground() {
	bool ret = gBackground.LoadImg("map//bg.png", gRenderer);
	return ret;
}

int main(int argc, char* args[])
{

	int dead = 0;
	int high_score = 0;
	bool is_quit = false;
	if (init() == false)
		return -1;
	if (LoadBackground() == false) {
		std::cout << "false to load media";
		return -1;
	}
	Mix_PlayMusic(g_sound_meomeo, -1);
	Menu menuu;
	int ret_menu = menuu.ShowMenu(gRenderer, font_time, "map//menu1.png", 310, 440, "Play Game", "Exit", 0, 0);

	if (ret_menu == 1)
	{
		is_quit = true;
	}
	else
	{
		is_quit = false;
	}

play_again:
	int ans = 0;
	Timer fps_timer;
	
	GameMap game_map;
	game_map.LoadMap("map//map01.dat");
	game_map.LoadTile(gRenderer);

	
	Player player_;
	player_.LoadImg("img//meo4.png", gRenderer);
	player_.set_clips();

	Text result_game;
	result_game.setColor(Text::WHITE_TEXT);

	ImgFunction res;
	res.LoadImg("img//res.png", gRenderer);
	

	while (!is_quit)
	{
		fps_timer.start();
		
			while (SDL_PollEvent(&gEvent) != 0)
			{
				if (gEvent.type == SDL_QUIT)
				{
					is_quit = true;
				}
				player_.HandleInputAction(gEvent, gRenderer, g_sound_put);
			}
			SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

			SDL_RenderClear(gRenderer);

			gBackground.Render(gRenderer, NULL);
			
			Map map_data = game_map.getMap();

			player_.ShowPlayer(gRenderer);

			player_.SetMapXY(map_data.start_x_, map_data.start_y_);

			player_.PlayerMove(map_data);

			player_.CheckMap(map_data, dead, ans, g_sound_point);

			player_.CenterEntityOnMap(map_data);
			
			game_map.SetMap(map_data);

			game_map.DrawMap(gRenderer);			


			high_score = max(ans / 8, high_score);
			std::string score = "Score: ";
			std::string str_val = std::to_string(ans / 8);
			score += str_val;
			result_game.SetText(score);
			result_game.LoadFromRenderedText(font_time, gRenderer);
			result_game.RenderText(gRenderer, 480, 15);

			std::string best = "Best: ";
			std::string str_val1 = std::to_string(high_score);
			best += str_val1;
			result_game.SetText(best);
			result_game.LoadFromRenderedText(font_time, gRenderer);
			result_game.RenderText(gRenderer, 780, 15);
			
		if (dead == 1)
		{
			Mix_PlayChannel(-1, g_sound_hit, 0);
			Sleep(500);
			int ending = menuu.ShowMenu(gRenderer, font_time, "img//res.png", 350, 350, "Play Again", "Exit", ans, high_score);
			
			if (ending == 1) {
				is_quit = true;
			}
			else {
				is_quit = false;
				dead = 0;
				goto play_again;
			}
		}

		SDL_RenderPresent(gRenderer);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAMES_PER_SECOND;
		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}
	close();
	return 0;
}