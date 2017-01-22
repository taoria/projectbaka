// projectbaka.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "stdafx.h"
#include "SpriteSystem.h"
#include "bakamain.h"
#include "GlobalSystem.h"
class BAKADLL Baka;
using namespace D2D1;
SpriteBase *test;
Baka* baka_test;
Baka::Baka(int x, int y,int wx,int wy){
	//set positions
	baka_test = this;
	windowX = x;
	windowY = y;
	width = wx;
	height = wy;
	ThisWorld = new WorldPart();
	ThisCam = new RenderCamera(0,0);
	ThisBack = new BackGround(GLOBAL_WHITE);
	ThisGlobal = new Global();
	//set default info
	SetDefaultSettings();
	//registerclass
	RegisterBaka();
	//createwindow;
	BakaCreateWindow();
//	BakaAddSrpite();
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&BakaWicFactory));
	if (FAILED(hr))
	{
		Debug("警告", "WIC工厂创建失败");
	}
	//DebugInt((int)baka_test);
}
int Baka::SetBackGround(PCWSTR a){
	ThisBack->color = 0;
	SpriteLoadBitMap(a, ThisBack);
	return 0;
}
bool Baka::BakaSetControl(GameControl *p){
	this->bakaGameControl = p;
	return false;
}
Baka::Baka(int x, int y, int wx, int wy, PCWSTR a){
	//set positions
	baka_test = this;
	windowX = x;
	windowY = y;
	width = wx;
	height = wy;
	ThisWorld = new WorldPart();
	ThisCam = new RenderCamera(0, 0);
	ThisBack = new BackGround(GLOBAL_WHITE);
	ThisGlobal = new Global();
	//set default info
	SetDefaultSettings();
	//registerclass
	RegisterBaka();
	//createwindow;
	BakaCreateWindow();
	//	BakaAddSrpite();
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&BakaWicFactory));
	if (FAILED(hr))
	{
		Debug("警告", "WIC工厂创建失败");
	}
	SetBackGround(a);
	//DebugInt((int)baka_test);
}
Baka::Baka(int x, int y){
	//set positions
	ThisWorld = new WorldPart();
	ThisCam = new RenderCamera(0, 0);
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
bool Baka::RegisterBaka(){
	//initialize the informa of baka
	WNDCLASS Baka_Class;
	Baka_Class.style = 0;
	Baka_Class.cbClsExtra = 0;
	Baka_Class.cbWndExtra = 0;
	Baka_Class.hIcon = Baka_Icon;
	Baka_Class.hCursor = Baka_Cursor;
	Baka_Class.hInstance = Baka_Instance;
	Baka_Class.lpfnWndProc = BakaProc;
	Baka_Class.lpszMenuName = NULL;
	Baka_Class.lpszClassName = classname;
	Baka_Class.hbrBackground = Baka_Hbrush;
	if (RegisterClass(&Baka_Class))
	{
		//
		return true;
	}else{
		return false;
	}

}
//default settings 
bool Baka::SetDefaultSettings(){
	Baka_Hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Baka_Cursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	Baka_Icon = LoadIcon(NULL, IDI_APPLICATION);
	strcpy_s(title , "一个默认的BAKA游戏");
	strcpy_s(classname, "default_class");
	return true;
}
//function that getting start windows
bool Baka::BakaCreateWindow(){
	
	Baka_Hwnd = CreateWindow(classname, title, WS_POPUPWINDOW, windowX, windowY, width, height, NULL, NULL, Baka_Instance, NULL);
	GetClientRect(Baka_Hwnd, &windowRect);
	LRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &BakaFactory);
	LRESULT hr2 = BakaFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(Baka_Hwnd, SizeU(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top)), &BakaRenderTarget);
	if (SUCCEEDED(hr2))
	{
		switch (ThisBack->GetColor())
		{
		case GLOBAL_BLACK:
		{
			BakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::Gold), &pBlackBrush);
			break;
		}
		case GLOBAL_WHITE:
		{
			BakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
			break;
		}
		case GLOBAL_IMAGE:
		{
			BakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
			break;
		}
		default:
		
			BakaRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &pBlackBrush);
		}
	}
	return true;
}
bool Baka::BakaStart(){
	ShowWindow(Baka_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(Baka_Hwnd);
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
void Baka::DrawARectAngle(){
    #ifdef baka_d2d
	
	BakaRenderTarget->BeginDraw();
	BakaRenderTarget->DrawRectangle(RectF(windowRect.left + 100.0f, windowRect.top + 100.0f, windowRect.right - 100.0f, windowRect.bottom - 100.0f), pBlackBrush);
	this->Render();
	//RenderSpriteGlobal(test, 200, 200);
	BakaRenderTarget->EndDraw();
	#endif
}
//this is main function run in the game
LRESULT CALLBACK Baka::BakaProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
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

bool Baka::RenderSprite(RenderCamera *a, SpriteBase *b){

	int x = b->realX- a->camera_X; //the x that sprite to camera
	int y = b->realY - a->camera_Y; //the y that sprite to camera
	int CenterX = width / 2;
	int CenterY = height / 2;
	return  RenderSpriteGlobal(b,CenterX+x-(b->sizeX/2) ,CenterY-y-(b->sizeY/2) );
}

bool Baka::RenderSpriteGlobal(SpriteBase *b,int x,int y){
	D2D1_SIZE_F size = b->SpriteBitmap->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(x, y);
	//draw bitmap
	BakaRenderTarget->DrawBitmap(
		b->SpriteBitmap,
		D2D1::RectF(
		upperLeftCorner.x,
		upperLeftCorner.y,
		upperLeftCorner.x + size.width,
		upperLeftCorner.y + size.height)
		);
		return false;
}
int Baka::SpriteLoadBitMap(PCWSTR adress,SpriteBase *s){
	HRESULT h=NULL;
	if (!s->HaveBitMap)
	{

		IWICImagingFactory *pIWICFactory=NULL;
		h = LoadBitmapFromFile( adress, &s->SpriteBitmap);
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
}

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
