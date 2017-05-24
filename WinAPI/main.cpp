#include "Game.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCWSTR lpszClass = TEXT("TANK GAME"); // 프로그램 제목

static HBITMAP hBit;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd = Game::GetInstance()->GenerateGameWindow(hInstance, lpszClass, (WNDPROC)WndProc); // 게임 윈도우 생성

	ShowWindow(hWnd, nCmdShow); // 전체화면

	MSG Message;

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	RECT crt; // 스크린 Rect
	HDC hdc, hMemDC;
	HBITMAP OldBit;

	GetClientRect(hWnd, &crt);
	hdc = GetDC(hWnd);

	if (hBit == nullptr)
	{
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillSurface(hWnd, hMemDC, false); // 눈금표시

	Game::GetInstance()->Update(); // 게임 업데이트
	Game::GetInstance()->Draw(hWnd, hMemDC); // 그리기

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc ,hMemDC;
	PAINTSTRUCT ps;
	HBITMAP OldBit;
	RECT crt; // 스크린 Rect

	switch (iMessage) {
	case WM_CREATE:
		Game::GetInstance()->Initilize();
		Game::GetInstance()->Start();
		SetTimer(hWnd, 1, FPS, (TIMERPROC)(TimerProc));
		return 0;
	case WM_KEYDOWN:
		Game::GetInstance()->InputHandle(wParam);
		return 0;
	case WM_LBUTTONDOWN:
		Game::GetInstance()->CreateBullet(lParam,1);
		return 0;
	case WM_RBUTTONDOWN:
		Game::GetInstance()->CreateBullet(lParam, 2);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &crt);
		hMemDC = CreateCompatibleDC(hdc);
		OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, OldBit);
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}