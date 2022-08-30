#include "Game.h"

#include "../Utility/Utils.h"
#include "../Graphics/Graphics.h"


bool Game::Init()
{
	finish = false;

	DEBUG_FILE( "fileDebug.txt", DAY << PLACE << "Compilation number: " << GET_COMP_NUM("Compilations.txt") << "\n");
	DEBUG_OUT(" Last Compilation was " << GET_COMP_NUM("Compilations.txt" ) << "\n" );

	appProperties.LoadConfiguration( "config.yml");
	bool result = Window::Get().Init( appProperties);

	if (result)	// Init OpenGL
	{
		result = Graphics::Get().Init( &Window::Get() );

		if (!result) Window::Get().Deinit(); // If something fails Kill Window
	}

	// Camera 3D Init
	camera3D.Init(appProperties);
	camera3D.SetLookAt(	cVec3::One() * 5.f, cVec3::Zero(), cVec3::Up() );

	return result;
}

void Game::Update(float timeStep)
{

	Window::Get().Update();

	finish = (finish || Window::Get().GetCloseApplication());

	if (finish) return;

	camera3D.Update(timeStep);
}

void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Render Here!
	Graphics::Get().DrawLine(	cVec3(0, 1, -2), cVec3(1, 0, -3), 
								cVec3::Right() +cVec3::Up()  );


	// Activate 3D camera
	Graphics::Get().ActivateCamera(&camera3D);

	// Set World Matrix
	cMatrix world;
	world.LoadIdentity();
	Graphics::Get().SetWorldMatrix(world);

	//Draw Debug Lines
	Graphics::Get().DrawGrid();
	Graphics::Get().DrawAxis();
	Graphics::Get().DrawPoint(	cVec3(-0.5f, 1.0f, -1.5f),
								cVec3::Foward() + cVec3::Right() );

	Graphics::Get().DrawLine(	cVec3(-1.5f, 0.0f,-1.5f),
								cVec3(-1.5f, 0.0f, 1.5f), 
								cVec3::Up());


	//world.LoadTranslation(cVec3(1, 0, -1.5f));
	//Graphics::Get().SetWorldMatrix(world);

	////


	Graphics::Get().SwapBuffer();

}


bool Game::Deinit()
{
	SET_COMP_NUM("Compilations.txt");

	bool result = Graphics::Get().Deinit();

	result = result && Window::Get().Deinit(); //  Kill Window

	return result;
}