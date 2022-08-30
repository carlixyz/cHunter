#ifndef UTIL_H
#define	UTIL_H

#ifdef _WIN32							// Windows Parsing
#include <windows.h>
#define GetMiliSeconds() timeGetTime()
#else
#include <sys/time.h>
float GetMiliSeconds() 
{
	timeval ltTime;
	gettimeofday(&ltTime, NULL);
	return ltTime.tv_usec / 1000.0f;
}
#endif



#ifdef _DEBUG
#include <sstream>
#include <fstream>
#include <iostream>

//#define DEBUG_ERR(x) (std::cerr << (x);)
//#define DEBUG_OUT(x) (std::cout << (x);)
#define DEBUG_FILE( NAME, x ) { std::ofstream os( NAME, std::ios::out | std::ios::app  ); os << x;  }
#define DEBUG_OUT( x ) {  std::ostringstream os; os << x; ::OutputDebugString(os.str().c_str()); }

#define DAY  __DATE__ << ", " << __TIME__ << " - "  
#define PLACE   __FILE__ << "(" << __LINE__ << ") "  
#define FIELD( x ) #x << " = [" << x << "]\n"

#define SET_COMP_NUM( NAME ) { int add;  std::ifstream inFile( NAME); inFile >> add; std::ofstream outFile( NAME, std::ios::trunc); outFile << ++add; }
inline int GetCompNum(std::string name) { int x; std::ifstream inFile(name); inFile >> x; return x; }
#define GET_COMP_NUM(NAME) GetCompNum(NAME)

#define MSG_BOX( x ) {MessageBox(NULL, x, "ERROR", MB_OK | MB_ICONSTOP);}

//... etc
#else 
//#define DEBUG_ERR(x)
//#define DEBUG_OUT(x)
#define DEBUG_FILE( NAME, x)
#define DEBUG_OUT( x )

#define DAY 
#define PLACE 
#define FIELD 

#define SET_COMP_NUM( NAME )
#define GET_COMP_NUM( NAME )

#define MSG_BOX( x )
//... etc
#endif










#endif // UTIL_H