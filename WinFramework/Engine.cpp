#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	gameMenu(RectF(Vec2(0.0f, 0.0f), Vec2(800.0f, 600.0f)), 163, 172, 255, true)
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);
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
	if (!gameMenu.isVisible())
	{
		if (!isInit)
		{
			if (game != nullptr)
			{
				delete game;
				game = nullptr;
			}
			game = new ArkanoidGame(3);
			if (game != nullptr)
			{
				isInit = true;
			}
		}
		else
		{
			if (!game->isGameOver())
			{
				game->Update(dt, wnd.mouse);
			}
			else
			{
				gameMenu.SetGameMenuVisibility(game->isGameOver());
				isInit = false;
			}
		}


	}
	else
	{
		gameMenu.Update(wnd.mouse);
		if (gameMenu.isGameQuit())
		{
			PostQuitMessage(0);
		}
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

	if (!gameMenu.isVisible())
	{
		if (isInit)
		{
			game->Draw(gfx, Colors);
		}
	}
	else
	{
		gameMenu.Draw(gfx, Colors);
	}
}


