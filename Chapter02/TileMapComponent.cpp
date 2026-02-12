// TileMapComponent.cpp

#include "TileMapComponent.h"
#include "Actor2.h"
#include <fstream>
#include <sstream>



TileMapComponent::TileMapComponent(Actor2* owner, int drawOrder)
	: SpriteComponent2(owner, drawOrder)
	, tileWidth(0)
	, tileHeight(0)
{}


void TileMapComponent::loadCSV(std::string fileName) {
	// Create a file pointer
	std::ifstream file;

	// Open the provided file
	file.open(fileName);

	// Read a line from the file
	std::string line;
	while (std::getline(file, line)) {
		
		// Prepare variables for parsing the line
		std::stringstream ss(line);
		std::string cell;
		std::vector<int> row;

		// Go through the line and save all the cells to the vector
		while (std::getline(ss, cell, ',')) { row.push_back(std::stoi(cell)); }

		// Save the row to map
		map.push_back(row);
	}
	
	// Close the file
	file.close();
}


void TileMapComponent::printMap() const {
	// Check that map is not empty and then print it
	if (!map.empty()) {
		// Print the contents of the map
		for (std::vector<int> row : map) {
			for (int value : row) {
				SDL_Log("%d", value);
			}
		}
	}
	else { SDL_Log("No map is currently loaded."); }
}


void TileMapComponent::setTileDimensions(int width, int height) {
	this->tileWidth = width;
	this->tileHeight = height;
}


void TileMapComponent::draw(SDL_Renderer* renderer)
{
	// Calculate number of tiles per row
	int tilesPerRow = textureWidth / tileWidth;
	
	// Loop through each row of tiles in the map
	int y = 0;
	for (std::vector<int> row : map) {	
		int x = 0;
		// Loop through each tile in the row
		for (int value : row) {
			// Don't draw a tile if the value is -1
			if (value != -1) {
				// The destination to place the tile
				SDL_Rect tileDest;
				tileDest.w = tileWidth;
				tileDest.h = tileHeight;
				tileDest.x = x;
				tileDest.y = y;

				// Draw only a subsection of 
				SDL_Rect sourceTile;
				sourceTile.h = tileHeight;
				sourceTile.w = tileWidth;

				// Calculate which tile to pick from based on value
				sourceTile.x = ((value % tilesPerRow)) * tileWidth;
				sourceTile.y = ((int)(value / tilesPerRow)) * tileHeight;

				// Draw the tile
				SDL_RenderCopy(renderer, texture, &sourceTile, &tileDest);
			}
			x += 32;
		}
		y += 32;
	}
}
