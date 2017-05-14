#pragma once
#include<Windows.h>
#include<iostream>

class Scene;
class Scene_Builder;
class Tank;
class TankBuilder;

// 배경 색 채우기
void FillSurface(HWND hWnd, HDC hdc, BOOL isActive);

// scene 만들기
Scene* CreateScene1(Scene_Builder& builder);
Scene* CreateScene2(Scene_Builder& builder);

// 탱크 만들기
Tank* CreateTank(TankBuilder& builder);

namespace PerlinNoise
{
	// 선형 보간
	float Linear_Interpolate(float a, float b, float x);
	// 노이즈 함수
	float Noise1(int x);

	float SmoothedNoise_1(float x);

	float InterpolatedNoise_1(float x);

	float PerlinNoise_1D(float x, float persistance, int octave);
}