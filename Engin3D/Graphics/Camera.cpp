//#include <assert.h>

//#include "../Utility/Utils.h"
#include "Camera.h"


void Camera::Init(ApplicationProperties properties)
{
	View.LoadIdentity();
	Proj.LoadIdentity();
	ViewProj.LoadIdentity();

	float aspect = (float)properties.Width / (float)properties.Height;
	SetPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void Camera::SetLookAt(	const cVec3 & position, 
						const cVec3 &target, 
						const cVec3 &up)
{
	View.LoadLookAt( position, target, up);
	RefreshViewProj();

}

void Camera::SetYaw(float rad)
{
	cMatrix lYaw;
	View *= lYaw.LoadRotation(View.GetUp(), rad);
}

void Camera::SetPitch(float rad)
{
	cMatrix lRot;
	View *= lRot.LoadRotation(cVec3(1.0f, 0.0f, 0.0f), rad);
}

void Camera::SetOrtho(	float left, float right, 
						float bottom, float top, 
						float ZNear, float ZFar	)
{
	Proj.LoadOrtho(left, right, bottom, top, ZNear, ZFar);
	RefreshViewProj();
}

void Camera::SetPerspective(	float FOVY_rad, float aspect, 
								float ZNear, float ZFar)
{
	Proj.LoadPerpective(FOVY_rad, aspect, ZNear, ZFar);
	RefreshViewProj();
}
