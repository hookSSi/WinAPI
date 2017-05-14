#include "Common.h"
#include "Scene.h"
#include "Tank.h"
#include "TextUI.h"

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

	// ����
	TextUI* subject = new TextUI(L"��ũ ����");
	subject->position = Vector2D(WIDTH/2, HEIGHT/2 - 100);
	// �޴� �ؽ�Ʈ UI
	SpecialTextUI* menu_ui = new SpecialTextUI(L"Press Enter to start", 0.3);
	menu_ui->position = Vector2D(WIDTH / 2, HEIGHT / 2);

	builder.AddGameObject(string("����"), subject);
	builder.AddGameObject(string("Press Enter"), menu_ui);

	return builder.GetProduct();
}

Scene* CreateScene2(Scene_Builder& builder)
{
	builder.CreateNewProduct();

	// ����
	TextUI* subject = new TextUI(L"��ũ ����");
	subject->position = Vector2D(200, 60);
	// �޴� �ؽ�Ʈ UI
	SpecialTextUI* menu_ui = new SpecialTextUI(L"Press Enter to start");
	menu_ui->position = Vector2D(200, 100);

	builder.AddGameObject(string("����"), subject);
	builder.AddGameObject(string("Press Enter"), menu_ui);

	return builder.GetProduct();
}

Tank* CreateTank(TankBuilder& builder)
{
	builder.CreateNewProduct();

	return builder.GetProduct();
}

// ���� ����
float PerlinNoise::Linear_Interpolate(float a, float b, float x)
{
	return a*(1 - x) + b*x;
}

// �ڻ��� ����
float Cos_Interpolate(float a, float b, float x)
{
	float ft = x * PI;
	float f = (1 - cos(ft)) * 0.5f;

	return a*(1 - f) + b*f;
}

// ������ �Լ�
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