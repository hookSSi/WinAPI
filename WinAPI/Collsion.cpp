#include "Collision.h"

// �浹 ó�� ������Ʈ
bool Collision::Update()
{
	if (isActive)
	{

		return true; // ������Ʈ�� Active �Ǿ� �־� Update�� �����
	}
	return false; // ������Ʈ�� Active �Ǿ� ���� ����
}

bool Collision::Draw(HWND hWnd, HDC hdc)
{

	return true;
}