#include "Window.h"

LRESULT CALLBACK Window::WndProc(HWND Wnd, UINT Msg, WPARAM WParam, LPARAM	LParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SYSCOMMAND:
	{
		switch (LParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0; // Interrupt the action
		}
		break;
	}
	}
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(Wnd, Msg, WParam, LParam);
}

bool Window::Init(ApplicationProperties &properties)
{
	CloseApplication = false;

	// 1- Init vars
	DC = NULL;
	Wnd = NULL;
	Instance = GetModuleHandle(NULL);
	Properties = properties;

	// 2- Register the window Class Structure
	WNDCLASS WndClass;
	// Redraw On Size, and Own DC For Window.
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	// WndProc Handles Messages
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	// No Extra Window Data
	WndClass.cbClsExtra = 0;
	// No Extra Window Data
	WndClass.cbWndExtra = 0;
	// Set the instance
	WndClass.hInstance = Instance;
	// Load the default Icon
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// Load the Arrow Pointer
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// No Background Required for GL
	WndClass.hbrBackground = NULL;
	// We Don´t Want a Menu
	WndClass.lpszMenuName = NULL;
	// Set the Class Name
	WndClass.lpszClassName = Properties.ApplicationName.c_str();


	int Ret = RegisterClass(&WndClass);
	if (!Ret) // Attempt To Register The Window Class
	{
		DWORD Error = GetLastError();
		MessageBox(NULL, "Failed to Register the Window", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// 3- Preparation of Window for FullScreen 
	if (Properties.Fullscreen)
	{
		// Device Mode
		DEVMODE ScreenSettings;
		// Clear the memory
		memset(&ScreenSettings, 0, sizeof(ScreenSettings));
		ScreenSettings.dmSize = sizeof(ScreenSettings);
		ScreenSettings.dmPelsWidth = Properties.Width;
		ScreenSettings.dmPelsHeight = Properties.Height;
		ScreenSettings.dmBitsPerPel = Properties.Bits;
		ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try to Set Selected Mode and Get Results.
		LONG Result = ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);
		if (Result != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "The Requested FullScreen Mode Is Not Supported By\n Your Video Card. Use Windowed Mode Instead?",
				"ERROR", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				Properties.Fullscreen = false;
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}

	// 4- Window Creation
	DWORD lExStyle;
	DWORD lStyle;
	if (Properties.Fullscreen)
	{
		// Window Extended Style
		lExStyle = WS_EX_APPWINDOW;
		// Windows Style
		lStyle = WS_POPUP;
		// Hide Mouse Pointer
		ShowCursor(FALSE);
	}
	else
	{
		//Window Extended Style
		lExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		// Windows Style
		lStyle = WS_OVERLAPPEDWINDOW;
	}

	RECT WindowRect;// Setting Dimensions
	WindowRect.left = (long)0;
	WindowRect.right = (long)Properties.Width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)Properties.Height;

	AdjustWindowRectEx(&WindowRect, lStyle, FALSE, lExStyle);

	// Create The Window
	Wnd = CreateWindowEx(lExStyle,
		Properties.ApplicationName.c_str(),
		Properties.ApplicationName.c_str(),
		lStyle |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		0, 0,
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,
		NULL,
		NULL,
		Instance,
		NULL);

	if (!Wnd)
	{
		Deinit();	// Reset the Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow( Wnd, SW_SHOW);
	SetForegroundWindow( Wnd);
	SetFocus(Wnd);

	// 5- Access to Device´s context
	DC = GetDC(Wnd);
	if (!DC)
	{
		Deinit();
		MessageBox(NULL, "Can´t access the HDC.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

void Window::Update()
{
	MSG Msg;
	// Is There A Message Waiting?
	if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		// Have we Receibed a Quit Message ?
		if (Msg.message == WM_QUIT)
		{
			CloseApplication = true;
		}
		else
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}

bool Window::Deinit()
{
	if (Properties.Fullscreen)
	{
		// If So switch Back To The Desktop Resolution
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (DC && !ReleaseDC(Wnd, DC))
	{
		DC = NULL;
		return false;
	}

	if (Wnd && !DestroyWindow(Wnd))
	{
		Wnd = NULL;
		return false;
	}

	if (!UnregisterClass(Properties.ApplicationName.c_str(), Instance))
	{
		Instance = NULL;
		return false;
	}
	return true;
}