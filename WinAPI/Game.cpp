#include "Game.h"
#include "TextUI.h"
#include "Scene.h"
#include "Map.h"
#include "Bullet.h"
#include "Physics.h"
#include "ObjectPool.h"
#include "ParticleManager.h"
#include "InputHandler.h"
#include "TankCommand.h"
#include "EventManager.h"

HINSTANCE g_hInst;

Game::Game()
{
}

Game::~Game()
{
	for (auto iter = scene_list.begin(); iter != scene_list.end(); iter++)
	{
		if ((*iter) != nullptr)
		{
			(*iter)->DeleteAllGameObject();
			delete (*iter);
		}
	}
	delete player1_input;
	delete player2_input;
	delete eventManager;
}

bool Game::Initilize()
{
	is_scene_loaded = false ; // scene이 로드 됬나요?
	isLoaded = false ;

	currentScene = SCENE_NAME::MAIN;
	eventManager = new EventManager();

	Physics::GetInstance();

	Scene_Builder builder;

	scene_list.push_back(new Scene());
	scene_list.push_back(new Scene());

	scene_list.reserve(2);

	Map *map1 = new Map();
	Map *map2 = new Map();

	if (map1->Initialize())
	{
		map_list.push_back(map1);
	}

	if (map2->Initialize())
	{
		map_list.push_back(map2);
	}

	map_list.reserve(2);

	this->SetScene(SCENE_NAME::MENU);

	ObjectPool::GetInstance();

	float speed = 40;
	float degreeScale = 2;

	player1_input = new InputHandler();
	player1_input->SetButtonA(new MoveCommand(Vector2D(-speed, 0.0f)));
	player1_input->SetButtonD(new MoveCommand(Vector2D(speed, 0.0f)));
	player1_input->SetButtonW(new FireDegreeCommand(degreeScale));
	player1_input->SetButtonS(new FireDegreeCommand(-degreeScale));
	player1_input->SetButtonCtrl(new JumpCommand(300));
	player1_input->SetButtonShift(new FireCommand(1));

	player2_input = new InputHandler2();
	player2_input->SetButtonA(new MoveCommand(Vector2D(-speed, 0.0f)));
	player2_input->SetButtonD(new MoveCommand(Vector2D(speed, 0.0f)));
	player2_input->SetButtonW(new FireDegreeCommand(degreeScale));
	player2_input->SetButtonS(new FireDegreeCommand(-degreeScale));
	player2_input->SetButtonCtrl(new JumpCommand(300));
	player2_input->SetButtonShift(new FireCommand(2));

	this->isLoaded = true;

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
	this->LoadScene(); // 여기서 문제발생인듯
	return true;
}

bool Game::Update()
{
	if (is_scene_loaded && this->isLoaded)
	{
		if (scene_list.size() > (int)currentScene)
		{
			scene_list[(int)currentScene]->Update(); // Update
			Physics::GetInstance()->Update(); // FixedUpdate
			ParticleManager::GetInstance()->Update();
			
			if (currentScene == SCENE_NAME::MAIN) // 본 게임의 시작
			{
				player1_scoreUI->SetText(player1_score);
				player2_scoreUI->SetText(player2_score);

				if (eventManager->flag)
				{
					eventManager->flag = false;
					Game::GetInstance()->LoadNewGame();
				}	
			}

			return true;
		}
	}
}

bool Game::Draw(HWND hWnd, HDC hdc)
{
	if (is_scene_loaded && this->isLoaded)
	{
		if (scene_list.size() > (int)currentScene)
		{
			scene_list[(int)currentScene]->Draw(hWnd, hdc);
			ParticleManager::GetInstance()->Draw(hWnd,hdc);
			map_list[(int)currentScene]->Draw(hWnd,hdc);
			return true;
		}
	}
}

bool Game::ExitGame()
{
	ObjectPool::GetInstance()->FreeAllObject();
	return true;
}

bool Game::SetScene(SCENE_NAME scene_name)
{
	if (scene_list.size() > (int)scene_name)
	{
		scene_list[(int)currentScene]->DeleteAllGameObject();
		delete scene_list[(int)currentScene];
		this->currentScene = scene_name;
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
	case SCENE_NAME::MENU:
		scene_list[(int)currentScene] = CreateScene1(builder);
		break;
	case SCENE_NAME::MAIN:
		scene_list[(int)currentScene] = CreateScene2(builder);
		break;
	}

	is_scene_loaded = true;

	return true;
}

bool Game::InputHandle(WPARAM wParam)
{
	if (this->isLoaded)
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_RETURN:
			player1_score = 0;
			player2_score = 0;
			LoadNewGame();
			break;
		default:
			if (currentScene == SCENE_NAME::MAIN)
			{
				Command *command = (player1_input->InputHandle(wParam));

				if (command != nullptr)
					command->execute(*player1_tank);

				Command *command2 = (player2_input->InputHandle(wParam));

				if (command2 != nullptr)
					command2->execute(*player2_tank);
			}
			break;
		}
	}
	
	return true;
}
void Game::LoadNewGame()
{
	this->SetScene(SCENE_NAME::MAIN);
	LoadScene();
	map_list[(int)currentScene]->Initialize();
}

void Game::AddGameObjet(Object* object)
{ 
	scene_list[(int)currentScene]->AddGameObject(object);
	Physics::GetInstance()->AddObject(object);
}

void Game::CreateBullet(LPARAM lParam, int p_master)
{
	if (this->isLoaded && currentScene == SCENE_NAME::MENU)
	{
		Bullet *bullet = (Bullet*)ObjectPool::GetInstance()->GetGameObject(OBJECT_TYPE::BULLET);

		bullet->SetPosition(Vector2D(LOWORD(lParam), HIWORD(lParam)));
		bullet->SetSize(Vector2D(3, 3));
		bullet->velocity = Vector2D(0, 10);
		bullet->master = p_master;
		bullet->Init();

		scene_list[(int)currentScene]->AddGameObject(bullet);
		Physics::GetInstance()->AddObject(bullet);
	}
}