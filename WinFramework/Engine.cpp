#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	ball(Vec2(300.0f, 300.0f), Vec2(100.0f, 100.0f)),
	pad(Vec2(400.0f, 500.0f), 75, 25, 255, 100, 75),
	walls(0.0f, 800.0f, 0.0f, 600.0f)
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);

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
	testBrick = Brick(RectF(Vec2(200.0f, 300.0f), Vec2(300.0f, 400.0f)), 255, 255, 255);
}

Engine::~Engine()
{
}

void Engine::Run(Window& wnd)
{
	//Thread sleep to stop burning cycles
	LARGE_INTEGER LastCounter = EngineGetWallClock();
	
	LARGE_INTEGER WorkCounter = EngineGetWallClock();

	float WorkSecondsElapsed = EngineGetSecondsElapsed(LastCounter, WorkCounter);
	float SecondsElapsedForFrame = WorkSecondsElapsed;

	while (SecondsElapsedForFrame < FPSMS)
	{
		if (SleepIsGranular)
		{
			DWORD SleepMS = (DWORD)(1000.0f * (FPSMS - SecondsElapsedForFrame));
			Sleep(SleepMS);
		}
		SecondsElapsedForFrame = EngineGetSecondsElapsed(LastCounter, EngineGetWallClock());
	}

	counter = std::to_string(cX);
	finTitle = winName + counter;
	SetWindowTextA(wnd.GetCustomWindow(), finTitle.c_str());
	cX = 1.0f / SecondsElapsedForFrame;
	Update(wnd);
	ComposeFrame();

	LARGE_INTEGER EndCounter = EngineGetWallClock();
	LastCounter = EndCounter;
}

void Engine::Update(Window& wnd)
{
	float dt = ft.Go();
	ball.Update(dt);
	pad.Update(wnd.mouse, dt);
	for (Brick& b : bricks)
	{
		b.DoBallCollision(ball);
	}
	pad.DoBallCollision(ball);
	ball.DoWallCollision(walls);
	pad.DoWallCollision(walls);
	startPos = { 100.0f, 100.0f };
	endPos = Vec2((float)(wnd.mouse.GetPosX()), (float)(wnd.mouse.GetPosY()));
	Vec2 ray_dir = endPos - startPos;
	if (testBrick.RayVsRectCollision(startPos, ray_dir, RectF(Vec2(200.0f, 300.0f), Vec2(300.0f, 400.0f)), cp, cn, t) && t < 1.0f)
	{
		testBrick = Brick(RectF(Vec2(200.0f, 300.0f), Vec2(300.0f, 400.0f)), 0, 255, 0);
		collided = true;
	}
	else
	{
		testBrick = Brick(RectF(Vec2(200.0f, 300.0f), Vec2(300.0f, 400.0f)), 255, 255, 255);
		collided = false;
	}
}

LARGE_INTEGER Engine::EngineGetWallClock() const
{
	LARGE_INTEGER Result;
	QueryPerformanceCounter(&Result);
	return Result;
}

float Engine::EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const
{
	float Result = ((float)(End.QuadPart - Start.QuadPart) / PerfCountFrequency);
	return Result;
}

void Engine::ComposeFrame()
{
	//gfx.FillScreenFast(Colors,255, 0, 0);
	gfx.ClearScreenSuperFast(Colors);
	//gfx.DrawPixel(Colors, 100, 100, 255, 0, 0);
	ball.Draw(gfx, Colors);
	pad.Draw(gfx, Colors);
	for (Brick& b : bricks)
	{
		b.Draw(gfx, Colors);
	}
	testBrick.Draw(gfx, Colors);
	gfx.DrawLine(Colors, startPos, endPos, 255, 0, 0);
	if (collided)
	{
		gfx.DrawLine(Colors, cp, cp + cn * 20.0f, 255, 255, 0);
	}
	
}


