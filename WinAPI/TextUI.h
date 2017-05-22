#pragma once
#include "stdafx.h"
#include "Object.h"
#include<chrono>

class TextUI : public Object
{
public:
	wstring *text; // �ؽ�Ʈ
	int length;

	TextUI() :length(0){ text = new wstring(); this->SetText(L""); };
	TextUI(LPCWSTR p_text) :length(wcslen(p_text)){ text = new wstring(); this->SetText(p_text); }
	~TextUI(){ delete text; };

	virtual void Draw(HWND hWnd, HDC hdc); // ������
	virtual bool Update(){ return true; }; // ���� ������Ʈ ������Ʈ
	LPCWSTR GetText(){ return text->c_str(); } // �ؽ�Ʈ�� LPCWSTR�� ��ȯ
	void SetText(LPCWSTR p_text){ text->clear(); text->assign(p_text); length = text->length(); } // LPCWSTR�� �ؽ�Ʈ�� ����
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
	virtual bool Update(); // ���� ������Ʈ ������Ʈ
private:
	void Twinkle();
	chrono::system_clock::time_point previousTime = { currentTime };
	bool flag = { true };
	float timeRate; // ���� �ֱ�
};