#include "Map.h"
#include "Pixel.h"

Map::Map()
{
	for (int x = 0; x < WIDTH; x++)
	{
		vector<Pixel> column;
		for (int y = 0; y < HEIGHT; y++)
		{
			Pixel pixel;
			pixel.position = Vector2D(0,0);
			pixel.SetSolid(false);
			column.push_back(pixel);
		}
		_terrain.push_back(column);
	}
}

bool Map::Initialize()
{
	srand((unsigned)time(nullptr));

	// 지속성: 진폭이 작아져 가는 정도
	this->_persistance =  rand() % 10 + 3;
	// 노이즈 함수들이 더해지는 정도
	this->_octave =  rand() % 10 + 3;

	float maxY = 0;

	for (int x = 0; x < WIDTH; x++)
	{
		maxY = PerlinNoise::PerlinNoise_1D(x / WIDTH, this->_persistance, this->_octave);
		for (int y1 = 0, y2 = 0; (350 - maxY) - y2 > 0; y1++, y2++)
		{
			_terrain[x][y1].position = Vector2D((float)x, (350-maxY) - y2);
			_terrain[x][y1].SetSolid(true);
		}
	}

	return true;
}

bool Map::Draw(HWND hWnd, HDC hdc)
{
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyPen = CreatePen(PS_SOLID, 1, WHITE_COLOR);
	OldPen = (HPEN)SelectObject(hdc, MyPen);

	MyBrush = (HBRUSH)CreateSolidBrush(WHITE_COLOR);
	OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	for (int x = 0; x < WIDTH; x++)
	{
		Rectangle(hdc, x, _terrain[x][0].position.y, x + 1, HEIGHT);
	}

	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);
	SelectObject(hdc, OldBrush);
	DeleteObject(MyBrush);

	Draw_norm(hWnd, hdc, this->toggle);

	return true;
}

bool Map::Draw_norm(HWND hWnd, HDC hdc, bool toggle)
{
	if (toggle)
	{
		return false;
	}
	else
	{

		HPEN MyPen, OldPen;

		MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		int boxSize = 3;
		float scale = 10;

		for (int x = 0; x < WIDTH; x += boxSize)
		{
			Vector2D norm = GetNormal(x, _terrain[x][0].position.y, boxSize) * scale;
			MoveToEx(hdc, x, _terrain[x][0].position.y, NULL);
			LineTo(hdc, x - norm.x, _terrain[x][0].position.y - norm.y);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);

		return true;
	}
}

Vector2D Map::GetNormal(int x, int y, int boxSize)
{
	Vector2D avg;
	for (int w = -boxSize; w <= boxSize; w++)
	{
		for (int h = -boxSize; h <= boxSize; h++)
		{
			if ((x + w) >= WIDTH || (y + h) >= HEIGHT || (x + w) < 0 || (y + h) < 0)
			{
				continue;
			}
			else
			{
				if (_terrain[x + w][y + h].IsSolid())
				{
					avg = avg - Vector2D(w, h);
				}
			}
		}
	}
	float length = avg.Magnitude();

	if (length == 0)
	{
		return Vector2D(0, 0);
	}
	else
	{
		return avg / length;
	}
}