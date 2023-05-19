#pragma once

#include <windows.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include<SDL_mixer.h>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent; 

static Mix_Chunk* g_sound_put;
static Mix_Chunk* g_sound_hit;
static Mix_Chunk* g_sound_point;
static Mix_Music* g_sound_meomeo;

const int FRAMES_PER_SECOND = 24;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int SPEED_SCREEN = 2;


const int RENDER_DRAW_COLOR = 0XFF;

const int COLOR_KEY_R = 195;
const int COLOR_KEY_G = 195;
const int COLOR_KEY_B = 195;


#define TILE_SIZE 64
#define BLANK_TILE 0

#define MAX_MAP_X 750
#define MAX_MAP_Y 10


typedef struct Map
{
    int start_x_; // vi tri o tile map
    int start_y_;

    int max_x_; // chi so o tile map vd o: thu 3 max_y = 3 = start_x/64 
    int max_y_;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    const char* file_name_;
} Map;

