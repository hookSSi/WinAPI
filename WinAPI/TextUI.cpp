#include "TextUI.h"

void TextUI::Draw(HWND hWnd, HDC hdc)
{
	SetTextColor(hdc, WHITE_COLOR);
	SetBkColor(hdc, BLACK_COLOR);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, position.x, position.y, this->GetText(), wcslen(this->GetText()));
}

void SpecialTextUI::Draw(HWND hWnd, HDC hdc)
{
	if (flag)
	{
		SetTextColor(hdc, WHITE_COLOR);
		SetBkColor(hdc, BLACK_COLOR);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, position.x, position.y, this->GetText(), wcslen(this->GetText()));
	}
}

bool SpecialTextUI::Update()
{
	this->Twinkle();

	return true;
}

void SpecialTextUI::Twinkle()
{
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - this->start;

	if (sec.count() >= timeRate)
	{
		flag = !flag;
		this->start = std::chrono::system_clock::now();
	}
}