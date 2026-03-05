// TileMapComponent.h

#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
	// Constructor for the TileMapComponent class
	TileMapComponent(Actor* owner, int drawOrder = 100);

	// Load and read the tilemap csv file (where the tiles go)
	void loadCSV(std::string fileName);

	// Print the current map
	void printMap() const;

	// Set the tile width and height
	void setTileDimensions(int width, int height);

	// Override the draw function to draw only 1 tile
	void draw(SDL_Renderer* renderer) override;

private:
	// Store the information found in the csv file
	std::vector<std::vector<int>> map;

	// Set tile width and height
	int tileWidth;
	int tileHeight;
};