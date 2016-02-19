#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <tchar.h>
#define _WIN32_WINNT 0x0500
#define IDC_TEXT1 101
#define IDC_BUTTON_GO 102
#define IDC_BUTTON_CLEAR 103
#define IDC_TEXT2 104
#define IDC_BUTTON_C1 105
#define IDC_BUTTON_C2 106

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */
  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = szClassName;
  wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
  wincl.style = CS_HREDRAW | CS_VREDRAW;
  wincl.cbSize = sizeof (WNDCLASSEX);

  /* Use default icon and mouse-pointer */
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName = NULL;                 /* No menu */
  wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
  wincl.cbWndExtra = 0;                      /* structure or the window instance */
  /* Use Windows's default colour as the background of the window */
  wincl.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);

  /* Register the window class, and if it fails quit the program */
  if (!RegisterClassEx (&wincl))
    return 0;

  /* The class is registered, let's create the program*/
  hwnd = CreateWindowEx (
    0,                   /* Extended possibilites for variation */
    szClassName,         /* Classname */
    "WP Lab_No1.1_Cotovici Alexandra",  /* Title Text */
    WS_OVERLAPPEDWINDOW, /* default window */
    440,///CW_USEDEFAULT,       /* Windows start the position */
    200,///CW_USEDEFAULT,       /* where the window ends up on the screen */
    544,                 /* The programs width */
    375,                 /* and height in pixels */
    HWND_DESKTOP,        /* The window is a child-window to desktop */
    NULL,                /* No menu */
    hThisInstance,       /* Program Instance handler */
    NULL                 /* No Window Creation data */
  );


  /* Make the window visible on the screen */
  ShowWindow (hwnd, nCmdShow);

  /* Run the message loop. It will run until GetMessage() returns 0 */
  while (GetMessage (&messages, NULL, 0, 0)){
    /* Translate virtual-key messages into character messages */
    TranslateMessage(&messages);
    /* Send message to WindowProcedure */
    DispatchMessage(&messages);
  }

  /* The program return-value is 0 - The value that PostQuitMessage() gave */
  return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
  PAINTSTRUCT paintStruct;
  HDC hdc;
  RECT rect;
  HBRUSH textArea1Brush;
  HBRUSH textArea2Brush;
  static HWND textArea1, buttonGo, buttonClear,
           textArea2, buttonViolet, buttonOrange;
  static int cxCoord, cyCoord;
  LRESULT textSize, textSize2;
  char textStore[1000];
  static bool textFlagViolet, textFlagOrange;
  static bool backgFlag;
  static int a, b, c;




  switch (message){
                 /* handle the messages */
    case WM_CREATE:{

        textArea1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_TEXT1, GetModuleHandle(NULL), NULL);
            buttonGo = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("GO"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_GO, GetModuleHandle(NULL), NULL);
            buttonClear =  CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Clear"),
                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);
            textArea2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_TEXT1, GetModuleHandle(NULL), NULL);
            buttonViolet = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Violet"),
                                       WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_DEFPUSHBUTTON,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_C1, GetModuleHandle(NULL), NULL);
            buttonOrange = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Orange"),
                                       WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_DEFPUSHBUTTON,
                                       0, 0, 0, 0,
                                       hwnd, (HMENU)IDC_BUTTON_C2, GetModuleHandle(NULL), NULL);

            SendMessage(textArea1, WM_SETTEXT, NULL, (LPARAM)"Insert text here... ");


        break;

    }
    case WM_PAINT:{
        hdc = BeginPaint(hwnd,&paintStruct);
        GetClientRect (hwnd, &rect);
        DrawText(hdc,TEXT("Done with Pride and Prejudice by Cotovici Alexandra "),-1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &paintStruct);
        return 0;
        break;
    }
    case WM_DRAWITEM:
            if ((UINT)wParam == IDC_BUTTON_C1) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szVioletBtnText[7];
                strcpy(szVioletBtnText, "Violet");
                GetTextExtentPoint32(lpdis->hDC, szVioletBtnText, strlen(szVioletBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(255,255,255));
                SetBkColor(lpdis->hDC, RGB(128,0,128));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szVioletBtnText,
                    strlen(szVioletBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);
                return TRUE;
			}

			else if ((UINT)wParam == IDC_BUTTON_C2) {
                LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                SIZE size;
                char szOrangeBtnText[7];
                strcpy(szOrangeBtnText, "Orange");
                GetTextExtentPoint32(lpdis->hDC, szOrangeBtnText, strlen(szOrangeBtnText), &size);
                SetTextColor(lpdis->hDC, RGB(255,255,255));
                SetBkColor(lpdis->hDC, RGB(255,165,0));

                ExtTextOut(
                    lpdis->hDC,
                    ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                    ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                    ETO_OPAQUE | ETO_CLIPPED,
                    &lpdis->rcItem,
                    szOrangeBtnText,
                    strlen(szOrangeBtnText),
                    NULL);

                DrawEdge(
                    lpdis->hDC,
                    &lpdis->rcItem,
                    (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                    BF_RECT);

                return TRUE;

			}

			break;

    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
            winSize->ptMinTrackSize.x = 510;
            winSize->ptMinTrackSize.y = 375;
            winSize->ptMaxTrackSize.x = 630;
            winSize->ptMaxTrackSize.y = 425;
            break;
        }


   case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_BUTTON_GO:
                {
                    textSize = SendMessage(textArea1, WM_GETTEXT, 100, (LPARAM)textStore); // text size
                    textStore[textSize] = _T('\0'); // initialization with null character
                    SendMessage(textArea2, EM_REPLACESEL, 0, (LPARAM)textStore); // add inputed text to window
                    SendMessage(textArea2, EM_REPLACESEL, 0, (LPARAM)" ");
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
                    break;
                }

                case IDC_BUTTON_CLEAR:
                {
                    SendMessage(textArea2, WM_SETTEXT, NULL, NULL);
                    break;
                }

                case IDC_BUTTON_C1:
                {
                    textFlagViolet = true;
                    textFlagOrange = false;
                    InvalidateRect(textArea2,NULL, TRUE);
                    break;
                }

                case IDC_BUTTON_C2:
                {
                    textFlagOrange = true;
                    textFlagViolet = false;
                    InvalidateRect(textArea2,NULL, TRUE);
                    break;
                }

                }
        break;

    case WM_SIZE:
        {
            cxCoord = LOWORD(lParam); // 544
            cyCoord = HIWORD(lParam); // 375
            MoveWindow(textArea2, 20, 45, cxCoord-40, cyCoord/2-97, TRUE);
            MoveWindow(buttonViolet, 20, cyCoord/2-40, cxCoord-430, cyCoord/2-144, TRUE);
            MoveWindow(buttonOrange, 411, cyCoord/2-40, cxCoord-430, cyCoord/2-144, TRUE);
            MoveWindow(textArea1, 20, cyCoord-140, cxCoord-40, cyCoord/2-97, TRUE);
            MoveWindow(buttonGo, 20, (cyCoord-175) + cyCoord/2-55, cxCoord-425, cyCoord/2-135, TRUE);
            MoveWindow(buttonClear, 213, (cyCoord-175) + cyCoord/2-55, cxCoord-425, cyCoord/2-135, TRUE);
            break;
        }
    case WM_CTLCOLOREDIT:
        {
            if(IDC_TEXT1 == GetDlgCtrlID((HWND)lParam))
            {
                textArea1Brush = CreateSolidBrush(RGB(255, 255, 0));
                SetBkMode((HDC)wParam, TRANSPARENT);
                return(INT_PTR)textArea1Brush;
            }
            else if(IDC_TEXT2 == GetDlgCtrlID((HWND)lParam))
            {
                textArea2Brush = CreateSolidBrush(RGB(0, 255, 0));
                SetBkMode((HDC)wParam, TRANSPARENT);
                return(INT_PTR)textArea2Brush;
            }
            break;
        }
    case WM_SYSCOMMAND:
        {
            switch(wParam)
            {
                case SC_MINIMIZE:
                {
                    return MessageBox(NULL, TEXT("You just clicked Minimize button"),
                                       TEXT("Minimize Button Clicked!"), MB_OK | MB_ICONEXCLAMATION);


                    break;
                }

                case SC_MAXIMIZE:
                {
                    srand(time(NULL));
                    a = rand() % 255 + 1;
                    b = rand() % 255 + 1;
                    c = rand() % 255 + 1;
                    backgFlag = true;
                    if(backgFlag == true)
                    {
                        SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(a, b, c)));
                    }
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;
                 }

                 case SC_CLOSE:
                 {
                    if(MessageBox(hwnd, "Do you want to close the program?", "Alert", MB_YESNO) == IDYES)
                        {
                            exit(1);
                        }
                        break;
                 }

                 default:
                     return DefWindowProc(hwnd, message, wParam, lParam);
                }
            break;
        }

    case WM_CTLCOLORSTATIC:
        {
            if(textFlagViolet == true && (HWND)lParam == textArea2)
            {
                HBRUSH hbr = (HBRUSH) DefWindowProc(hwnd, message, wParam, lParam);
                SetTextColor((HDC) wParam, RGB(255,0,255));
                return (BOOL) hbr;
            }
            else if(textFlagOrange == true && (HWND)lParam == textArea2)
            {
                HBRUSH hbr = (HBRUSH) DefWindowProc(hwnd, message, wParam, lParam);
                SetTextColor((HDC) wParam, RGB(255, 165, 0));
                return (BOOL) hbr;
            }

            break;
        }
    case WM_DESTROY:
      PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
      break;

    default:                      /* for messages that we don't deal with */
      return DefWindowProc (hwnd, message, wParam, lParam);
  }

  return 0;
}
