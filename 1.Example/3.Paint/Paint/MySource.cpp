#include "MySource.h"

//������ â ����
HWND InitMainWindowSet(HINSTANCE hInstance, WNDPROC WndProc,const WCHAR* name)
{
    //������ â ����ü ���� �� �����ϱ�
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
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = name;
    wcex.hIconSm = NULL;
    RegisterClassExW(&wcex);

    //�ش� ������ â�� ������ͼ� ������ â �����ϱ�
    return CreateWindowW(name, name, WS_MAXIMIZE| WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        100, 100, 750, 750, nullptr, nullptr, hInstance, nullptr);
}

//��ư�����ϱ� 
void CreateButton(const WCHAR* name,LONG x,LONG y,LONG width ,LONG height, HMENU id, HWND hWnd, HINSTANCE hInst)
{
    CreateWindowW(L"button", name, WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BS_PUSHLIKE | BS_ICON, x,y,width,height, hWnd, id, hInst,NULL);
}

void CreateButtonImg(const WCHAR* buttonName,int imgName, HWND hWnd, HINSTANCE hInst)
{
    HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(imgName));
    SendMessageW(FindWindowExW(hWnd, NULL, L"button", buttonName), BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);

}
//���� ���� ���� �����
void CreateRGBTable(const WCHAR* name, LONG left, LONG top, LONG right, LONG bottom, HMENU id, HWND hWnd, HINSTANCE hInst)
{
    
    //RGB�� ��ũ�� �� ���� �� ���� ����
    CreateWindowW(L"scrollbar", L"R", WS_CHILD | WS_VISIBLE | SBS_HORZ, right+20, top+15, right + 30, 15, hWnd, id, hInst, NULL);
    SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL, 0, 255, TRUE);
    CreateWindowW(L"scrollbar", L"G", WS_CHILD | WS_VISIBLE | SBS_HORZ, right+20, top+40, right + 30, 15, hWnd, id+1, hInst, NULL);
    SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL, 0, 255, TRUE);
    CreateWindowW(L"scrollbar", L"B", WS_CHILD | WS_VISIBLE | SBS_HORZ, right+20, top+65, right + 30, 15, hWnd, id+2, hInst, NULL);
    SetScrollRange(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL, 0, 255, TRUE);
    //SetColor(hWnd);
}

//�޸� DC �� ��Ʈ�ʿ� �޸� �Ҵ� �ϱ�
void CreateBackPage(HWND hWnd, HINSTANCE hInst, HDC* memDC , HBITMAP* memBitmap)
{
    HDC hdc = GetDC(hWnd);
    *memDC = CreateCompatibleDC(hdc);
    RECT rect;
    GetClientRect(hWnd, &rect);
    *memBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    (HBITMAP)SelectObject(*memDC, *memBitmap);
    FillRect(*memDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
    ReleaseDC(hWnd, hdc);
}

//���� ����
void SetColor(HWND hWnd,HDC memdc,HBITMAP memBitmap)
{
    //��ũ�� Bar�� �� �޾ƿ���
    int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
    int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
    int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

    HBRUSH newBrush = CreateSolidBrush(RGB(R, G, B));
    HBRUSH OldBrush = (HBRUSH)SelectObject(memdc, newBrush);

    //���õ� ���� �����ֱ�
    Rectangle(memdc, 80, 30, 150, 120);


    //��ũ�� Bar�� �� ǥ�����ֱ�
    WCHAR text[20];
    wsprintf(text, L"R : %d    ", R );
    TextOutW(memdc, 360, 40, text, lstrlenW(text));
    wsprintf(text, L"G : %d     ", G );
    TextOutW(memdc, 360, 70, text, lstrlenW(text));
    wsprintf(text, L"B : %d     ", B );
    TextOutW(memdc, 360, 100, text, lstrlenW(text));


    SelectObject(memdc, OldBrush);
    DeleteObject(newBrush);

}
//�׸���
POINT Draw(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam,POINT stPos) 
{

    //��ũ�� Bar�� �� �޾ƿ���
    int R = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"R"), SB_CTL);
    int G = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"G"), SB_CTL);
    int B = GetScrollPos(FindWindowExW(hWnd, NULL, L"scrollbar", L"B"), SB_CTL);

    HPEN newPen = CreatePen(PS_SOLID, 10, RGB(R, G, B));
    HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

    POINT pos;
    pos.x = GET_X_LPARAM(lParam);
    pos.y = GET_Y_LPARAM(lParam);

    MoveToEx(hdc, stPos.x, stPos.y, NULL);
    LineTo(hdc, pos.x, pos.y);
    SelectObject(hdc, oldPen);
    DeleteObject(newPen);

    stPos.x = pos.x;
    stPos.y = pos.y;
    return stPos;
}
//�����
POINT Eraser(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, POINT stPos)
{
    HPEN newPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
    HPEN oldPen = (HPEN)SelectObject(hdc, newPen);

    POINT pos;
    pos.x = GET_X_LPARAM(lParam);
    pos.y = GET_Y_LPARAM(lParam);

    MoveToEx(hdc, stPos.x, stPos.y, NULL);
    LineTo(hdc, pos.x, pos.y);
    SelectObject(hdc, oldPen);
    DeleteObject(newPen);

    stPos.x = pos.x;
    stPos.y = pos.y;
    return stPos;
}

