#pragma once
#include "stdafx.h"
#include "Object.h"
#include<chrono>

class TextUI : public Object
{
public:
	wstring *text; // 텍스트
	int length;

	TextUI() :length(0){ text = new wstring(); this->SetText(L""); };
	TextUI(LPCWSTR p_text) :length(wcslen(p_text)){ text = new wstring(); this->SetText(p_text); }
	~TextUI(){ delete text; };

	virtual void Draw(HWND hWnd, HDC hdc); // 랜더링
	virtual bool Update(){ return true; }; // 게임 오브젝트 업데이트
	LPCWSTR GetText(){ return text->c_str(); } // 텍스트를 LPCWSTR로 반환
	void SetText(LPCWSTR p_text){ text->clear(); text->assign(p_text); length = text->length(); } // LPCWSTR을 텍스트로 설정
	void SetText(int num){ text->clear(); text->assign(to_wstring(num)); length = text->length(); }
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
	chrono::system_clock::time_point previousTime = { currentTime };
	bool flag = { true };
	float timeRate; // 깜빡 주기
};