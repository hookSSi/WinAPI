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
	Command* buttonA; // ���� �̵�
	Command* buttonS; // �Ʒ��� ���̵�
	Command* buttonD; // ������ �̵�
	Command* buttonW; // ���η� ���̵�
	Command* buttonSpace; // �߻�
	Command* buttonShift; // �뽬
	Command* buttonCtrl; // ����
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