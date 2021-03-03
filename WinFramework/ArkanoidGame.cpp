#include "ArkanoidGame.h"

ArkanoidGame::ArkanoidGame(int numLives)
	:
	walls(0.0f, 800.0f, 0.0f, 600.0f),
	lives(numLives)
{
	gameOver = false;
	clicked = false;
	pad = new Paddle(Vec2(400.0f, 500.0f), 75, 25, 255, 100, 75);
	ball = new Ball(pad->GetPos() - Vec2(0.0f, 20.0f), Vec2(0.0f, 0.0f));
	bricks = new Brick[nBricks];

	Vec2 topLeft = Vec2(100.0f, 50.0f);
	int i = 0;
	int changingColor = 50;
	int stratingColor = 50;

	for (int y = 0; y < Rows; y++)
	{
		for (int x = 0; x < Colls; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2((float)x * brickWidth, (float)y * brickHeight),
				topLeft + Vec2((float)x * brickWidth + brickWidth, (float)y * brickHeight + brickHeight)),
				y * changingColor + stratingColor, y * changingColor, y * changingColor + stratingColor);
			i++;
		}
	}
}

ArkanoidGame::~ArkanoidGame()
{
	if (ball != nullptr)
	{
		delete ball;
		ball = nullptr;
	}
	if (pad != nullptr)
	{
		delete pad;
		pad = nullptr;
	}
	if (bricks != nullptr)
	{
		delete[] bricks;
		bricks = nullptr;
	}
}

void ArkanoidGame::Update(float dt, const Mouse& mouse)
{

	if (wait < 0.2f)
	{
		wait += dt;
	}
	if (wait > 0.2f)
	{
		wait = dt;
		if (mouse.LeftIsPressed() && !clicked)
		{
			ball->SetVelocity(Vec2(300.0f, -300.0f));
			clicked = true;
		}
	}
	if (clicked)
	{

		ball->Update(dt);
		pad->Update(mouse, dt);
		Vec2 bCp, bCn, pCp, pCn;
		float bT = 0.0f;
		float pT = 0.0f;

		/*
		bool collisionHappened = false;
		float curColDistSq;
		int curColIndex;

		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].CheckBallCollision(*ball))
			{
				const float newColDistSq = (ball->GetPosition() - bricks[i].GetCenter()).GetLengthSq();
				if (collisionHappened)
				{
					if (newColDistSq < curColDistSq )
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					collisionHappened = true;
				}
			}
		}
		if (collisionHappened)
		{
			if (bricks[curColIndex].DoTraceCollisionTest(*ball, bricks[curColIndex].GetOriginalRect(), bCp, bCn, bT, dt))
			{
				numBricks++;
			}
		}
		*/
		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].DoTraceCollisionTest(*ball, bricks[i].GetOriginalRect(), bCp, bCn, bT, dt))
			{
				numBricks++;
				break;
			}
		}
		pad->DoTraceCollisionTest(*ball, pad->GetRect(), pCp, pCn, pT, dt);
		//pad.DoBallCollision(ball);
		ball->DoWallCollision(walls);
		pad->DoWallCollision(walls);

		if (ball->GetLifeStatus())
		{
			if (lives > 1)
			{
				lives--;
				clicked = false;
			}
			else
			{
				gameOver = true;
				clicked = false;
				wait = 0.0f;
			}
			ball->SetLifeStatus(false);
		}
	}
	else
	{
		ball->SetPos(pad->GetPos() - Vec2(0.0f, 20.0f));
		ball->Update(dt);

		pad->Update(mouse, dt);
		pad->DoWallCollision(walls);
	}
	if (numBricks >= nBricks)
	{
		gameOver = true;
		clicked = false;
		wait = 0.0f;
	}
}

void ArkanoidGame::Draw(Graphics& gfx, int* Colors)
{
	//gfx.DrawPixel(Colors, 100, 100, 255, 0, 0);
	gfx.DrawRect(Colors, walls, 65, 89, 110);
	ball->Draw(gfx, Colors);
	pad->Draw(gfx, Colors);
	for (int i = 0; i < nBricks; i++)
	{
		bricks[i].Draw(gfx, Colors);
	}
	for (int i = 0; i < lives; i++)
	{
		gfx.DrawRect(Colors, RectF(Vec2(20.0f + i * 20.0f, 550.0f), Vec2(30.0f + i * 20.0f, 560.0f)), 255, 0, 0);
	}
}

bool ArkanoidGame::isGameOver() const
{
	return gameOver;
}