//�̹��� �����
//������۸�
//������
//��ư ����

//��� �� ����
void SetFunction(WPARAM wParam, LPARAM lParam,HWND hWnd)
{
    if (HIWORD(wParam) == BN_CLICKED)
    {
        switch (LOWORD(wParam))
        {
        case 1:
        {
            if (SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
                SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Erase"), BM_SETCHECK, BST_UNCHECKED, 0);
                return ;
            }
            else {
                SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);

            }
        }
        case 2:
        {
            if (SendMessageW((HWND)lParam, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                SendMessageW((HWND)lParam, BM_SETCHECK, BST_CHECKED, 0);
                SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Pen"), BM_SETCHECK, BST_UNCHECKED, 0);
                return ;
            }
            else {
                SendMessageW((HWND)lParam, BM_SETCHECK, BST_UNCHECKED, 0);
            }
        }

        } // ����ġ�� ����

    }
    return ;
}

//��� �� �޾ƿ���
int GetFunction(WPARAM wParam, LPARAM lParam, HWND hWnd)
{
    // 1 == �׸��� 2 == ����� ���� �� 0
    if (SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Pen"), BM_GETCHECK, BST_CHECKED, 0) == BST_CHECKED) return 1;
    if (SendMessageW(FindWindowExW(hWnd, NULL, L"button", L"Erase"), BM_GETCHECK, BST_CHECKED, 0) == BST_CHECKED) return 2;
    else return 0;

}

//��ũ�� ����
void SetScrollFunction(WPARAM wParam, LPARAM lParam)
{

    switch (LOWORD(wParam))
    {
    case SB_LINELEFT:
        SetScrollPos((HWND)lParam, SB_CTL, max(0,GetScrollPos((HWND)lParam,SB_CTL)-1), TRUE);
        break;
    case SB_PAGELEFT:
        SetScrollPos((HWND)lParam, SB_CTL, max(0, GetScrollPos((HWND)lParam, SB_CTL) - 5), TRUE);
        break;
    case SB_LINERIGHT:
        SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 1), TRUE);
        break;
    case SB_PAGERIGHT:
        SetScrollPos((HWND)lParam, SB_CTL, min(255, GetScrollPos((HWND)lParam, SB_CTL) + 5), TRUE);
        break;
    case SB_THUMBTRACK:
        SetScrollPos((HWND)lParam, SB_CTL, HIWORD(wParam), TRUE);
        break;
    }
}
//��� ����� �ɰ��� �ϳ��� �߰��� ����


