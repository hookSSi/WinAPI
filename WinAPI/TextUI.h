#pragma once
#include "stdafx.h"
#include "Object.h"
#include<chrono>

class TextUI : public Object
{
public:
	TextUI():text(L""){};
	TextUI(LPCWSTR p_text) :text(p_text){}
	~TextUI(){};

	virtual void Draw(HWND hWnd, HDC hdc);
	virtual bool Update(){ return true; }; // 게임 오브젝트 업데이트
	LPCWSTR GetText(){ return this->text; }
	void SetText(LPCWSTR p_text){ this->text = p_text; }
private:
	LPCWSTR text; // 텍스트
};

class SpecialTextUI : public TextUI
{
public:
	SpecialTextUI() :TextUI(), timeRate(0){};
	SpecialTextUI(LPCWSTR p_text) :TextUI(p_text), timeRate(0){}
	SpecialTextUI(LPCWSTR p_text, float p_timeRate) :TextUI(p_text), timeRate(p_timeRate){}
	~SpecialTextUI(){};

	virtual void Draw(HWND hWnd, HDC hdc);
	virtual bool Update(); // 게임 오브젝트 업데이트
private:
	void Twinkle();
	bool flag = { true };
	float timeRate; // 깜빡 주기
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
};