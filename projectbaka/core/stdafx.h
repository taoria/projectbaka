// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "../targetver.h"
#include<stdio.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#define baka_d2d
#ifdef baka_gdi //dx9 settings 
#include <d2d1.h>
#define BakaBitMap = Nothing
#else
#ifdef baka_dx12
#include <d3d11.h>
#define D3DCREATE = Direct3DCreate11(D3D_SDK_VERSION)
#else
#ifdef baka_d2d
#include "D2dPrerequisite.h"
#define BakaBitmap ID2D1Bitmap
#endif
#endif
#endif
#include<string.h>
#include <windows.h>
#include<map>



// TODO: reference additional headers your program requires here
