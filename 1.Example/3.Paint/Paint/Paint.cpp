// Paint.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Paint.h"

//함수 원형 선언 부분
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 전역변수
HINSTANCE hInst;                               

HDC memDC;
HBITMAP memBitmap;
POINT stPos;


// WinMain함수 부분
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    /*윈도우 설정 및 메인 윈도우를 생성합니다.*/
    HWND hWnd = InitMainWindowSet(hInstance, &WndProc, L"Paint");
    //정상적으로 생성되었다면 윈도우를 갱신합니다.
    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// WndProc 함수부분
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //윈도우 생성 메세지
    case WM_CREATE:
    {
        //버튼 생성
        CreateButton(L"Pen", 20, 20, 50, 50, (HMENU)1, hWnd, hInst);
        CreateButton(L"Erase", 20, 75, 50, 50, (HMENU)2, hWnd, hInst);
        //버튼 생성 및 이미지 씌우기
        CreateButtonImg(L"Pen", IDI_ICON2, hWnd, hInst);
        CreateButtonImg(L"Erase", IDI_ICON1, hWnd, hInst);
        //색상 테이블 생성
        CreateRGBTable(L"RGBtable", 80, 30, 150, 120, (HMENU)10, hWnd, hInst);

        //더블 버퍼링을 위한 메모리 셋팅
        CreateBackPage(hWnd, hInst, &memDC, &memBitmap);
        break;
    }

    //메인 기능 그리기 Or 지우기
    case WM_COMMAND:
    {
        //토글 버튼 처리하기
        SetFunction(wParam, lParam, hWnd);
        //각종 버튼에 따른 동작 
        break;
    }
    //스크롤 기능
    case WM_HSCROLL:
    {
        SetScrollFunction(wParam, lParam);
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
        break;
    }


        /*각종 마우스 동작에 따른 컨트롤*/
    case WM_MOUSEMOVE:
    {
        if (wParam == MK_LBUTTON && stPos.y >= 150) {
            //그리기 모드
            if (GetFunction(wParam, lParam, hWnd) == 1)
            {
                stPos = Draw(hWnd, memDC, wParam, lParam, stPos);
                HDC hdc = GetDC(hWnd);
                RECT rect;
                GetClientRect(hWnd, &rect);
                BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
                ReleaseDC(hWnd, hdc);
            }
            //지우기 모드
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
        //좌 클릭시 초기 좌표 값 저장
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
