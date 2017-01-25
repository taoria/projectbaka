// projectbaka.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "stdafx.h"
#include "sprite.h"
#include "bakamain.h"
#include "global.h"
class BAKADLL BakaEnvironment;
using namespace D2D1;
SpriteBase *test;
BakaEnvironment* baka_test;
BakaEnvironment::BakaEnvironment(int x, int y,int wx,int wy){
	//set positions
	baka_test = this;
	windowX = x;
	windowY = y;
	width = wx;
	height = wy;
	thisWorld = new WorldPart();
	thisCam = new RenderCamera(0,0);
	thisBack = new BackGround(GLOBAL_WHITE);
	thisGlobal = new Global();
	//set default info
	SetDefaultSettings();
	//registerclass
	RegisterBaka();
	//createwindow;
	BakaCreateWindow();
//	BakaAddSrpite();
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&bakaWicFactory));
	if (FAILED(hr))
	{
		Debug("警告", "WIC工厂创建失败");
	}
	//DebugInt((int)baka_test);
}
int BakaEnvironment::SetBackGround(PCWSTR a){
	thisBack->color = 0;
	SpriteLoadBitMap(a, thisBack);
	return 0;
}
bool BakaEnvironment::BakaSetControl(GameControl *p){
	this->bakaGameControl = p;
	return false;
}
BakaEnvironment::BakaEnvironment(int x, int y, int wx, int wy, PCWSTR a){
	//set positions
	baka_test = this;
	windowX = x;
	windowY = y;
	width = wx;
	height = wy;
	thisWorld = new WorldPart();
	thisCam = new RenderCamera(0, 0);
	thisBack = new BackGround(GLOBAL_WHITE);
	thisGlobal = new Global();
	//set default info
	SetDefaultSettings();
	//registerclass
	RegisterBaka();
	//createwindow;
	BakaCreateWindow();
	//	BakaAddSrpite();
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&bakaWicFactory));
	if (FAILED(hr))
	{
		Debug("警告", "WIC工厂创建失败");
	}
	SetBackGround(a);
	//DebugInt((int)baka_test);
}
BakaEnvironment::BakaEnvironment(int x, int y){
	//set positions
	thisWorld = new WorldPart();
	thisCam = new RenderCamera(0, 0);
	windowX = x;
	windowY = y;
	//set default info
	SetDefaultSettings();
	//registerclass
	RegisterBaka();
	//createwindow;
	baka_test = this;
	BakaStart();


}
bool BakaEnvironment::RegisterBaka(){
	//initialize the informa of baka
	WNDCLASS Baka_Class;
	Baka_Class.style = 0;
	Baka_Class.cbClsExtra = 0;
	Baka_Class.cbWndExtra = 0;
	Baka_Class.hIcon = bakaIcon;
	Baka_Class.hCursor = bakaCursor;
	Baka_Class.hInstance = bakaInstance;
	Baka_Class.lpfnWndProc = BakaProc;
	Baka_Class.lpszMenuName = NULL;
	Baka_Class.lpszClassName = classname;
	Baka_Class.hbrBackground = bakaHBrush;
	if (RegisterClass(&Baka_Class))
	{
		//
		return true;
	}else{
		return false;
	}

}
//default settings 
bool BakaEnvironment::SetDefaultSettings(){
	bakaHBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	bakaCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	bakaIcon = LoadIcon(NULL, IDI_APPLICATION);
	strcpy_s(title , "一个默认的BAKA游戏");
	strcpy_s(classname, "default_class");
	return true;
}
//function that getting start windows
bool BakaEnvironment::BakaCreateWindow(){
	
	bakaHwnd = CreateWindow(classname, title, WS_POPUPWINDOW, windowX, windowY, width, height, NULL, NULL, bakaInstance, NULL);
	GetClientRect(bakaHwnd, &windowRect);
	LRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &bakaFactory);
	LRESULT hr2 = bakaFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(bakaHwnd, SizeU(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top)), &bakaRenderTarget);
	if (SUCCEEDED(hr2))
	{
		switch (thisBack->GetColor())
		{
		case GLOBAL_BLACK:
		{
			bakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Gold), &pBlackBrush);
			break;
		}
		case GLOBAL_WHITE:
		{
			bakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
			break;
		}
		case GLOBAL_IMAGE:
		{
			bakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
			break;
		}
		default:
		
			bakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
		}
	}
	return true;
}
bool BakaEnvironment::BakaStart(){
	ShowWindow(bakaHwnd, SW_SHOWNORMAL);
	UpdateWindow(bakaHwnd);
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
	//	DebugInt(ThisWorld->SIZE);
		//MessageBox(NULL, "hehe", "hehe", MB_OK);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
void BakaEnvironment::DrawARectAngle(){
    #ifdef baka_d2d
	
	bakaRenderTarget->BeginDraw();
	bakaRenderTarget->DrawRectangle(RectF(windowRect.left + 100.0f, windowRect.top + 100.0f, windowRect.right - 100.0f, windowRect.bottom - 100.0f), pBlackBrush);
	this->Render();
	//RenderSpriteGlobal(test, 200, 200);
	bakaRenderTarget->EndDraw();
	#endif
}
//this is main function run in the game
LRESULT CALLBACK BakaEnvironment::BakaProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	//HDC    hdc;

	//PAINTSTRUCT ps;

	//RECT     rect;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:{

		baka_test->DrawARectAngle();
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);

	}
	return 0;

}

bool BakaEnvironment::RenderSprite(RenderCamera *a, SpriteBase *b){

	int x = b->realX- a->camera_X; //the x that sprite to camera
	int y = b->realY - a->camera_Y; //the y that sprite to camera
	int CenterX = width / 2;
	int CenterY = height / 2;
	return  RenderSpriteGlobal(b,CenterX+x-(b->sizeX/2) ,CenterY-y-(b->sizeY/2) );
}

bool BakaEnvironment::RenderSpriteGlobal(SpriteBase *bb,int x,int y){
	BakaBitmap *bbMap = bb->GetBitmap();
	D2D1_SIZE_F size = bbMap->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(x, y);
	//draw bitmap
	bakaRenderTarget->DrawBitmap(
		bb->GetBitmap(),
		D2D1::RectF(
		upperLeftCorner.x,
		upperLeftCorner.y,
		upperLeftCorner.x + size.width,
		upperLeftCorner.y + size.height)
		);
		return false;
}
/*int BakaEnvironment::SpriteLoadBitMap(PCWSTR adress,SpriteBase *s){
	HRESULT h=NULL;
	if (!s->HaveBitMap)
	{

		IWICImagingFactory *pIWICFactory=NULL;
		h = LoadBitmapFromFile( adress, &s->GetBitmap());
		D2D1_SIZE_F size = s->SpriteBitmap->GetSize();
		s->sizeX = size.width;
		s->sizeY = size.height;
	}

	else
	{
		Debug("提示", "位图重复载入,请先清空原位图");
	}
	if (!SUCCEEDED(h))
	{
		Debug("错误", "位图载入失败");
	}
	return false;
}*/

//WorldBase:://
//**********//
//**********////**********////**********////**********////**********////**********////**********////**********////**********////**********////**********////**********////**********////**********////**********//
WorldBase::WorldBase(int x, int y){
	sizeX = x;
	sizeY = y;
}
bool WorldBase::AddSprite(int x, int y, SpriteBase &s){
	s.realX = x;
	s.realY = y;
	return true;
}
