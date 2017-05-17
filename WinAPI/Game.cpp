#include "Game.h"
#include "stdafx.h"
#include "TextUI.h"
#include "Scene.h"
#include "Map.h"
#include "Bullet.h"
#include "Physics.h"

HINSTANCE g_hInst;

void CreateDynamicPixel(int x, int y)
{
	
}

bool Game::Initilize()
{
	scene_list.reserve(2);

	Scene_Builder builder;

	scene_list.push_back(CreateScene1(builder));
	scene_list.push_back(CreateScene2(builder));

	Map *map1 = new Map();
	if (map1->Initialize())
	{
		map_list.push_back(map1);
	}
	return true;
}

HWND Game::GenerateGameWindow(HINSTANCE hInstance, LPCWSTR lpszClass, WNDPROC WndProc)
{
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	return CreateWindow(lpszClass, lpszClass, this->WD_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
}

bool Game::Start()
{
	this->SetScene(0);
	this->LoadScene();
	return true;
}

bool Game::Update()
{
	if (is_scene_loaded)
	{
		if (scene_list.size() > currentScene)
		{
			scene_list[currentScene]->Update(); // Update
			Physics::GetInstance()->Update(); // FixedUpdate
			return true;
		}
	}
}

bool Game::Draw(HWND hWnd, HDC hdc)
{
	if (is_scene_loaded)
	{
		if (scene_list.size() > currentScene)
		{
			scene_list[currentScene]->Draw(hWnd, hdc);
			
			map_list[currentScene]->Draw(hWnd,hdc);
			return true;
		}
	}
}

bool Game::ExitGame()
{
	return true;
}

bool Game::SetScene(int number)
{
	if (scene_list.size() > number)
	{
		scene_list[currentScene]->DeleteAllGameObject();
		this->currentScene = number;
		is_scene_loaded = false;
		return true;
	}
	else
	{
		_ASSERTE(!"scene의 index가 너무 큰걸로 할려고 하고있습니다");
		exit(0);
		return false;
	}
}

bool Game::LoadScene()
{
	Scene_Builder builder;

	switch (this->currentScene)
	{
	case 0:
		scene_list[currentScene] = CreateScene1(builder);
		break;
	case 1:
		scene_list[currentScene] = CreateScene2(builder);
		break;
	}

	is_scene_loaded = true;
	return true;
}

bool Game::InputHandle(WPARAM wParam)
{
	switch (wParam)
	{
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	case WM_LBUTTONDOWN:
		break;
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	default:
		return false;
		break;
	}

	return true;
}

void Game::CreateBullet(LPARAM lParam)
{
	Bullet *bullet = new Bullet();

	bullet->SetPosition(Vector2D(LOWORD(lParam), HIWORD(lParam)));
	bullet->SetSize(Vector2D(3, 3));
	bullet->velocity = Vector2D(0, 30);

	Physics::GetInstance()->AddObject(bullet);
	int count = bullet->counter;

	string str = "Bullet";

	bool success = scene_list[currentScene]->AddGameObject(str, bullet);
	
}