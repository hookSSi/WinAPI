#include "Common.h"
#include "Scene.h"
#include "Tank.h"
#include "TextUI.h"
#include "Map.h"
#include "Game.h"
#include "Physics.h"

void FillSurface(HWND hWnd, HDC hdc, BOOL mode)
{
	RECT crt;

	GetClientRect(hWnd, &crt);

	if (mode)
	{
		FillRect(hdc, &crt, GetSysColorBrush(COLOR_WINDOW));
		for (int i = 0; i<crt.right; i += 10) {
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, crt.bottom);
		}

		for (int i = 0; i<crt.bottom; i += 10) {
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, crt.right, i);
		}
	}
	else
	{
		HBRUSH MyBrush, OldBrush;

		MyBrush = CreateSolidBrush(RGB(0, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

		FillRect(hdc, &crt, MyBrush);

		DeleteObject(MyBrush);
	}
}

Scene* CreateScene1(Scene_Builder& builder)
{
	builder.CreateNewProduct();

	// 제목
	TextUI* subject = new TextUI(L"탱크 게임");
	subject->position = Vector2D(WIDTH/2, HEIGHT/2 - 100);
	// 메뉴 텍스트 UI
	SpecialTextUI* menu_ui = new SpecialTextUI(L"Press Enter to start", 0.3);
	menu_ui->position = Vector2D(WIDTH / 2, HEIGHT / 2);

	builder.AddGameObject(subject);
	builder.AddGameObject(menu_ui);

	return builder.GetProduct();
}

Scene* CreateScene2(Scene_Builder& builder)
{
	builder.CreateNewProduct();

	// 스코어 제목 관련 변수
	int subjectGap = 100; // 수평
	int subjectGap2 = 15;// 수직
	// 스코어 관련 변수
	int scoreGap = 105;
	int scoreGap2 = 40;


	// 플레이어 1 스코어 UI
	TextUI* scoreSubject1 = new TextUI(L"플레이어1 점수");
	scoreSubject1->position = Vector2D(subjectGap, subjectGap2);
	TextUI* score1 = new TextUI(L"0");
	score1->position = Vector2D(scoreGap, scoreGap2);


	// 플레이어 2 스코어 UI
	TextUI* scoreSubject2 = new TextUI(L"플레이어2 점수");
	scoreSubject2->position = Vector2D((int)(WIDTH - subjectGap), subjectGap2);
	TextUI* score2 = new TextUI(L"0");
	score2->position = Vector2D((int)(WIDTH - scoreGap), scoreGap2);

	// 플레이어 1 탱크
	Tank* player1_tank = new Tank();
	player1_tank->position = Vector2D(100, 100);
	player1_tank->SetSize(Vector2D(12, 2));

	// 플레이어 2 탱크
	Tank* player2_tank = new Tank();
	player2_tank->position = Vector2D((int)(WIDTH - 100), 100);
	player2_tank->SetSize(Vector2D(12, 2));

	Physics::GetInstance()->player1_tank = player1_tank;
	Physics::GetInstance()->player2_tank = player2_tank;
	Game::GetInstance()->player1_tank = player1_tank;
	Game::GetInstance()->player2_tank = player2_tank;

	builder.AddGameObject(scoreSubject1);
	builder.AddGameObject(score1);
	builder.AddGameObject(scoreSubject2);
	builder.AddGameObject(score2);
	builder.AddGameObject(player1_tank);
	builder.AddGameObject(player2_tank);

	Game::GetInstance()->player1_scoreUI = score1;
	Game::GetInstance()->player2_scoreUI = score2;

	return builder.GetProduct();
}

Tank* CreateTank(TankBuilder& builder)
{
	builder.CreateNewProduct();

	return builder.GetProduct();
}

// 선형 보간
float PerlinNoise::Linear_Interpolate(float a, float b, float x)
{
	return a*(1 - x) + b*x;
}

// 코사인 보간
float Cos_Interpolate(float a, float b, float x)
{
	float ft = x * PI;
	float f = (1 - cos(ft)) * 0.5f;

	return a*(1 - f) + b*f;
}

// 노이즈 함수
float PerlinNoise::Noise1(int x)
{
	x = (x << 13) ^ x;
	return (1.0f - ((x*(x*x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float PerlinNoise::SmoothedNoise_1(float x)
{
	return Noise1(x) / 2 + Noise1(x - 1) / 4 + Noise1(x + 1) / 4;
}

float PerlinNoise::InterpolatedNoise_1(float x)
{
	int integer_X = int(x);
	float fractional_X = x - integer_X;

	float v1 = SmoothedNoise_1(integer_X);
	float v2 = SmoothedNoise_1(integer_X + 1);

	return Cos_Interpolate(v1, v2, fractional_X);
}


float PerlinNoise::PerlinNoise_1D(float x, float persistance, int octave)
{
	float total = 0;
	float p = persistance;
	int n = octave;

	for (int i = 0; i <= n; i++)
	{
		float frequency = 2 * i;
		float amplitude = p * i;

		total = total + InterpolatedNoise_1(x * frequency) * amplitude;
	}

	return total;
}

const Vector2D& Raycast(int startX, int startY, int lastX, int lastY)
{
	Map *terrain = Game::GetInstance()->GetMap();

	int delta_x = abs(startX - lastX);
	int delta_y = abs(startY - lastY);

	int x = startX;
	int y = startY;

	int xinc1, xinc2, yinc1, yinc2;

	if (lastX >= startX)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}
	if (lastY >= startY)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	int den, num, numadd, numpixels;
	if (delta_x >= delta_y)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;
	}

	int prevX = startX;
	int prevY = startY;

	for (int curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		if (!IsValidPos(x, y))
		{
			return Vector2D(-1,-1);
		}

		if (terrain->IsPixelSolid(x, y))
		{
			return Vector2D(x,y);
		}

		prevX = x;
		prevY = y;

		num += numadd;

		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}

		x += xinc2;
		y += yinc2;	
	}

	return Vector2D(-1, -1);
}

bool IsValidPos(int x, int y)
{
	if (x < 0 || y < 0 || x >= WIDTH|| y >= HEIGHT)
		return false;
	else
		return true;
}
bool IsValidPos(Vector2D& pos)
{
	return IsValidPos(pos.x, pos.y);
}