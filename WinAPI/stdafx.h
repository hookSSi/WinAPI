#pragma once

// C++ 기본 헤더 파일
#include<Windows.h>
#include<iostream>

// 시간
#include<chrono>

// 문자열
#include<string>

// STL 컨테이너
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<stack>

// 수학
#include<math.h>

#include "Common.h" // 게임 공통으로 쓰는 선언

#include "Vector2D.h"

using namespace std;

const float FPS = 30; // FPS 숫자가 작을수록 더 많이 프레임을 그린다.

const float WIDTH = 640;
const float HEIGHT = 480;

const float PI = 3.1415927f; // 파이!

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