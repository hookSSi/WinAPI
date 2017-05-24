#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include "EventManager.h"

/* 전방 선언 */
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

	// 플레이어 1,2
	Tank* player1_tank;
	Tank* player2_tank;

	// 스코어
	TextUI* player1_scoreUI;
	int player1_score = { 100 };
	TextUI* player2_scoreUI;
	int player2_score = { 100 };

	Game();
	virtual ~Game();

	HWND Game::GenerateGameWindow(HINSTANCE hInstance, LPCWSTR lpszClass, WNDPROC WndProc);
	bool Initilize(); // 초기화
	bool Start();
	bool Draw(HWND hWnd, HDC hdc); // 그리기 작업
	bool Update(); // 업데이트
	bool ExitGame(); // 게임 종료 = 프로그램 종료

	bool SetScene(SCENE_NAME scene_name); // 불러올 Scene 인덱스 설정
	bool LoadScene(); // Scene 불러오기

	bool InputHandle(WPARAM wParam); // 입력 받기

	const int GetWD_STYLE(){ return this->WD_STYLE; }
	bool SetWD_STYLE(const int style){ this->WD_STYLE = style; }

	
	Map* GetMap() { return (this->map_list[(int)currentScene]); }// 맵 반환
	Scene* GetScene() { return (this->scene_list[(int)currentScene]); }

	void LoadNewGame();
	void CreateBullet(LPARAM lParam, int p_master);
	void AddGameObjet(Object* object);
private:

	// 키조작
	InputHandler* player1_input;
	InputHandler* player2_input;

	// 윈도우 스타일
	int WD_STYLE = (WS_CAPTION |
		WS_SYSMENU);
	// scene 관련 멤버
	vector<Scene*> scene_list; // scene 리스트
	bool is_scene_loaded = false; // scene이 로드 됬나요?
	SCENE_NAME currentScene;
	// 맵
	vector<Map*> map_list; // 지형 리스트

	bool isLoaded = { false };
};