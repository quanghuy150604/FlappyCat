#pragma once

#include "CommonFunction.h"
#include "ImgFunction.h"

#define MAX_TILES 20

class Tilemap : public ImgFunction
{
public:
	Tilemap() {;}
	~Tilemap() {;}
};

class GameMap
{
public:

	GameMap() {;}
	~GameMap() {;}

	void LoadMap(const char* name); 
	
	void LoadTile(SDL_Renderer* screen);
	
	void DrawMap(SDL_Renderer* screen);  
	
	Map getMap() const { return game_map; };
	
	void SetMap(Map& map_data) { game_map = map_data; }
private:
	
	Map game_map;
	
	Tilemap tile_map[MAX_TILES];
};
