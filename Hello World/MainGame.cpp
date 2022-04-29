#include "game.h"
#include "Constants.h"
#include "Paddle.h"

#include <algorithm>

using namespace std;

Paddle paddle = Paddle(START_PADDLE_X, START_PADDLE_Y);

void DrawPaddle(Paddle& paddle) {

	paddle.topRightX = paddle.PosX + PaddleWidth / 2;
	paddle.topRightY = paddle.PosY + PaddleHeight / 2;

	paddle.bottomLeftX = paddle.PosX - PaddleWidth / 2;
	paddle.bottomLeftY = paddle.PosY - PaddleHeight / 2;

	Play::DrawRect(Point2D(paddle.bottomLeftX, paddle.bottomLeftY), Point2D(paddle.topRightX, paddle.topRightY), Play::cBlue, true);
}


void UpdatePaddle(Paddle& paddle) {

	if (Play::KeyDown(VK_LEFT)) {
		if (paddle.bottomLeftX > 0)
		{
			paddle.PosX -= PADDLE_SPEED;
			Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "PaddleLeft!");
		}
		else {
			Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "Corner!");
		}
		
	}
	if (Play::KeyDown(VK_RIGHT))
	{
		if (paddle.topRightX < DISPLAY_WIDTH) {
			Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "PaddleRight!");
			paddle.PosX += PADDLE_SPEED;
		}
		else {
			Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "Corner!");
		}
		
	}
}

bool IsColliding( const Paddle& paddle, const GameObject& obj)
{
	const float dx = obj.pos.x - max(paddle.bottomLeftX, std::min(obj.pos.x, paddle.topRightX));
	const float dy = obj.pos.y - max(paddle.bottomLeftY, min(obj.pos.y, paddle.topRightY));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Game::SpawnBall();
	Game::SetupScene();
	Play::CentreAllSpriteOrigins();
	
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer(Play::cBlack);

	UpdatePaddle(paddle);
	DrawPaddle(paddle);

	std::vector<int> ballIds = Play::CollectGameObjectIDsByType(Type_Ball);
	for (int i = 0; i < ballIds.size(); i++)
	{
		if (IsColliding(paddle, Play::GetGameObject(ballIds[i])))
		{
			Play::DrawDebugText(Point2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2), "paddleCollision!!!");
			Play::GetGameObject(ballIds[i]).velocity.y = (Play::GetGameObject(ballIds[i]).velocity.y < 0) ? BALL_SPEED : -BALL_SPEED;;
		}
	}

	Game::StepFrame(elapsedTime);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}