#include "UIElement.h"

UIElement::UIElement(const RectF& rect_in, unsigned char r, unsigned char g, unsigned char b, bool visible)
	:
	rect(rect_in),
	R(r),
	G(g),
	B(b),
	isActive(visible)
{
}

void UIElement::Draw(Graphics& gfx, int* Colors)
{
	if (isActive)
	{
		gfx.DrawRect(Colors, rect, R, G, B);
	}
}

void UIElement::Update(const Mouse& mouse)
{
	if (isActive)
	{
		Vec2 mPos;
		mPos.x = (float)mouse.GetPosX();
		mPos.y = (float)mouse.GetPosY();
		if (mPos.x > rect.left && mPos.x < rect.right &&
			mPos.y > rect.top && mPos.y < rect.bottom)
		{
			isSelected = true;
			if (mouse.LeftIsPressed())
			{
				isActive = false;
			}
		}
		else
		{
			isSelected = false;
		}
	}
}

void UIElement::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	R = r;
	G = g;
	B = b;
}

void UIElement::SetButtonActive(bool inFlag)
{
	isActive = inFlag;
}

bool UIElement::GetSelectedStatus() const
{
	return isSelected;
}

bool UIElement::GetActiveStatus() const
{
	return isActive;
}
