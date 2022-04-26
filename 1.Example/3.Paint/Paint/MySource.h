#pragma once

#include <Windowsx.h>
#include "framework.h"
#include "Paint.h"


//�ʱ� ���� ���� �Լ�
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc,const WCHAR* name);

//��ư ���� �Լ�
void CreateButton(const WCHAR* name, LONG x, LONG y, LONG width, LONG height, HMENU id, HWND hWnd, HINSTANCE hInst);
void CreateButtonImg(const WCHAR* buttonName, int imgName, HWND hWnd, HINSTANCE hInst);
//���� ���� �Լ�
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst);
void SetColor(HWND hWnd, HDC hdc, HBITMAP memBitmap);

//������۸� �ʱ� ���� �Լ�
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC, HBITMAP* memBitmap);

// �׸��� or ����� ��ư ��� �Լ�
void SetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd);
void SetScrollFunction(WPARAM wParam, LPARAM lParam);

// �׸��� or ����� ���
POINT Draw(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam,  POINT stPos);
POINT Eraser(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos);


