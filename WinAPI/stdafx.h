#pragma once

// C++ �⺻ ��� ����
#include<Windows.h>
#include<iostream>

// �ð�
#include<chrono>

// ���ڿ�
#include<string>

// STL �����̳�
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<stack>

// ����
#include<math.h>

#include "Common.h" // ���� �������� ���� ����

#include "Vector2D.h"

using namespace std;

const float FPS = 30; // FPS ���ڰ� �������� �� ���� �������� �׸���.

const float WIDTH = 640;
const float HEIGHT = 480;

const float PI = 3.1415927f; // ����!

#define WHITE_COLOR RGB(255, 255, 255)
#define BLACK_COLOR RGB(0,0,0)
#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(0,255,0)
#define BLUE_COLOR RGB(0,0,255)

enum class OBJECT_TYPE
{
	OBJECT = 1,
	BULLET = 2,
	DYNAMIC_PIXEL = 3
};