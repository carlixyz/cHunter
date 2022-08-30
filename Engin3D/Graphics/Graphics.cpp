#include "Graphics.h"

#include <assert.h>
#include "../Utility/Utils.h"


bool Graphics::Init(Window * win)
{
	bool Result = CreateContext(win);

	if (Result)
		InitializeGLState();

	return Result;
}

void Graphics::SetWorldMatrix(const cMatrix & matrix)
{
	WorldMatrix = matrix;
}

void Graphics::RefreshWorldView()
{
	// Select the worldModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	// Calculate the ModelView Matrix
	cMatrix WorldView = currentCam->GetView();
	WorldView = WorldMatrix * WorldView;
	// Set the view Matrix
	glLoadMatrixf(WorldView.AsFloatPointer());
}

void Graphics::ActivateCamera(Camera * cam)
{
	assert(cam);
	currentCam = cam;

	//Select the projection matrix;
	glMatrixMode(GL_PROJECTION);
	// Set The projection Matrix
	glLoadMatrixf(currentCam->GetProj().AsFloatPointer());
	// Refresh World View Matrix
	RefreshWorldView();
}

bool Graphics::CreateContext(Window * win)
{
	assert(win);			//Ensure that window != null

	// FULL Pixel Description
	static PIXELFORMATDESCRIPTOR PFD =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		(BYTE)win->GetBpp(),
		0, 0, 0, 0, 0, 0,
		0,
		0, 0, 0, 0, 0, 0,
		32, 0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	//Create & Get Device Context
	HDC &DC = win->GetHDC();
	if (!DC)
	{
		Deinit();
		MessageBox(NULL, "Can't Create A GL Device Context.",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// Create pixel format
	pixelFormat = ChoosePixelFormat(DC, &PFD);
	if (!pixelFormat)
	{
		Deinit();
		MessageBox(NULL, "Can't Find a suitable PixelFormat.",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!SetPixelFormat(DC, pixelFormat, &PFD))
	{
		Deinit();
		MessageBox(NULL, "Can't Set The PixelFormat.",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// Create OpenGL Context
	HRC = wglCreateContext(DC);
	if (!HRC)
	{
		Deinit();
		MessageBox(NULL, "Can't Create A GL Rendering Context.",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// Set the current context
	if (!wglMakeCurrent(DC, HRC))
	{
		Deinit();
		MessageBox(NULL, "Can't Activate the GL Rendering Context.",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	window = win;

	return true;
}

void Graphics::InitializeGLState()
{
	// Specify shade model
	glShadeModel( GL_SMOOTH);		

	// Set background color of the window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Depth Buffer initialization
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	// Perspective and view initialization
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	unsigned width = window->GetWidth();
	unsigned height = window->GetHeight();
	glViewport(0, 0, width, height);

	// Enable use of texture
	glEnable(GL_TEXTURE_2D);

	// set the transparency behaviour
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set the correct projection (perspective)
	// with the aspect based on the window's size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = (float)width / (float)height;
	gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);

	// Put the identity matrix into model matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool Graphics::Deinit()
{
	if (HRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
			MessageBox(NULL, "Release of DC and RC Failed",
				"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);

		if (!wglDeleteContext(HRC))
			MessageBox(NULL, "Release Rendering Context Failed",
				"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	
		HRC = NULL;
	}

	window = NULL;

	return true;
}

void Graphics::SwapBuffer()
{
	if (window)
		SwapBuffers(window->GetHDC());

}

void Graphics::DrawPoint(const cVec3 & pos, const cVec3 & color)
{
	glDisable(GL_TEXTURE_2D);

	// POINT
	glPointSize(10);
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_POINTS);
	glVertex3f(pos.x, pos.y, pos.z);
	glEnd();

	glEnable(GL_TEXTURE_2D);

}

void Graphics::DrawLine(const cVec3 & pos1, const cVec3 & pos2, const cVec3 & color)
{
	glDisable(GL_TEXTURE_2D);

	// LINE
	glLineWidth(1);
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINES);
	for (float xtmp = -10.0f; xtmp <= 10.0f; xtmp += 1.0f)
	{
		glVertex3f(pos1.x, pos1.y, pos1.z);
		glVertex3f(pos2.x, pos2.y, pos2.z);
	};

	glEnd();

	glEnable(GL_TEXTURE_2D);
}

void Graphics::DrawGrid()
{
	glDisable(GL_TEXTURE_2D);

	// GRID
	glLineWidth(1);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);


	for (float xtmp = -10.0f; xtmp <= 10.0f; xtmp += 1.0f)
	{
		glVertex3f(  xtmp, 0.0f, -10.0f);
		glVertex3f(  xtmp, 0.0f, 10.0f);
		glVertex3f(-10.0f, 0.0f, xtmp);
		glVertex3f(10.0f, 0.0f, xtmp);
	}
	glEnd();

	glEnable(GL_TEXTURE_2D);

}

void Graphics::DrawAxis()
{
	glDisable(GL_TEXTURE_2D);

	// AXIS
	glLineWidth(2);
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);	// X AXIS
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);	// Y AXIS
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);	// Z AXIS
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	glEnable(GL_TEXTURE_2D);

}

