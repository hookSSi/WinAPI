#include "Collision.h"

// 충돌 처리 업데이트
bool Collision::Update()
{
	if (isActive)
	{

		return true; // 컴포넌트가 Active 되어 있어 Update가 실행됨
	}
	return false; // 컴포넌트가 Active 되어 있지 않음
}

bool Collision::Draw(HWND hWnd, HDC hdc)
{

	return true;
}