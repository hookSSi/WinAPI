#pragma once
#include "stdafx.h"
#include "Singleton.h"

/* ���� ���� */
class Scene;
class Map;
class TextUI;

class Game : public Singleton < Game >
{
public:
	// ���ھ�
	TextUI* player1_scoreUI;
	int player1_score = { 100 };
	TextUI* player2_scoreUI;
	int player2_score = { 100 };

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

	
	Map* GetMap() { return (this->map_list[currentScene]); }// �� ��ȯ
	Scene* GetScene() { return (this->scene_list[currentScene]); }

	void CreateBullet(LPARAM lParam);
private:
	// ������ ��Ÿ��
	int WD_STYLE = (WS_CAPTION |
		WS_SYSMENU);
	// scene ���� ���
	vector<Scene*> scene_list; // scene ����Ʈ
	bool is_scene_loaded = false; // scene�� �ε� �糪��?
	int currentScene;
	// ��
	vector<Map*> map_list; // ���� ����Ʈ

	bool isLoaded = { false };
};