#pragma once

#include "../Utility/Singleton.h"
#include "../Window/Window.h"
//#include "../Graphics/Camera.h"
#include "../Graphics/DebugCamera.h"

class Game : public Singleton<Game>
{

		bool finish = false;
		ApplicationProperties appProperties;

		DebugCamera camera3D;

	public:
		friend class Singleton<Game>;

		bool Init();
		void Update(float timeStep);

		void Render();
		bool Deinit();

		inline bool HasFinished() { return finish; }

	protected:
		Game() { ; } // Protected Constructor

};
