// main.cpp : Defines the entry point for the application.
//

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers.
// Windows Header Files:
#include <windows.h>

// C/C++ RunTime Header Files:
#include <tchar.h>
#include <exception>

#include "timer.h"
#include "ini_params.h"
#include "utils.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;					 // current instance
TCHAR szTitle[MAX_LOADSTRING];		 // the title bar text
TCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name

//load simulation parameters
Simulation::Ini_params ini_params;

//create a timer
Simulation::Timer timer(ini_params.m_fFramesPerSecond);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


//
//  FUNCTION: WinMain()
//
//  PURPOSE: Application main entry point.
//
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	try
	{
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		MSG msg;
		HACCEL hAccelTable;

		// Initialize global strings.
		LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInstance, IDC_NEURAL_NEWORKS_SIMULATION, szWindowClass, MAX_LOADSTRING);
		MyRegisterClass(hInstance);

		// Perform application initialization:
		if (!InitInstance (hInstance, nCmdShow))
		{
			return FALSE;
		}

		hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NEURAL_NEWORKS_SIMULATION));

		//start the timer
		timer.start();

		bool bDone = FALSE;

		// Main message loop:
		while(!bDone)
		{			
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE )) 
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					if( msg.message == WM_QUIT ) 
					{
						// Stop loop if it's a quit message.
						bDone = TRUE;
					} 
					else 
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			if (timer.readyForNextFrame())
			{
				// This will call WM_PAINT which will render the scene.
				InvalidateRect(msg.hwnd, NULL, TRUE);
				UpdateWindow(msg.hwnd);
			}
		}

		UnregisterClass(szWindowClass, hInstance );
		return FALSE;
	}
	catch(std::exception ex)
	{
		MessageBox(NULL, Utils::string_to_wstring(std::string(ex.what())).c_str(), L"ERROR!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NEURAL_NEWORKS_SIMULATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NEURAL_NEWORKS_SIMULATION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}



//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window.
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in global variable.

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		GetSystemMetrics(SM_CXSCREEN) / 2 - ini_params.m_iWindowWidth / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - ini_params.m_iWindowHeight / 2,
		ini_params.m_iWindowWidth,
		ini_params.m_iWindowHeight,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	HDC hdc_hWnd;

	int wmId;
	int wmEvent;

	// These hold the dimensions of the client window area.
	static int cxClient, cyClient;

	// Used to create the back buffer.
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;

	std::wstring fps_string;

	try
	{
		switch (message)
		{
		case WM_CREATE: 
			// Get the size of the client window.
			RECT rect;
			GetClientRect(hWnd, &rect);

			cxClient = rect.right;
			cyClient = rect.bottom;

			// Create a surface for us to render to (backbuffer).
			hdc = CreateCompatibleDC(NULL);

			hdc_hWnd = GetDC(hWnd);
			hBitmap = CreateCompatibleBitmap(hdc_hWnd, cxClient, cyClient);
			ReleaseDC(hWnd, hdc_hWnd);

			hOldBitmap = static_cast<HBITMAP>(SelectObject(hdc, hBitmap)); 

			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

			// Has the user resized the client area?
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			// Resize the backbuffer accordingly.
			SelectObject(hdc, hOldBitmap);

			hdc_hWnd = GetDC(hWnd);
			hBitmap = CreateCompatibleBitmap(hdc_hWnd, cxClient, cyClient);
			ReleaseDC(hWnd, hdc_hWnd);

			hOldBitmap = static_cast<HBITMAP>(SelectObject(hdc, hBitmap));

			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);

			// Fill the backbuffer with white.
			BitBlt(hdc, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);

			// Print the simulation FPS rate.
			fps_string = L"FPS: " + Utils::ftos(timer.getFPS());
			TextOut(hdc, 5, 0, fps_string.c_str(), fps_string.length());

			// Now blit backbuffer to front.
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdc, 0, 0, SRCCOPY); 

			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			SelectObject(hdc, hOldBitmap);

			// Clean up backbuffer objects.
			DeleteDC(hdc);
			DeleteObject(hBitmap); 

			// Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	catch(std::exception ex)
	{
		MessageBox(NULL, Utils::string_to_wstring(std::string(ex.what())).c_str(), L"ERROR!", MB_OK|MB_ICONERROR);
		
		SelectObject(hdc, hOldBitmap);

		// Clean up backbuffer objects.
		DeleteDC(hdc);
		DeleteObject(hBitmap); 

		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);
	}

	return S_OK;
}



// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
