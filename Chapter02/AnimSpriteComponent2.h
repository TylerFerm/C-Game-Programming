//  AnimSpriteComponent2.h

#pragma once

#include "SpriteComponent2.h"
#include <vector>
#include <unordered_map>
#include <string>

// Forward declaration
class Actor2;

// Create a component that can handle animated sprites
class AnimSpriteComponent2 : public SpriteComponent2
{
public:
	// Constructor for the animated sprite component
	AnimSpriteComponent2(Actor2* owner, int drawOrder = 100);

	// Update the animation every frame (overrides the update function from component)
	void update(float deltatime) override;

	// Set the textures used for animation
	void addAnimation(const std::string animName, const std::vector<SDL_Texture*>& textures);

	// Set the current animation
	bool setCurrentAnimation(const std::string animName);
	
	// Get the animation frame rate
	float getAnimFPS() const { return animFPS; }

	// Set the animation frame rate
	void setAnimFPS(float fps) { animFPS = fps; }

private:
	// Store all the textures in the animation
	// Old textbook way of storing one animation: std::vector<SDL_Texture*> animTextures;
	// Store the textures for multiple types of animations
	std::unordered_map<std::string, std::vector<SDL_Texture*>> animations;

	// Keep track of the current frame displayed
	float currentFrame;

	// Keep track of the animation frame rate
	// This exists to keep track of time (not be render frame rate) to ensure consistent animation speed across devices
	float animFPS;

	// Keep track of the current animation
	std::string currentAnimation;
};