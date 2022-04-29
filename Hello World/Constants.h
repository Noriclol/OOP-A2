#pragma once
//Display
const int DISPLAY_WIDTH = 320;
const int DISPLAY_HEIGHT = 480;
const int DISPLAY_SCALE = 2;

//Paddle
const int START_PADDLE_X = DISPLAY_WIDTH / 2;
const int START_PADDLE_Y = DISPLAY_HEIGHT - 50;
const int PaddleWidth = 40;
const int PaddleHeight = 5;
const float PADDLE_SPEED = 1.5f;

//Ball
const int START_BALL_X = DISPLAY_WIDTH / 2;
const int START_BALL_Y = DISPLAY_HEIGHT - 60;
const float BALL_SPEED = 1.0f;
//Bricks
//GameConsts


const int BRICK_AMOUNT_X = 18;
const int BRICK_AMOUNT_Y = 4;
const int BRICK_OFFSET_X = 17;
const int BRICK_OFFSET_Y = 11;
const int BRICK_SPACING_X = 17;
const int BRICK_SPACING_Y = 11;







enum ObjectType {
	Type_Ball,
	Type_Player,
	Type_Brick,
	Type_GameBoard
};