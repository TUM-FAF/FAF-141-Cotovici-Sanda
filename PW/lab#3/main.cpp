#include <windows.h>
#include <windowsx.h>
#include "resources.h"
#include <string.h>
#include <iostream>
#include <stdio.h>


LPSTR szClassName = "Lab3Class";
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

void updateColorControls(HDC, COLORREF, int, int);
int getFromInput(HWND);
POINT getCurrentPointPosition(int, int, RECT, int);

COLORREF fillColor = RGB(255, 0 ,255);
COLORREF borderColor = RGB(0, 0, 0);
COLORREF colorSelect(HWND hwnd, COLORREF color)
{
    COLORREF g_rgbCustom[16] = {0};
    CHOOSECOLOR cc = {sizeof(CHOOSECOLOR)};

    cc.Flags = CC_RGBINIT | CC_SOLIDCOLOR;
    cc.hwndOwner = hwnd;
    cc.rgbResult = color;
    cc.lpCustColors = g_rgbCustom;

    if(ChooseColor(&cc))
    {
        color = cc.rgbResult;
    }
    //InvalidateRect(hwnd, NULL,FALSE);
    return color;
}

// Redirecting child messages to parent window
WNDPROC GroupBoxProc;
LONG CALLBACK GroupRelay(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_COMMAND || msg == WM_NOTIFY){
        return SendMessage(GetParent(hwnd), msg, wParam, lParam);
    }

    return CallWindowProc(GroupBoxProc, hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASSEX wincl;
    MSG msg;
    HWND hwnd;
    hInst = hInstance;

    /* The Window Structure */
    wincl.hInstance = hInst;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);                             // Default icon
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);                                  // Default arrow mouse cursor
    wincl.lpszMenuName = NULL;                                                    // No menu
    wincl.cbClsExtra = 0;                                                         // No extra bytes after the window class
    wincl.cbWndExtra = 0;                                                         //  structure or the window instance

    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(216,191,216));

    if(!RegisterClassEx(&wincl))                                                  // Register the WNDCLASSEX
    {
        MessageBox(NULL, "This Program Requires Windows NT", "Error", MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        (DWORD)NULL,
        szClassName,
        "Laboratory based on GDI",                                                                // Window title
        WS_OVERLAPPED | WS_BORDER | WS_SYSMENU,                                 // Basic window style
        CW_USEDEFAULT, CW_USEDEFAULT,                                           // Set starting point to default value
        800, 515,                                                               // Set all the dimensions to default value
        NULL,                                                                   //no parent window
        NULL,                                                                   //no menu
        hInst,
        NULL);                                                                  //no parameters to pass

    ShowWindow(hwnd, iCmdShow);                                                 //display the window on the screen
    UpdateWindow(hwnd);                                                         //make sure the window is updated correctly

    while(GetMessage(&msg, NULL, 0, 0))                                         //message loop
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndToolsGroup;
    static HWND hwndPencilTool;
    static HWND hwndEllipseTool;
    static HWND hwndLineTool;
    static HWND hwndEraserTool;
    static HWND hwndFillCheck;
    static HWND hwndBorderWidth;
    static HWND hwndEraserWidth;
    static HWND hwndRectangleTool;
    static HWND hwndEditGroup;
    static HWND hwndBezierTool;
    static HWND hwndClear;
    RECT rect ;
    int screenW;
    int screenH;
    PAINTSTRUCT ps;
    HDC hdc = GetDC(hwnd);
    int xMouse, yMouse;

    // Color preview rectangles
    int xFillPreview   = 655;
    int yFillPreview   = 230;
    int xStrokePreview = 655;
    int yStrokePreview = 280;


    HDC hdcMem,hdcLine, hdcEllipse, hdcRect;
    /*
    BITMAP bitmap;
    HBITMAP hbmpDesignerImage = NULL;
    hbmpDesignerImage = (HBITMAP)LoadImage(hInst, "paint_brush.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpDesignerImage, sizeof(bitmap), &bitmap);*/

    static BITMAP bitmap, linebit, ellipsebit, rectbit;
    static HBITMAP hbmplogo = NULL ;
    static HBITMAP hLine = NULL;
    static HBITMAP hEllipse = NULL;
    static HBITMAP hRect    = NULL;

     hbmplogo = (HBITMAP)LoadImage(hInst, "pen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmplogo, sizeof(bitmap), &bitmap);

    hLine = (HBITMAP)LoadImage(hInst, "line.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hLine, sizeof(linebit), &linebit);

    hEllipse = (HBITMAP)LoadImage(hInst, "ellipse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hEllipse, sizeof(ellipsebit), &ellipsebit);

    hRect = (HBITMAP)LoadImage(hInst, "rect.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hRect, sizeof(rectbit), &rectbit);


    static RECT drawingArea = {15, 15, 530, 380};
    static RECT fillColorRect = {xFillPreview, yFillPreview, xFillPreview + 25, yFillPreview + 20};
    static RECT borderColorRect = {xStrokePreview, yStrokePreview, xStrokePreview + 25, yStrokePreview + 20};
    static RECT gradientRect = {45, 450, 250, 400};
    static RECT gradientRect2 = {275, 450, 500, 400};
    static RECT tempRect;
    static RECT tempRect2;


    // Drawing stuff
    HBRUSH hBrush;
    static POINT pointPen;
    POINT point;
    HPEN linePen;
    int width;

    static BOOL lineStarted;
    static POINT line;
    static BOOL rectangleStarted;
    static RECT rectangle;
    static BOOL ellipseStarted;
    static RECT ellipse;
    static int bezierStage = 0;
    static POINT bezierPoints[4];

    HPEN borderPen;
    HBRUSH fillBrush;

    switch(msg)
    {
        case WM_CREATE:
            screenW = GetSystemMetrics(SM_CXSCREEN);
            screenH = GetSystemMetrics(SM_CYSCREEN);
            GetWindowRect(hwnd, &rect);
            SetWindowPos(
                    hwnd, 0,
                    (screenW - rect.right)/2,
                    (screenH - rect.bottom)/2,
                    0, 0, SWP_NOZORDER|SWP_NOSIZE);

            // Drawing tools group
            hwndToolsGroup = CreateWindowEx(
                0,
                "Button",
                "Tools",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                555, 15,
                140, 150,
                hwnd,
                (HMENU)IDB_TOOLS_GROUP,
                hInst,
                NULL);

            // Pen tool
            hwndPencilTool = CreateWindowEx(
                0,
                "Button",
                "Pencil",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 15,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_PENCIL_TOOL,
                hInst,
                NULL);
            Button_SetCheck(hwndPencilTool, BST_CHECKED);
            // Line tool
            hwndLineTool = CreateWindowEx(
                0,
                "Button",
                "Line",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 35,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_LINE_TOOL,
                hInst,
                NULL);
// Rectangle tool
            hwndRectangleTool = CreateWindowEx(
                0,
                "Button",
                "Rectangle",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 55,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_RECTANGLE_TOOL,
                hInst,
                NULL);


            // Ellipse tool
            hwndEllipseTool = CreateWindowEx(
                0,
                "Button",
                "Ellipse",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 75,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_ELLIPSE_TOOL,
                hInst,
                NULL);


            // Bezier tool
            hwndBezierTool = CreateWindowEx(
                0,
                "Button",
                "Bezier",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 95,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_ERASER_TOOL,
                hInst,
                NULL);

            // Eraser tool
            hwndEraserTool = CreateWindowEx(
                0,
                "Button",
                "Eraser",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                15, 115,
                120, 20,
                hwndToolsGroup,
                (HMENU)IDB_ERASER_TOOL,
                hInst,
                NULL);

            // Editable group
            hwndEditGroup = CreateWindowEx(
                0,
                "Button",
                "Edit",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                555, 190,
                150, 150,
                hwnd,
                (HMENU)IDB_TOOLS_GROUP,
                hInst,
                NULL);

            // Fill checkbox
            hwndFillCheck = CreateWindowEx(
                0,
                "Button",
                "Fill with color",
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                10, 15,
                120, 20,
                hwndEditGroup,
                (HMENU)IDB_FILL_CHECK,
                hInst,
                NULL);

            // Fill with label
            CreateWindowEx(
                0,
                "Static",
                "Fill with",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 40,
                90, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border width label
            CreateWindowEx(
                0,
                "Static",
                "Border width",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 65,
                100, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border width input
            hwndBorderWidth = CreateWindowEx(
                0,
                "Edit",
                "1",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                100, 65,
                25, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Border color label
            CreateWindowEx(
                0,
                "Static",
                "Border color",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 90,
                90, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Eraser width label
            CreateWindowEx(
                0,
                "Static",
                "Eraser width",
                WS_VISIBLE | WS_CHILD | SS_LEFT,
                10, 115,
                100, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);

            // Eraser width input
            hwndEraserWidth = CreateWindowEx(
                0,
                "Edit",
                "1",
                WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                100, 115,
                25, 20,
                hwndEditGroup,
                (HMENU)0,
                hInst,
                NULL);
            hwndClear = CreateWindow(TEXT("Button"), TEXT("Clear all"),
                      WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                      550, 370,
                      160, 40,
                      hwnd, (HMENU)IDI_CLEAR,
                      NULL, NULL);


            // Redirecting child messages to parent window
            GroupBoxProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hwndEditGroup, GWLP_WNDPROC));
            SetWindowLongPtr(hwndEditGroup, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GroupRelay));

            GroupBoxProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hwndToolsGroup, GWLP_WNDPROC));
            SetWindowLongPtr(hwndToolsGroup, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(GroupRelay));
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDI_CLEAR:
                InvalidateRect(hwnd, &drawingArea, FALSE);
				InvalidateRect(hwnd, &drawingArea, TRUE);
            break;
                default:
                    DefWindowProc(hwnd, WM_COMMAND, wParam, lParam);
                    break;
            }
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Fill color preview rectangle
            updateColorControls(hdc, fillColor, xFillPreview, yFillPreview);

            // Stroke color preview rectangle
            updateColorControls(hdc, borderColor, xStrokePreview, yStrokePreview);

            // Draw image

            hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hbmplogo);
            BitBlt(hdc, 700, 30, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);

            hdcLine = CreateCompatibleDC(hdc);
            SelectObject(hdcLine, hLine);
            BitBlt(hdc, 700, 50, linebit.bmWidth, linebit.bmHeight, hdcLine, 0, 0, SRCCOPY);
            DeleteDC(hdcLine);

            hdcEllipse = CreateCompatibleDC(hdc);
            SelectObject(hdcEllipse, hEllipse);
            BitBlt(hdc, 700, 90, ellipsebit.bmWidth, ellipsebit.bmHeight, hdcEllipse, 0, 0, SRCCOPY);
            DeleteDC(hdcEllipse);

            hdcRect = CreateCompatibleDC(hdc);
            SelectObject(hdcRect, hRect);
            BitBlt(hdc, 700, 70, rectbit.bmWidth, rectbit.bmHeight, hdcRect, 0, 0, SRCCOPY);
            DeleteDC(hdcRect);

            // Blank draw area
            SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
            SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
            Rectangle(hdc, drawingArea.left, drawingArea.top, drawingArea.right, drawingArea.bottom);

            tempRect.top = gradientRect.top;
            tempRect.bottom = gradientRect.bottom;
            for(int i = 0; i < (gradientRect.right - gradientRect.left); i++) {
                int purple;
                purple = i * 255 / (gradientRect.right - gradientRect.left);
                tempRect.left  = gradientRect.left  + i;
                tempRect.right = gradientRect.left + i + 1;
                hBrush = CreateSolidBrush(RGB(purple, 0, purple));
                FillRect(hdc, &tempRect, hBrush);
                DeleteObject(hBrush);
            }

            tempRect2.top = gradientRect2.top;
            tempRect2.bottom = gradientRect2.bottom;
            for(int i = 0; i < (gradientRect2.right - gradientRect2.left); i++) {
                int yellow;
                yellow = i * 255 / (gradientRect2.right - gradientRect2.left);
                tempRect2.left  = gradientRect2.left  + i;
                tempRect2.right = gradientRect2.left + i + 1;
                hBrush = CreateSolidBrush(RGB(yellow,yellow,0));
                FillRect(hdc, &tempRect2, hBrush);
                DeleteObject(hBrush);
            }

            EndPaint(hwnd, &ps);
            break;

        case WM_LBUTTONDOWN:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);

            if(xMouse >= fillColorRect.left && xMouse <= fillColorRect.right)
            {
                if(yMouse >= fillColorRect.top && yMouse <= fillColorRect.bottom)
                {
                    fillColor = colorSelect(hwnd, fillColor);
                    updateColorControls(hdc, fillColor, xFillPreview, yFillPreview);
                }
                else if(yMouse >= borderColorRect.top && yMouse <= borderColorRect.bottom)
                {
                    borderColor = colorSelect(hwnd, borderColor);
                    updateColorControls(hdc, borderColor, xFillPreview, yFillPreview);
                }
                return 0;
            }

            if( (xMouse > drawingArea.left) && (xMouse < drawingArea.right) &&
                (yMouse > drawingArea.top) && (yMouse < drawingArea.bottom) )
            {
                width = getFromInput(hwndBorderWidth);
                point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                xMouse = point.x;
                yMouse = point.y;

                // If Pencil tool is selected, setting startpoint
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndPencilTool) == BST_CHECKED))
                {
                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                // Line
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndLineTool) == BST_CHECKED))
                {
                    line.x = xMouse;
                    line.y = yMouse;
                    lineStarted = true;
                }

                // Rectangle
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndRectangleTool) == BST_CHECKED))
                {
                    rectangle.left = xMouse;
                    rectangle.top = yMouse;
                    rectangleStarted = true;
                }

                // Ellipse
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndEllipseTool) == BST_CHECKED))
                {
                    ellipse.left = xMouse;
                    ellipse.top = yMouse;
                    ellipseStarted = true;
                }

                // Bezierceg
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndBezierTool) == BST_CHECKED))
                {
                    if(bezierStage == 0)
                    {
                        bezierPoints[0] = point;
                        bezierStage = 1;
                    }
                    else
                    {
                        bezierPoints[2] = point;
                        bezierStage = 3;
                    }
                }
            }
            break;

        case WM_LBUTTONUP:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            width = getFromInput(hwndBorderWidth);
            point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
            xMouse = point.x;
            yMouse = point.y;

            borderPen = CreatePen(PS_SOLID, width, borderColor);
            if(Button_GetCheck(hwndFillCheck) == BST_CHECKED)
                fillBrush = CreateSolidBrush(fillColor);
            else
                fillBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

            if(lineStarted)
            {
                SelectObject(hdc, borderPen);
                MoveToEx(hdc, xMouse, yMouse, NULL);
                LineTo(hdc, line.x, line.y);
                DeleteObject(borderPen);
                lineStarted = false;
            }

            if(rectangleStarted)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);
                Rectangle(hdc, rectangle.left, rectangle.top, xMouse, yMouse);

                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                rectangleStarted = false;
            }

            if(ellipseStarted)
            {
                SelectObject(hdc, borderPen);
                SelectObject(hdc, fillBrush);

                Ellipse(hdc, ellipse.left, ellipse.top, xMouse, yMouse);
                DeleteObject(borderPen);
                DeleteObject(fillBrush);

                ellipseStarted = false;
            }

            if(bezierStage == 1)
            {
                bezierPoints[1] = point;
                bezierStage = 2;
            }

            if(bezierStage == 3)
            {
                bezierPoints[3] = point;
                bezierStage = 0;
                SelectObject(hdc, borderPen);
                PolyBezier(hdc, bezierPoints, 4);
                DeleteObject(borderPen);
            }
            break;

        case WM_MOUSEMOVE:
            xMouse = GET_X_LPARAM(lParam);
            yMouse = GET_Y_LPARAM(lParam);
            if( (xMouse > drawingArea.left) && (xMouse < drawingArea.right) &&
                (yMouse > drawingArea.top) && (yMouse < drawingArea.bottom) )
            {
                 // If Pen tool is selected
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndPencilTool) == BST_CHECKED))
                {
                    width = getFromInput(hwndBorderWidth);
                    point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                    xMouse = point.x;
                    yMouse = point.y;
                    linePen = CreatePen(PS_SOLID, width, borderColor);
                    SelectObject(hdc, linePen);
                    MoveToEx(hdc, xMouse, yMouse, NULL);
                    LineTo(hdc, pointPen.x, pointPen.y);
                    DeleteObject(linePen);
                    pointPen.x = xMouse;
                    pointPen.y = yMouse;
                }

                // If Eraser tool is selected
                if((wParam == MK_LBUTTON) && (Button_GetCheck(hwndEraserTool) == BST_CHECKED))
                {
                    width = getFromInput(hwndEraserWidth);
                    point = getCurrentPointPosition(xMouse, yMouse, drawingArea, width);
                    xMouse = point.x;
                    yMouse = point.y;
                    rect.left = point.x - (width / 2);
                    rect.right = point.x + (width / 2);
                    rect.top = point.y - (width / 2);
                    rect.bottom = point.y + (width / 2);
                    InvalidateRect(hwnd, &rect, FALSE);
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                    //ValidateRect(hwnd, &rect);
                }
            }

            break;

        case WM_CLOSE:
            if(MessageBox(hwnd, "Do you want to close?", "Laboratory work No.3 ", MB_YESNO) == IDYES)
                DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void updateColorControls(HDC hdc, COLORREF rgb, int xLeft, int yTop)
{
    HBRUSH hBrush = CreateSolidBrush(rgb);
    HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(10, 40, 140));

    SelectObject(hdc, hBrush);
    SelectObject(hdc, hPen);

    Rectangle(hdc, xLeft, yTop, xLeft + 25, yTop + 20);

    hBrush = CreateSolidBrush(RGB(10, 40, 140));
    SelectObject(hdc, hBrush);

    Rectangle(hdc, xLeft+18, yTop+13, xLeft + 25, yTop + 20);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

int getFromInput(HWND input)
{
    int result, len;
    len = SendMessage(input, WM_GETTEXTLENGTH, 0, 0);

    char * temp = (char *)malloc(len + 1);
    SendMessage(input, WM_GETTEXT, len + 1, (LPARAM)temp);
    result = atoi(temp);
    free(temp);
    return result;
}

POINT getCurrentPointPosition(int xMouse, int yMouse, RECT limit, int width)
{
    POINT result;
    width = width / 2 + 1;

    if(xMouse + width > limit.right)
        result.x = limit.right - width;
    else if(xMouse - width < limit.left)
        result.x = limit.left + width;
    else
        result.x = xMouse;

    if(yMouse - width < limit.top)
        result.y = limit.top + width;
    else if(yMouse + width > limit.bottom)
        result.y = limit.bottom - width;
    else
        result.y = yMouse;

    return result;
}
