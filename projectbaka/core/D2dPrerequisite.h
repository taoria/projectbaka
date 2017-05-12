 //D2dPrerequisite.h
 #pragma once

//////////////////////////////////////////////////////////////////////////
 //Header files and lib files for Direct2D and DirectWrite
#include <wincodec.h>
//#include<d2d1_1helper.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
//////////////////////////////////////////////////////////////////////////
 //Helper template for resource releasing
 template<class Interface>
 inline void SafeRelease(Interface **ppInterfaceToRelease)
 {
	if (*ppInterfaceToRelease != NULL)
	 {
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
	}
}

 #ifndef Assert
 #if defined(DEBUG) || defined(_DEBUG)
 #define Assert(b) do { if (!(b)) { OutputDebugStringA("Assert: " #b "\n"); } } while (0 )
 #else
 #define Assert(b)
 #endif //DEBUG || _DEBUG
 #endif
 