#pragma once
#include "stdafx.h"

class Command
{
public:
	virtual ~Command(){};
	virtual void execute(Tank& tank) = 0;
};

class InputHandler
{
	friend class InputHandler2;

public:
	InputHandler(){}
	virtual ~InputHandler(){ delete(buttonA); 
					 delete(buttonS); 
					 delete(buttonD);
					 delete(buttonW);
					 delete(buttonShift);
					 delete(buttonCtrl);
	}

	virtual Command* InputHandle(WPARAM wParam);
	void SetButtonA(Command* button){ buttonA = button;}
	void SetButtonS(Command* button){ buttonS = button; }
	void SetButtonD(Command* button){ buttonD = button;}
	void SetButtonW(Command* button){ buttonW = button; }
	void SetButtonShift(Command* button) { buttonShift = button; }
	void SetButtonCtrl(Command* button) { buttonCtrl = button; }
private:
	Command* buttonA; // 왼쪽 이동
	Command* buttonS; // 아래로 포이동
	Command* buttonD; // 오른쪽 이동
	Command* buttonW; // 위로로 포이동
	Command* buttonShift; // 발사
	Command* buttonCtrl; // 점프
};

inline Command* InputHandler::InputHandle(WPARAM wParam)
{
	switch (wParam)
	{
	case 'A':
	case 'a':
		if (buttonA != nullptr)
		{
			return buttonA;
		}		
		break;
	case 'S':
	case 's':
		if (buttonS != nullptr)
		{
			return buttonS;
		}
		break;
	case 'D':
	case 'd':
		if (buttonD != nullptr)
		{
			return buttonD;
		}
		break;
	case 'W':
	case 'w':
		if (buttonW != nullptr)
		{
			return buttonW;
		}
		break;
	case VK_SHIFT:
		if (buttonShift != nullptr)
		{
			return buttonShift;
		}
		break;
	case VK_CONTROL:
		if (buttonCtrl != nullptr)
		{
			return buttonCtrl;
		}
		break;
	}

	return nullptr;
}

class InputHandler2 : public InputHandler
{
public:
	InputHandler2(){}
	virtual ~InputHandler2(){}
	virtual Command* InputHandle(WPARAM wParam);
};

inline Command* InputHandler2::InputHandle(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if (buttonA != nullptr)
		{
			return buttonA;
		}
		break;
	case VK_DOWN:
		if (buttonS != nullptr)
		{
			return buttonS;
		}
		break;
	case VK_RIGHT:
		if (buttonD != nullptr)
		{
			return buttonD;
		}
		break;
	case VK_UP:
		if (buttonW != nullptr)
		{
			return buttonW;
		}
		break;
	case 'n':
	case 'N':
		if (buttonShift != nullptr)
		{
			return buttonShift;
		}
		break;
	case 'm':
	case 'M':
		if (buttonCtrl != nullptr)
		{
			return buttonCtrl;
		}
		break;
	}

	return nullptr;
}