#include "TextUI.h"

void TextUI::Draw(HWND hWnd, HDC hdc)
{
	SetTextColor(hdc, WHITE_COLOR);
	SetBkColor(hdc, BLACK_COLOR);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, position.x, position.y, text->c_str(), this->length);
}

void SpecialTextUI::Draw(HWND hWnd, HDC hdc)
{
	if (flag)
	{
		SetTextColor(hdc, WHITE_COLOR);
		SetBkColor(hdc, BLACK_COLOR);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, position.x, position.y, text->c_str() , this->length);
	}
}

bool SpecialTextUI::Update()
{
	this->Twinkle();

	return true;
}

void SpecialTextUI::Twinkle()
{
	currentTime = chrono::system_clock::now();

	std::chrono::duration<double> sec = currentTime - previousTime;

	if (sec.count() > timeRate)
	{
		flag = !flag;
		previousTime = currentTime;
	}
}