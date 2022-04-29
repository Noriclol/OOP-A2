#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void Game::SpawnBall()
{
	const int objectId = Play::CreateGameObject(ObjectType::Type_Ball, {START_BALL_X, START_BALL_Y }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ -1, -1 }) * BALL_SPEED;
}

void Game::SetupScene()
{
	for (int y = 0; y < BRICK_AMOUNT_Y; y++)
	{
		for (int x = 0; x < BRICK_AMOUNT_X; x++)
		{
			Play::CreateGameObject(ObjectType::Type_Brick, { BRICK_OFFSET_X + x * BRICK_SPACING_X, BRICK_OFFSET_Y + y * BRICK_SPACING_Y }, 6, "brick");
		}
	}
}

void Game::StepFrame(float timeSinceStart)
{
	//Collect gameobjects
	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
	std::vector<int> brickIds = Play::CollectGameObjectIDsByType(Type_Brick);

	//Draw/Update Ball
	for (int i = 0; i < ballIds.size(); i++)
	{
		float velocityX = Play::GetGameObject(ballIds[i]).velocity.x;
		float velocityY = Play::GetGameObject(ballIds[i]).velocity.y;
		float positionX = Play::GetGameObject(ballIds[i]).pos.x;
		float positionY = Play::GetGameObject(ballIds[i]).pos.y;

		if (positionX < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = BALL_SPEED;

		}
		if (positionY < 0)
		{
			Play::GetGameObject(ballIds[i]).velocity.y = BALL_SPEED;
		}

		if (positionX > DISPLAY_WIDTH)
		{
			Play::GetGameObject(ballIds[i]).velocity.x = -BALL_SPEED;

		}
		if (positionY > DISPLAY_HEIGHT)
		{
			Play::GetGameObject(ballIds[i]).velocity.y = -BALL_SPEED;
		}

		Play::UpdateGameObject(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Play::GetGameObject(ballIds[i]));


	}

	//Check for collisions between ball and bricks
	for (int i = 0; i < ballIds.size(); i++) {
		for (int j = 0; j < brickIds.size(); j++)
		{
			GameObject& ball = Play::GetGameObject(ballIds[i]);
			GameObject& brick = Play::GetGameObject(brickIds[j]);

			if (Play::IsColliding(ball, brick)) {
				Play::DestroyGameObject(brickIds[j]);

				ball.velocity.x = (ball.velocity.x < 0) ? BALL_SPEED : -BALL_SPEED;
				ball.velocity.y = (ball.velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;

			}
		}

	}


	//Render Bricks
	for (int i = 0; i < brickIds.size(); i++)
	{



		Play::UpdateGameObject(Play::GetGameObject(brickIds[i]));
		Play::DrawObject(Play::GetGameObject(brickIds[i]));
	}



}






