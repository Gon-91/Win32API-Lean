

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "resource.h"


HINSTANCE hInst;
HWND heditR, heditG, heditB;
int R, G, B;

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
    wcex.lpszClassName = L"ColorTable";
    wcex.hIconSm = NULL;
    RegisterClassExW(&wcex);
    //������ ������ ���� �� ������Ʈ
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
    HWND hWnd = CreateWindowW(L"ColorTable", L"ColorTable", WS_OVERLAPPEDWINDOW,
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
    WCHAR editword[10];
    switch (message)
    {
    case WM_CREATE:
        heditR = CreateWindowW(L"edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER, 30, 40, 50, 25, hWnd, (HMENU)1, hInst, NULL);
        heditG = CreateWindowW(L"edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER, 30, 70, 50, 25, hWnd, (HMENU)2, hInst, NULL);
        heditB = CreateWindowW(L"edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER, 30, 100, 50, 25, hWnd, (HMENU)3, hInst, NULL);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);

            //RGB ǥ�ø� �ϱ� ���� �ؽ�Ʈ
            TextOutW(hdc, 10, 45, L"R", 1);
            TextOutW(hdc, 10, 75, L"G", 1);
            TextOutW(hdc, 10, 105, L"B", 1);

            //����� �� ǥ�ø� �ϱ� ���� �ؽ�Ʈ
            wsprintf(editword, L"R : %d", R);
            TextOutW(hdc, 100, 45, editword, lstrlenW(editword));
            wsprintf(editword, L"G : %d", G);
            TextOutW(hdc, 100, 75, editword, lstrlenW(editword));
            wsprintf(editword, L"B : %d", B);
            TextOutW(hdc, 100, 105, editword, lstrlenW(editword));

            //�� ĥ�ϱ�
            HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
            HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, newBrush);
            Rectangle(hdc, 200, 50, 500, 400);
            SelectObject(hdc,OldBrush);
            DeleteObject(newBrush);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_COMMAND:

        switch (HIWORD(wParam))
        {
        case EN_CHANGE:

            //R ó��
            if (LOWORD(wParam) == 1) {

                int num = 0;
                if (GetWindowTextW(heditR, editword, GetWindowTextLengthW(heditR) + 1) != NULL) {
                    num = _wtoi(editword);
                }

                if (0 <= num && num <= 255) {
                    R = num;
                }
                else {
                    MessageBox(hWnd, L"0 ~ 255�� ���ڸ� �Է��� �� �ֽ��ϴ�.", L"���", NULL);
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }

            //G ó��
            if (LOWORD(wParam) == 2) {
                GetWindowTextW(heditG, editword, GetWindowTextLengthW(heditG) + 1);
                int num = _wtoi(editword);

                if (0 <= num && num <= 255) {
                    G = num;
                }
                else {
                    MessageBox(hWnd, L"0 ~ 255�� ���ڸ� �Է��� �� �ֽ��ϴ�.", L"���", NULL);
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }

            //B ó��
            if (LOWORD(wParam) == 3) {
                GetWindowTextW(heditB, editword, GetWindowTextLengthW(heditB) + 1);
                int num = _wtoi(editword);

                if (0 <= num && num <= 255) {
                    B = num;
                }
                else {
                    MessageBox(hWnd, L"0 ~ 255�� ���ڸ� �Է��� �� �ֽ��ϴ�.", L"���", NULL);
                }
                InvalidateRect(hWnd, NULL, TRUE);
            }

            break;
        }
        break;
    case WM_SETTEXT:

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

