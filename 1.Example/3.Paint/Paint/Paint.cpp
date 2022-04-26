// Paint.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Paint.h"

//�Լ� ���� ���� �κ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ��������
HINSTANCE hInst;                               

HDC memDC;
HBITMAP memBitmap;
POINT stPos;


// WinMain�Լ� �κ�
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    /*������ ���� �� ���� �����츦 �����մϴ�.*/
    HWND hWnd = InitMainWindowSet(hInstance, &WndProc, L"Paint");
    //���������� �����Ǿ��ٸ� �����츦 �����մϴ�.
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
    return (int)msg.wParam;
}

// WndProc �Լ��κ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //������ ���� �޼���
    case WM_CREATE:
    {
        //��ư ����
        CreateButton(L"Pen", 20, 20, 50, 50, (HMENU)1, hWnd, hInst);
        CreateButton(L"Erase", 20, 75, 50, 50, (HMENU)2, hWnd, hInst);
        //��ư ���� �� �̹��� �����
        CreateButtonImg(L"Pen", IDI_ICON2, hWnd, hInst);
        CreateButtonImg(L"Erase", IDI_ICON1, hWnd, hInst);
        //���� ���̺� ����
        CreateRGBTable(L"RGBtable", 80, 30, 150, 120, (HMENU)10, hWnd, hInst);

        //���� ���۸��� ���� �޸� ����
        CreateBackPage(hWnd, hInst, &memDC, &memBitmap);
        break;
    }

    //���� ��� �׸��� Or �����
    case WM_COMMAND:
    {
        //��� ��ư ó���ϱ�
        SetFunction(wParam, lParam, hWnd);
        //���� ��ư�� ���� ���� 
        break;
    }
    //��ũ�� ���
    case WM_HSCROLL:
    {
        SetScrollFunction(wParam, lParam);
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
        break;
    }


        /*���� ���콺 ���ۿ� ���� ��Ʈ��*/
    case WM_MOUSEMOVE:
    {
        if (wParam == MK_LBUTTON && stPos.y >= 150) {
            //�׸��� ���
            if (GetFunction(wParam, lParam, hWnd) == 1)
            {
                stPos = Draw(hWnd, memDC, wParam, lParam, stPos);
                HDC hdc = GetDC(hWnd);
                RECT rect;
                GetClientRect(hWnd, &rect);
                BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
                ReleaseDC(hWnd, hdc);
            }
            //����� ���
            else if (GetFunction(wParam, lParam, hWnd) == 2)
            {
                stPos = Eraser(hWnd, memDC, wParam, lParam, stPos);
                HDC hdc = GetDC(hWnd);
                RECT rect;
                GetClientRect(hWnd, &rect);
                BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
                ReleaseDC(hWnd, hdc);
            }

        }
        break;
    }
    case WM_LBUTTONDOWN:
    {
        //�� Ŭ���� �ʱ� ��ǥ �� ����
        stPos.x = GET_X_LPARAM(lParam);
        stPos.y = GET_Y_LPARAM(lParam);
        break;
    }
    case WM_LBUTTONUP:
    {
        break;
    }
    case WM_RBUTTONDOWN:
    {
        break;
    }
    case WM_RBUTTONUP:
    {
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetColor(hWnd,memDC,memBitmap);
        RECT rect;
        GetClientRect(hWnd, &rect);
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        DeleteObject(memBitmap);
        DeleteDC(memDC);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
