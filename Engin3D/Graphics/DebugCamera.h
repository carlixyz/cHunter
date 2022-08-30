#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H

#include "Camera.h"


class DebugCamera : public  Camera // Developer´s Camera
{
public:
	 //void Init(); 
	 void Update(float lfTimestep);

private:
	cVec3 OldPos;
	cVec3 NewPos;

};
#endif 
