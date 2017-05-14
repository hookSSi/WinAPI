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
	Vector2D GetNormal(int x, int y, int boxSize);
private:
	using TERRAIN = vector<vector<Pixel>>; 
	// �ȼ� ����Ʈ
	TERRAIN _terrain; 
	// ���Ӽ�: ������ �۾��� ���� ����
	int _persistance;
	// ������ �Լ����� �������� ����
	int _octave;
};