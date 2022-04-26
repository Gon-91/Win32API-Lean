#pragma once

#include <Windowsx.h>
#include "framework.h"
#include "Paint.h"


//초기 구조 적용 함수
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc,const WCHAR* name);

//버튼 생성 함수
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst);
void CreateButtonImg(const WCHAR* buttonName, int imgName, HWND hWnd, HINSTANCE hInst);
//색상 선택 함수
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst);
void SetColor(HWND hWnd, HDC hdc, HBITMAP memBitmap);

//더블버퍼링 초기 셋팅 함수
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);

// 그리기 or 지우기 버튼 토글 함수
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);
void SetScrollFunction(WPARAM wParam, LPARAM lParam);

// 그리기 or 지우기 기능
POINT Draw(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam,  POINT stPos);
POINT Eraser(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos);


