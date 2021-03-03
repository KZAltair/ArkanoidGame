#include "GameMenu.h"

GameMenu::GameMenu(const RectF& size, unsigned char r, unsigned char g, unsigned char b, bool visible)
	:
	rect(size),
	R(r),
	G(g),
	B(b),
	isActive(visible)
{
	buttonStart = new UIElement(RectF(Vec2(300.0f, 300.0f), Vec2(500.0f, 325.0f)), 120, 100, 50, true);
	buttonQuit = new UIElement(RectF(Vec2(300.0f, 350.0f), Vec2(500.0f, 375.0f)), 120, 100, 50, true);
}

void GameMenu::Draw(Graphics& gfx, int* Colors)
{
	if (isActive)
	{
		gfx.DrawRect(Colors, rect, R, G, B);
		buttonStart->Draw(gfx, Colors);
		buttonQuit->Draw(gfx, Colors);
	}
}

void GameMenu::Update(const Mouse& mouse)
{
	if (isActive)
	{
		buttonStart->SetButtonActive(true);
		buttonQuit->SetButtonActive(true);
		buttonStart->Update(mouse);
		buttonQuit->Update(mouse);
		if (buttonStart->GetSelectedStatus())
		{
			buttonStart->SetColor(200, 100, 50);
			if (mouse.LeftIsPressed())
			{
				isActive = false;
			}
		}
		else
		{
			buttonStart->SetColor(120, 100, 50);
		}
		if (buttonQuit->GetSelectedStatus())
		{
			buttonQuit->SetColor(200, 100, 50);
			if (mouse.LeftIsPressed())
			{
				isQuit = true;
			}
		}
		else
		{
			buttonQuit->SetColor(120, 100, 50);
		}
	}
}

bool GameMenu::isVisible() const
{
	return isActive;
}

bool GameMenu::isGameQuit() const
{
	return isQuit;
}

void GameMenu::SetGameMenuVisibility(bool inFlag)
{
	isActive = inFlag;
}

GameMenu::~GameMenu()
{
	if (buttonStart != nullptr)
	{
		delete buttonStart;
		buttonStart = nullptr;
	}
	if (buttonQuit != nullptr)
	{
		delete buttonQuit;
		buttonQuit = nullptr;
	}
}
