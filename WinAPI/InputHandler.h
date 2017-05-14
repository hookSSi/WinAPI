#pragma once
#include<Windows.h>

class Command
{
public:
	virtual ~Command(){};
	virtual bool execute() = 0;
};

class InputHandler
{
public:
	InputHandler(){}
	~InputHandler(){ delete(buttonA); 
					 delete(buttonS); 
					 delete(buttonD);
					 delete(buttonW);
					 delete(buttonSpace);
					 delete(buttonShift);
					 delete(buttonCtrl);
	}

	bool InputHandle(WPARAM wParam);
	bool SetButtonA(Command* button){ buttonA = button; return true; }
	bool SetButtonD(Command* button){ buttonD = button; return true; }
private:
	Command* buttonA; // 왼쪽 이동
	Command* buttonS; // 아래로 포이동
	Command* buttonD; // 오른쪽 이동
	Command* buttonW; // 위로로 포이동
	Command* buttonSpace; // 발사
	Command* buttonShift; // 대쉬
	Command* buttonCtrl; // 점프
};

inline bool InputHandler::InputHandle(WPARAM wParam)
{
	switch (wParam)
	{
	case 'A':
	case 'a':
		if (buttonA != nullptr)
		{
			buttonA->execute();
		}		
		break;
	case 'S':
	case 's':
		if (buttonS != nullptr)
		{
			buttonS->execute();
		}
		break;
	case 'D':
	case 'd':
		if (buttonD != nullptr)
		{
			buttonD->execute();
		}
		break;
	case 'W':
	case 'w':
		if (buttonW != nullptr)
		{
			buttonW->execute();
		}
		break;
	case VK_SPACE:
		if (buttonSpace != nullptr)
		{
			buttonSpace->execute();
		}
		break;
	case VK_SHIFT:
		if (buttonShift != nullptr)
		{
			buttonShift->execute();
		}
		break;
	case VK_CONTROL:
		if (buttonCtrl != nullptr)
		{
			buttonCtrl->execute();
		}
		break;
	}

	return true;
}