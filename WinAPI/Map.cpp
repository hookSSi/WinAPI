#include "Map.h"
#include "Pixel.h"

Map::Map() : _persistance(0), _octave(0)
{
	maxY_list.reserve(WIDTH);
	_terrain.reserve(WIDTH);

	for (int x = 0; x < WIDTH; x++)
	{
		vector<Pixel*> column;
		for (int y = 0; y < HEIGHT; y++)
		{
			Pixel *pixel = new Pixel(Vector2D(0, 0));
			column.push_back(pixel);
		}
		_terrain.push_back(column);
		maxY_list.push_back(0);
	}
}

bool Map::Initialize()
{
	/* 처음으로 초기화! */
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			_terrain[x][y]->position = Vector2D(0, 0);
			_terrain[x][y]->SetSolid(false);
		}
	}

	srand((unsigned)time(nullptr));

	// 지속성: 진폭이 작아져 가는 정도
	this->_persistance =  rand() % 10 + 3;
	// 노이즈 함수들이 더해지는 정도
	this->_octave =  rand() % 10 + 3;

	float maxY = 0;

	for (int x = 0; x < WIDTH; x++)
	{
		maxY = PerlinNoise::PerlinNoise_1D(x / WIDTH, this->_persistance, this->_octave);
		maxY_list[x] = (int)(350 - maxY);
		for (int y1 = (int)(350 - maxY), y2 = 0; (350 - maxY) + y2 <= HEIGHT; y1++, y2++)
		{
			_terrain[x][y1]->position = Vector2D((float)x, (350 - maxY) + y2);
			_terrain[x][y1]->SetSolid(true);
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
		bool mode = true;

		for (int y = maxY_list[x]; y < HEIGHT; y++)
		{
			if (!_terrain[x][y]->IsSolid())
			{
				mode = false;
				break;
			}
		}

		if (mode) // 중간에 픽셀이 비지 않으면 선으로 처리
		{
			Rectangle(hdc, x, _terrain[x][maxY_list[x]]->position.y, x + 1, HEIGHT);
		}	
		else // 중간에 픽셀이 비면 일일히 처리
		{
			for (int y = maxY_list[x]; y < HEIGHT; y++)
			{
				if (_terrain[x][y]->IsSolid())
				{
					SetPixel(hdc, x, _terrain[x][y]->position.y, WHITE_COLOR);
				}
			}
		}
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
			for (int y = maxY_list[x]; y < HEIGHT; y++)
			{
				if (_terrain[x][y]->IsSolid())
				{
					Vector2D norm = GetNormal(x, _terrain[x][y]->position.y, boxSize) * scale;
					MoveToEx(hdc, x, _terrain[x][y]->position.y, NULL);
					LineTo(hdc, x + norm.x, _terrain[x][y]->position.y + norm.y);
					break;
				}
			}
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
				if (_terrain[x + w][y + h]->IsSolid())
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