#define BAKADLL __declspec(dllexport)
#define MAX_TITLE_LENGTH  250
#define BakaMain()  __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
#define Debug(a,b) MessageBox(NULL,a,b,MB_OK)
#define Warning(a,b) MessageBox(NULL,b,a,MB_OK)
#define BAKA_DEBUG
#define GLOBAL_BLACK 233
#define GLOBAL_WHITE 234
#define GLOBAL_GREY 235
#define GLOBAL_IMAGE 237
#define GLOBAL_COLOR 233
#include <stdarg.h> 
#include "stdafx.h"
#ifdef BAKA_DEBUG
#define S_Debug(a) MessageBox(NULL,a,a,MB_OK)
#else
#define S_Debug(a,b) 
#endif
void BAKADLL DebugBox(const char *format, ...); 
BAKADLL void DebugInt(int);
#pragma once
#include "stdafx.h"
typedef CHAR B_CHAR;
typedef int B_STATEMACHINE;
typedef unsigned int b_id;
class Render;
class BackGround;
class BAKADLL SpriteBase;
class BAKADLL RenderMachine;
class BAKADLL BaseContainer;
class BAKADLL BaseObject;
class BAKADLL GameControl;
class BAKADLL TextureManager;
class BAKADLL Texture;
class BaseObject
{
private:
	b_id baseObjectId;
public:
	b_id ReturnHandleId() {
		return  baseObjectId;
	}
	void setId(b_id id) {
		baseObjectId = id;
	}
};
class BaseSystem
{
private:
	b_id baseSystemId;
public:
	b_id ReturnHandleId() {
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

class StateMachine
{
	int State;
};

class BAKADLL BakaEnvironment 
{
private:
#ifdef baka_d2d
	ID2D1Factory *bakaFactory = NULL; //directXFactory;
	ID2D1HwndRenderTarget* bakaRenderTarget = NULL;
	ID2D1SolidColorBrush* pBlackBrush = NULL;
	ID2D1BitmapBrush* bakaBitMapBrush = NULL;
	GameControl *bakaGameControl;
#endif
	RECT __windowRect;
	BakaBitmap *__BakaBitMap = NULL;
	bool RegisterBaka();
	bool SetDefaultSettings();
	TextureManager *textureManager;
public:
	int windowX; //position of windows
	int windowY;
	int width;
	int height;
	IWICImagingFactory *bakaWicFactory = NULL;
	WorldPart *thisWorld = NULL;
	RenderCamera *thisCam = NULL;
	BackGround *thisBack = NULL;
	Global *thisGlobal = NULL;
	HWND bakaHwnd = NULL;
	HICON bakaIcon = NULL;
	Render *render = NULL;
	HCURSOR bakaCursor = NULL;
	HINSTANCE bakaInstance = NULL;
	HBRUSH bakaHBrush = NULL;
	//basic information 
	B_CHAR title[250];
	B_CHAR classname[250];
	//绘制一个矩形
	void DrawARectAngle();
	//注册
	//
	void BeginDraw();
	void EndDraw();
	bool BakaStart();
	//virtual void BakaAddSrpite();
	int  SpriteLoadBitMap(PCWSTR  address, SpriteBase *s) {
		return 0;
	}
	bool RenderTexture(Texture *t,int x,int );
	bool RenderSprite(RenderCamera *a, SpriteBase *b);
	bool RenderSpriteGlobal(SpriteBase *b, int x, int y);
	bool Render();
	bool BakaCreateWindow();
	bool BakaSetControl(GameControl *g);


	//static baka *baka_test;
	BakaEnvironment(int, int, int, int);// the main construction allows users create windows
	BakaEnvironment(int, int, int, int, PCWSTR a);
	int SetBackGround(PCWSTR a);
	BakaEnvironment(int, int);
	void Init();

	TextureManager* getTextureManagerInstance();
	void SetGameController(GameControl *gameControl);
	LRESULT 	static CALLBACK BakaProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT LoadBitmapFromFile(PCWSTR uri,ID2D1Bitmap **ppBitmap);
};
