#include "DebugCamera.h"

//#include "../Game/InputConfiguration.h"
//#include "../Input/InputManager.h"

#define MOUSE_SPEED 0.0015f 

#define SPEED 2

//#include "../Utility/Debug.h"
#include <Windows.h>

//void DebugCamera::Init() 
//{
//
//	this->NewPos  = cVec3(0.0f, 0.0f, 0.0f);
//	this->OldPos = NewPos;
//	this->SetLookAt( cVec3(0.0f, 5.0f, -50.0f), cVec3(0.0f, 5.f, 0.f) );
//	// cameraUp by default is = cVec3(0.0f, 1.f, 0.f);
//}

void DebugCamera::Update(float timestep)
{
 // Process Some Input Here

	//up = GetAsyncKeyState(VK_UP);
	//down = GetAsyncKeyState(VK_DOWN);
	//left = GetAsyncKeyState(VK_LEFT);
	//right = GetAsyncKeyState(VK_RIGHT);

	//front = GetAsyncKeyState(0x57);		// W
	//back = GetAsyncKeyState(0x53);		// S
	//sideLeft = GetAsyncKeyState(0x41);	// A
	//sideRight = GetAsyncKeyState(0x44);	// D


	cVec3 pos = this->GetPosition();

	//if (front)
	if (GetAsyncKeyState(0x57))	// W		
		pos.z += timestep * SPEED;

	//if (back)
	if (GetAsyncKeyState(0x53))	// S
		pos.z -= timestep * SPEED;

	if (GetAsyncKeyState(0x41)) // A
		pos.x += timestep * SPEED;

	if (GetAsyncKeyState(0x44)) // D
		pos.x -= timestep * SPEED;

	View.SetPosition(pos);

	if (GetAsyncKeyState(VK_UP))
		SetPitch(-timestep);

	if (GetAsyncKeyState(VK_DOWN))
		SetPitch(timestep);

	if (GetAsyncKeyState(VK_RIGHT))
		SetYaw(timestep);

	if (GetAsyncKeyState(VK_LEFT))
		SetYaw(-timestep);


	/*
	if (IsPressed(eIA_CameraLeft))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.x +=0.1f;
		mView.SetPosition( lPos);
	}	

	if (IsPressed(eIA_CameraRight))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.x -=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraUp))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.y +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraDown))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.y -=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraUp))
	{
		cVec3 &lPos = this->GetPosition() ;
		lPos.y +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraFoward))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.z +=0.1f;
		mView.SetPosition( lPos);
	}

	if (IsPressed(eIA_CameraBack))
	{	
		cVec3 &lPos = this->GetPosition() ;
		lPos.z -=0.1f;
		mView.SetPosition( lPos);
	}
	//this->SetLookAt( this->cameraPositon, this->cameraTarget); 

	if (  GetValue( eIA_MouseYaw ) || GetValue( eIA_MousePitch ) ) // Mouse Rotation
		{	
			if (NewPos.IsZero()) // Check First pass
			{
				OldPos.y = GetValue( eIA_MousePitch  ) ;
				OldPos.y = GetValue( eIA_MousePitch  ) ;

				OldPos.x = GetValue( eIA_MouseYaw  ) ;
				NewPos.x = GetValue( eIA_MouseYaw  ) ;
			}
			else
			{
				OldPos.x = NewPos.x ;
				OldPos.y = NewPos.y ;

				NewPos.x = GetValue( eIA_MouseYaw  ) ;
				NewPos.y = GetValue( eIA_MousePitch  ) ;

				if (OldPos.x - NewPos.x)
					this->SetYaw( GetValue( eIA_MouseYaw  )* MOUSE_SPEED );
				
				if (OldPos.y - NewPos.y)
					this->SetPitch( GetValue( eIA_MousePitch  )* MOUSE_SPEED );
			}
//		this->SetPitch(GetValue( eIA_MouseMoved  )* -0.001);
		}

		*/

/* // get inside & Uncomment if you want to use keyboard keys for Pitch & Yaw
		if (IsPressed(eIA_CameraYawRight))
			this->SetYaw(0.01f);

		if (IsPressed(eIA_CameraYawLeft))
			this->SetYaw(-0.01f);

		if (IsPressed(eIA_CameraPitchUp))
			this->SetPitch(-0.01f);

		if (IsPressed(eIA_CameraPitchDown))
			this->SetPitch(0.01f);
*/		

	
}
