#pragma once
#include "stdafx.h"
#include "Pixel.h"

class Map
{
public:
	Map();
	~Map(){};

	bool toggle; // 법선 벡터 보이기?

	bool Initialize();
	bool Draw(HWND hWnd, HDC hdc);
	bool Draw_norm(HWND hWnd, HDC hdc, bool toggle);
	bool IsPixelSolid(int x, int y){ return this->_terrain[x][y]->IsSolid(); }
	bool RemoveStaticPixel(int x, int y){ _terrain[x][y]->SetSolid(false); return true; }
	bool AddStaticPixel(int x, int y) { _terrain[x][y]->SetSolid(true); return true; }

	Vector2D GetNormal(int x, int y, int boxSize);
private:
	using TERRAIN = vector<vector<Pixel*>>; 
	// 픽셀 리스트
	TERRAIN _terrain; 
	vector<int> maxY_list;
	// 지속성: 진폭이 작아져 가는 정도
	int _persistance;
	// 노이즈 함수들이 더해지는 정도
	int _octave;
};