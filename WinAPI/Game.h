#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include "EventManager.h"

/* ���� ���� */
class Object;
class Scene;
class Map;
class TextUI;
class InputHandler;
class Tank;
class EventManager;

class Game : public Singleton < Game >
{
public:
	EventManager* eventManager;

	// �÷��̾� 1,2
	Tank* player1_tank;
	Tank* player2_tank;

	// ���ھ�
	TextUI* player1_scoreUI;
	int player1_score = { 100 };
	TextUI* player2_scoreUI;
	int player2_score = { 100 };

	Game();
	virtual ~Game();

	HWND Game::GenerateGameWindow(HINSTANCE hInstance, LPCWSTR lpszClass, WNDPROC WndProc);
	bool Initilize(); // �ʱ�ȭ
	bool Start();
	bool Draw(HWND hWnd, HDC hdc); // �׸��� �۾�
	bool Update(); // ������Ʈ
	bool ExitGame(); // ���� ���� = ���α׷� ����

	bool SetScene(SCENE_NAME scene_name); // �ҷ��� Scene �ε��� ����
	bool LoadScene(); // Scene �ҷ�����

	bool InputHandle(WPARAM wParam); // �Է� �ޱ�

	const int GetWD_STYLE(){ return this->WD_STYLE; }
	bool SetWD_STYLE(const int style){ this->WD_STYLE = style; }

	
	Map* GetMap() { return (this->map_list[(int)currentScene]); }// �� ��ȯ
	Scene* GetScene() { return (this->scene_list[(int)currentScene]); }

	void LoadNewGame();
	void CreateBullet(LPARAM lParam, int p_master);
	void AddGameObjet(Object* object);
private:

	// Ű����
	InputHandler* player1_input;
	InputHandler* player2_input;

	// ������ ��Ÿ��
	int WD_STYLE = (WS_CAPTION |
		WS_SYSMENU);
	// scene ���� ���
	vector<Scene*> scene_list; // scene ����Ʈ
	bool is_scene_loaded = false; // scene�� �ε� �糪��?
	SCENE_NAME currentScene;
	// ��
	vector<Map*> map_list; // ���� ����Ʈ

	bool isLoaded = { false };
};