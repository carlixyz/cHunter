#ifndef WIN_H
#define	WIN_H

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Utility/Singleton.h"
#include "AppProperties.h"

class Window : public Singleton<Window>
{
private:
	friend class Singleton<Window>;
	HINSTANCE Instance;
	HWND Wnd;
	HDC DC;
	ApplicationProperties Properties;
	bool CloseApplication = false;

	static LRESULT CALLBACK WndProc(HWND Wnd, UINT Msg, WPARAM WParam, LPARAM LParam);

public:
	//Method to initialize the Window
	bool Init(ApplicationProperties &properties);
	// Method to update the window
	void Update();
	//Method to deinitialize the window
	bool Deinit();

	//Method to get the width 
	inline unsigned GetWidth() { return Properties.Width; }

	//Method to get the height
	inline unsigned GetHeight() { return Properties.Height; }

	//Method to get the bpp
	inline unsigned GetBpp() { return Properties.Bits; }

	//Get DC
	inline HDC &GetHDC() { return DC; }

	inline bool GetCloseApplication() { return CloseApplication; }
	inline HWND GetHWND() { return Wnd; }

protected:
	Window() { ; }
};

#endif