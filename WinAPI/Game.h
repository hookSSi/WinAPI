#pragma once
#include "stdafx.h"
#include "Singleton.h"

/* 전방 선언 */
class Scene;
class Map;

class Game : public Singleton < Game >
{
public:
	Game(){};
	virtual ~Game(){}

	HWND Game::GenerateGameWindow(HINSTANCE hInstance, LPCWSTR lpszClass, WNDPROC WndProc);
	bool Initilize(); // 초기화
	bool Start();
	bool Draw(HWND hWnd, HDC hdc); // 그리기 작업
	bool Update(); // 업데이트
	bool ExitGame(); // 게임 종료 = 프로그램 종료

	bool SetScene(int number); // 불러올 Scene 인덱스 설정
	bool LoadScene(); // Scene 불러오기

	bool InputHandle(WPARAM wParam); // 입력 받기

	const int GetWD_STYLE(){ return this->WD_STYLE; }
	bool SetWD_STYLE(const int style){ this->WD_STYLE = style; }
private:
	// 윈도우 스타일
	int WD_STYLE = (WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME);
	// scene 관련 멤버
	vector<Scene*> scene_list; // scene 리스트
	bool is_scene_loaded = false; // scene이 로드 됬나요?
	int currentScene;
	// 맵
	vector<Map*> map_list; // 지형 리스트
};