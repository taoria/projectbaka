#define BAKADLL __declspec(dllexport)
#define MAX_TITLE_LENGTH  250
#define BakaMain()  __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
#define Debug(a,b) MessageBox(NULL,a,b,MB_OK)
#define BAKA_DEBUG
//global color
#define GLOBAL_BLACK 233
#define GLOBAL_WHITE 234
#define GLOBAL_GREY 235
//state machine
#define GLOBAL_IMAGE 237
#define GLOBAL_COLOR 233
#ifdef BAKA_DEBUG
#define S_Debug(b,a) MessageBox(NULL,a,b,MB_OK)
#else
#define S_Debug(a,b) 
#endif
BAKADLL void DebugInt(int);
#pragma once
#include "stdafx.h"
typedef CHAR B_CHAR;
typedef int B_STATEMACHINE;
typedef int b_Handle;
class Render;

class BAKADLL SpriteBase;
class BackGround;
class RenderList;
class RenderTable;
class BAKADLL RenderMachine;
class BAKADLL BaseContainer;
class BAKADLL BaseObject;
class BaseObject
{
private:
	b_Handle baseObjectId;
public:
	b_Handle ReturnHandleId() {
		return  baseObjectId;
	}
	void setId(b_Handle id) {
		baseObjectId = id;
	}
};
class BaseSystem
{
private:
	b_Handle baseSystemId;
public:
	b_Handle ReturnHandleId() {
		return  baseSystemId;
	}
};

class  BAKADLL WorldPart
{
public:
	SpriteBase *RenderList[8192]; 
	int SIZE;
	WorldPart();
	~WorldPart();
	void AddRenderSprite(SpriteBase *s);

};
class BAKADLL Global;
class BAKADLL WorldBase {
public:
	int sizeX; //the size of world,which is indicated by 
	int sizeY;
	WorldPart *WorldPart; //beta下只有一个渲染模块
	WorldBase(int, int); //构造函数 done
	bool AddSprite(int x, int y, SpriteBase &s);//添加精灵 undo
};

class BAKADLL RenderCamera {
public:
	int camera_X; //摄像机中心
	int camera_Y;
	RenderCamera(int new_X, int new_Y) {
		camera_X = new_X;
		camera_Y = new_Y;
	}
};
class BAKADLL GameControl;
class StateMachine
{
	int State;
};
class BAKADLL BakaEnvironment // export this class,it's the interface to operate most functions 
{
private:
#ifdef baka_d2d
	ID2D1Factory *bakaFactory = NULL; //directXFactory;
	ID2D1HwndRenderTarget* bakaRenderTarget = NULL;
	ID2D1SolidColorBrush* pBlackBrush = NULL;
	ID2D1BitmapBrush* bakaBitMapBrush = NULL;
	GameControl *bakaGameControl;
#endif
	RECT windowRect;
	BakaBitmap *BakaBitMap = NULL;
	public:
	int windowX; //position of windows
	int windowY;
	int width;
	int height;
	IWICImagingFactory *bakaWicFactory = NULL;
	WorldPart *thisWorld;
	RenderCamera *thisCam;
	BackGround *thisBack;
	Global *thisGlobal;
	// handle to application
	HWND bakaHwnd; // the handle to a new baka application
	HICON bakaIcon;
	HCURSOR bakaCursor;
	HINSTANCE bakaInstance;
	HBRUSH bakaHBrush;
	//basic information 
	B_CHAR title[250];
	B_CHAR classname[250];
	//绘制一个矩形
	void DrawARectAngle();
	//注册
	//
	bool BakaStart();
	//virtual void BakaAddSrpite();
	int  SpriteLoadBitMap(PCWSTR  address, SpriteBase *s);
	bool RenderSprite(RenderCamera *a, SpriteBase *b);
	bool RenderSpriteGlobal(SpriteBase *b, int x, int y);
	bool BakaCreateWindow();
	bool BakaSetControl(GameControl *g);
	bool Render();
	LRESULT 	static CALLBACK BakaProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT LoadBitmapFromFile(
		PCWSTR uri,
		ID2D1Bitmap **ppBitmap
		);
	//static baka *baka_test;
	BakaEnvironment(int, int, int, int);// the main construction allows users create windows
	BakaEnvironment(int, int, int, int, PCWSTR a);
	int SetBackGround(PCWSTR a);
	BakaEnvironment(int, int);
private:
	bool RegisterBaka();
	bool SetDefaultSettings();
};
