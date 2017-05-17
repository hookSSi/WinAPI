#pragma once
#include<Windows.h>
#include<iostream>
#include "Vector2D.h"

// ���漱��
class Scene;
class Scene_Builder;
class Tank;
class TankBuilder;
class Map;

// ��� �� ä���
void FillSurface(HWND hWnd, HDC hdc, BOOL isActive);

// scene �����
Scene* CreateScene1(Scene_Builder& builder);
Scene* CreateScene2(Scene_Builder& builder);

// ��ũ �����
Tank* CreateTank(TankBuilder& builder);

namespace PerlinNoise
{
	// ���� ����
	float Linear_Interpolate(float a, float b, float x);
	// ������ �Լ�
	float Noise1(int x);

	float SmoothedNoise_1(float x);

	float InterpolatedNoise_1(float x);
	// 1���� �޸� ������
	float PerlinNoise_1D(float x, float persistance, int octave);
}

// �浹 ó��
bool Raycast(Map& terrain, int startX, int startY, int lastX, int lastY);

bool IsValidPos(int x, int y);
bool IsValidPos(Vector2D& pos);