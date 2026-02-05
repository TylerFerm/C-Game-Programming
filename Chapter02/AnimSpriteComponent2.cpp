
#include "AnimSpriteComponent2.h"
#include "Math.h"

AnimSpriteComponent2::AnimSpriteComponent2(Actor2* owner, int drawOrder)
	:SpriteComponent2(owner, drawOrder) // Call the constructor of the inherited class
	, currentFrame(0.0f)
	, animFPS(24.0f)
	, currentAnimation("")
{}


void AnimSpriteComponent2::update(float deltatime)
{
	// First, call the default update defined from the inherited class
	SpriteComponent2::update(deltatime);

	// As long as there are textures in the animation vector, update animation
	if (currentAnimation != "") {
		// Update the current frame based on frame rate and delta time
		currentFrame += animFPS * deltatime;

		// Warp current frame if needed
		while (currentFrame >= animations[currentAnimation].size()) {
			currentFrame -= animations[currentAnimation].size();
		}

		// Set the current texture
		setTexture(animations[currentAnimation][static_cast<int>(currentFrame)]);
	}
}


void AnimSpriteComponent2::addAnimation(const std::string animName, const std::vector<SDL_Texture*>& textures) {
	// If animation is not in map, and textures isn't empty, add it
	if (animations.find(animName) == animations.end() && textures.size() > 0) {
		animations[animName] = textures;
	}
}


bool AnimSpriteComponent2::setCurrentAnimation(const std::string animName)
{
	// Check to make sure animName is in the map
	auto iter = animations.find(animName);
	
	if (iter != animations.end()) {
		// Set the animation to play from the beginning
		currentAnimation = animName;
		currentFrame = 0.0f;
		setTexture(iter->second[0]);
		return true;
	}

	// Animation could not be sent
	return false;
}
