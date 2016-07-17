// test_simulation.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "test_simulation.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE, WNDCLASSEX&);
BOOL				InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


//The controller class for this simulation
CController* g_pController = NULL;
CParams g_Params;


//
//  Application entry point.
//
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HWND hWnd;
	MSG msg;
	HACCEL hAccelTable;
	WNDCLASSEX wcex;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST_SIMULATION, szWindowClass, MAX_LOADSTRING);

	wcex.cbSize         = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST_SIMULATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST_SIMULATION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	// register the window class
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, (LPCWSTR)"Error Registering Class!", (LPCWSTR)"Error", 0);
		return 0;
	}

	hInst = hInstance; // Store instance handle in global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST_SIMULATION));

	//create a timer
	CTimer timer(g_Params.fFramesPerSecond);

	//start the timer
	timer.Start();

	// Enter the main message loop.
	bool bDone = FALSE;

	while(!bDone)
	{			
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			if(msg.message == WM_QUIT) 
			{
				//Stop loop if it's a quit message
				bDone = TRUE;
			}
			else 
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}

		if (timer.ReadyForNextFrame() || g_pController->FastRender())
		{	
			if(!g_pController->Update())
			{
				//we have a problem, end app
				bDone = TRUE;
			}

			//this will call WM_PAINT which will render our scene
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}									
	}

	if (g_pController) delete g_pController;

	UnregisterClass(szWindowClass, wcex.hInstance);
	return 0;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hdc;

	//dimensions of the client window area
	static int cxClient, cyClient;

	//used to create the back buffer
	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;

	switch (message)
	{
	case WM_CREATE: 
		{
			//get the size of the client window
			RECT rect;
			GetClientRect(hWnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;

			//setup the controller
			g_pController = new CController(hWnd);

			//create a surface for us to render to (backbuffer)
			hdcBackBuffer = CreateCompatibleDC(NULL);

			HDC hdc = GetDC(hWnd);

			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
			ReleaseDC(hWnd, hdc);

			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap); 

			break;
		}
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				}
			case IDM_EXIT:
				{
					DestroyWindow(hWnd);
					break;
				}
			default:
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			break;
		}
	case WM_KEYUP:
		{
			switch(wParam)
			{
			case VK_ESCAPE: //if ESC pressed
				{
					PostQuitMessage(0);
					break;
				}
			case 'F': //press to show plot
				{
					g_pController->FastRenderToggle();	
					break;
				}
			case 'R': //press to reset the app
				{
					if (g_pController) delete g_pController;
					//setup the new controller
					g_pController = new CController(hWnd);
					break;
				}
			}
			break;
		}
		//has the user resized the client area?
	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			//resize the backbuffer accordingly
			SelectObject(hdcBackBuffer, hOldBitmap);

			HDC hdc = GetDC(hWnd);

			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
			ReleaseDC(hWnd, hdc);

			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap); 

			break;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;

			hdc = BeginPaint(hWnd, &ps);

			//fill backbuffer with white
			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);

			//render the mines and sweepers
			g_pController->Render(hdcBackBuffer);

			//now blit backbuffer to front
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 

			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		{
			SelectObject(hdcBackBuffer, hOldBitmap);
			
			//clean up backbuffer objects
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap); 

			PostQuitMessage(0);
			break;
		}
	default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}
