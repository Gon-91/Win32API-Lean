

#include <windows.h>
#include <windowsx.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "resource.h"


HINSTANCE hInst;
int x, y;
WCHAR text[100];
// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //������ â ����ü ���� �� ����
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    wcex.lpszClassName = L"MousePosition";
    wcex.hIconSm = NULL;
    RegisterClassExW(&wcex);
    //������ ������ ���� �� ������Ʈ
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
    HWND hWnd = CreateWindowW(L"MousePosition", L"MousePosition", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    switch (message)
    {
    
    case WM_PAINT:
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            TextOutW(hdc, x + 10, y + 10, text, lstrlen(text));
            EndPaint(hWnd, &ps);
        break;
    case WM_MOUSEMOVE:
        x = GET_X_LPARAM(lParam);
        y = GET_Y_LPARAM(lParam);
        wsprintf(text, L" x : %d \t y : %d", x,y);
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

