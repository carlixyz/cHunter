#pragma once

#include "../Utility/Singleton.h"
#include "GLHeaders.h"
#include "../Window/Window.h"
#include "../Libraries/MathLib/MathLib.h"
#include "Camera.h"

class Window;								// foward Decls

class Graphics : public Singleton<Graphics>
{

	Window * window;
	GLuint pixelFormat;						 
	HGLRC HRC;								// OpenGL Render Context Handle

	Camera * currentCam;
	cMatrix WorldMatrix;


	bool CreateContext(Window * win);
	void InitializeGLState();

	public:
		friend class Singleton<Graphics>;

		bool Init(Window * win);
		bool Deinit();
		void SwapBuffer();


		void DrawPoint(const cVec3 &pos, const cVec3 &color);
		void DrawLine(const cVec3 &pos1, const cVec3 &pos2, const cVec3 &color );
		void DrawGrid();
		void DrawAxis();

		void ActivateCamera(Camera * cam);
		void SetWorldMatrix(const cMatrix &matrix);
		void RefreshWorldView();

	protected:
		Graphics() { ; }					// Protected Constructor

};

