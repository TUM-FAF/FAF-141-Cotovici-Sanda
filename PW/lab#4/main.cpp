#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <stdio.h>
#include "object.h"

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

static objects *objects[50];
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wnd;

    wnd.hInstance = hInst;
    wnd.lpszClassName = szClassName;
    wnd.lpfnWndProc = WindowProcedure;
    wnd.style =  CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wnd.cbSize = sizeof (WNDCLASSEX);

    wnd.hIcon = LoadIcon (hInst, MAKEINTRESOURCE(IDI_ICON));
    wnd.hIconSm = LoadIcon (hInst, MAKEINTRESOURCE(IDI_ICON));
    wnd.hCursor = LoadCursor (NULL, IDC_ARROW);
    wnd.lpszMenuName = NULL;
    wnd.cbClsExtra = 0;
    wnd.cbWndExtra = 0;
    wnd.hbrBackground =  (HBRUSH) GetStockObject(WHITE_BRUSH);

    COLORREF clr;
    if (!RegisterClassEx (&wnd))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           "Laboratory with Animation",
           WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           800,
           650,
           HWND_DESKTOP,
           NULL,
           hInst,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int cnt;
    static HDC hdc,hdcMem;
    static PAINTSTRUCT ps;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hbmMem;

    static HANDLE hOld;

    static int timerSpeed = 1,noObj = 0;
    static RECT area = {0, 0, 800, 650};

    switch (message)
    {
        case WM_CREATE:
        {
          hdc = GetDC(hwnd);
          GetClientRect(hwnd,&rect);

          SetTimer(hwnd, ID_TIMER, timerSpeed, NULL);
        break;
        }

        case WM_SIZE:
        {
            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            //Gets device context of the window and the rectangle of the client area
            hdc=GetDC(hwnd);
            GetClientRect(hwnd,&rect);
            //Generate the buffer memory using a bitmap akin memory data
            hdcMem=CreateCompatibleDC(hdc);
            hbmMem=CreateCompatibleBitmap(hdc,rect.right,rect.bottom);
            hOld = SelectObject(hdcMem,hbmMem);
            break;
        }

        case WM_MOUSEWHEEL:
        {
            if((short)HIWORD(wParam)<0)
            {
                timerSpeed+=20;
            }
            else
            {
                timerSpeed-=20;
                if (timerSpeed<0)
                {
                    timerSpeed=1;
                }
            }
            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
        break;
        }

        case WM_LBUTTONDOWN:
        {
            POINT newCoord;
            newCoord.x = LOWORD(lParam);
            newCoord.y = HIWORD(lParam);
            cnt=0;
            if (noObj>0)
            {
                for(int i = 0; i<noObj; i++)
                {
                    if(abs(newCoord.x-objects[i]->center.x)<52)
                    {
                        cnt+=1;
                    }
                }
                if(cnt==0)
                {
                    objects[noObj] = new Circle(newCoord,2 + newCoord.x%5);
                    objects[noObj] -> Color(RGB(newCoord.x%200, newCoord.x%150+newCoord.y%100, newCoord.y%200));

                    noObj++;
                }
            }
            else
            {
                objects[noObj] = new Circle(newCoord,2 + newCoord.x%5);
                objects[noObj] -> Color(RGB(newCoord.x%200, newCoord.x%150+newCoord.y%100, newCoord.y%200));

                noObj++;
            }
        break;
        }

         case WM_KEYDOWN:
         {
            switch(wParam)
            {
                case VK_DOWN:
                {
                    timerSpeed+=20;
                break;
                }

                case VK_UP:
                {
                    timerSpeed-=20;

                        if (timerSpeed < 0)
                        {
                            timerSpeed = 1;
                        }
                 break;
                }

                default: return DefWindowProc (hwnd, message, wParam, lParam);
            break;
            }

            KillTimer(hwnd,ID_TIMER);
            SetTimer(hwnd,ID_TIMER,timerSpeed,NULL);
        break;
        }



        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            GetClientRect(hwnd,&rect);

            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem, hbmMem);

            for(int i = 0; i<noObj-1; i++)
            {
                for(int j = i+1; j < noObj; j++)
                {
                    Interaction(*objects[i],*objects[j]);
                }
            }

            FillRect(hdcMem, &rect,(HBRUSH)GetStockObject(WHITE_BRUSH));

            for(int i = 0; i < noObj; i++)
            {
                objects[i] -> Move(hdcMem, rect, hBrush);
            }

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            EndPaint(hwnd,&ps);

        break;
        }

        case WM_ERASEBKGND:
            return 1;
        break;

        case WM_TIMER:
        {
            InvalidateRect(hwnd,NULL,FALSE);
        break;
        }

        case WM_DESTROY:
        {
            KillTimer(hwnd,ID_TIMER);

            PostQuitMessage (0);
        break;
        }

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
