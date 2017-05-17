#pragma once
#include "stdafx.h"
#include "Pixel.h"

class Map
{
public:
	Map();
	~Map(){};

	bool toggle; // ���� ���� ���̱�?

	bool Initialize();
	bool Draw(HWND hWnd, HDC hdc);
	bool Draw_norm(HWND hWnd, HDC hdc, bool toggle);
	bool IsPixelSolid(int x, int y){ return _terrain[x][y].IsSolid(); }
	bool RemoveStaticPixel(int x, int y){ _terrain[x][y].SetSolid(false); return true; }
	bool AddStaticPixel(int x, int y) { _terrain[x][y].SetSolid(true); return true; }

	Vector2D GetNormal(int x, int y, int boxSize);
private:
	using TERRAIN = vector<vector<Pixel>>; 
	// �ȼ� ����Ʈ
	TERRAIN _terrain; 
	vector<int> maxY_list;
	// ���Ӽ�: ������ �۾��� ���� ����
	int _persistance;
	// ������ �Լ����� �������� ����
	int _octave;
};