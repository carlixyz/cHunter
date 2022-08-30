#ifndef CAMERA_H
#define	CAMERA_H

//#include "../Utility/Singleton.h"
//#include "GLHeaders.h"
#include "../Libraries/MathLib/MathLib.h"
#include "../Window/AppProperties.h"

class Camera 
{


	inline void RefreshViewProj() { ViewProj = View * Proj; }

	public:

		void Init(ApplicationProperties properties);
		void SetLookAt(const cVec3 &position, 
						const cVec3 &target, 
						const cVec3 &up);
		inline void SetLookAt(const cVec3 &pos, const cVec3 &target)
		{	SetLookAt(pos, target, cVec3(1.0f, 1.0f, 1.0f));		}
		
		void SetYaw(float rad);
		void SetPitch(float rad);

		void SetOrtho(	float left, float right, 
						float bottom, float top,
						float ZNear, float ZFar);

		void SetPerspective(float FOVY_rad, float aspect,
							float ZNear, float ZFar);

		inline cVec3 GetFront() const { View.GetFront(); }
		inline cVec3 GetLeft() const { View.GetLeft(); }
		inline cVec3 GetRight() const { View.GetRight(); }
		inline cVec3 GetUp() const { View.GetUp(); }
		inline cVec3 GetPosition()	const { return View.GetPosition(); }

		inline const cMatrix &GetView() const { return View; }
		inline const cMatrix &GetProj() const { return Proj; }
		inline const cMatrix &GetViewProj() const { return ViewProj; }

	//protected:
	//	Camera() { ; }					// Protected Constructor
	protected:
		cMatrix View;
		cMatrix Proj;
		cMatrix ViewProj;
};

#endif	
