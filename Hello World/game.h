#pragma once

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Constants.h"

#include <string>

static class Game {
public:
	
	static void SpawnBall();
	static void SetupScene();
	static void StepFrame(float timeSinceStart);

};



