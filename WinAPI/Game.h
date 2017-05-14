#pragma once
#include "stdafx.h"
#include "Singleton.h"

/* ���� ���� */
class Scene;
class Map;

class Game : public Singleton < Game >
{
public:
	Game(){};
	virtual ~Game(){}

	HWND Game::GenerateGameWindow(HINSTANCE hInstance, LPCWSTR lpszClass, WNDPROC WndProc);
	bool Initilize(); // �ʱ�ȭ
	bool Start();
	bool Draw(HWND hWnd, HDC hdc); // �׸��� �۾�
	bool Update(); // ������Ʈ
	bool ExitGame(); // ���� ���� = ���α׷� ����

	bool SetScene(int number); // �ҷ��� Scene �ε��� ����
	bool LoadScene(); // Scene �ҷ�����

	bool InputHandle(WPARAM wParam); // �Է� �ޱ�

	const int GetWD_STYLE(){ return this->WD_STYLE; }
	bool SetWD_STYLE(const int style){ this->WD_STYLE = style; }
private:
	// ������ ��Ÿ��
	int WD_STYLE = (WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME);
	// scene ���� ���
	vector<Scene*> scene_list; // scene ����Ʈ
	bool is_scene_loaded = false; // scene�� �ε� �糪��?
	int currentScene;
	// ��
	vector<Map*> map_list; // ���� ����Ʈ
};