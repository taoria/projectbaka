// projectbaka.cpp : Defines the exported functions for the DLL application.
#pragma once
#include "stdafx.h"
#include "sprite.h"
#include "core\bakamain.h"
#include "global.h"
#include "render_system.h"
#include "bakagame.h"
#include<vector>
#pragma warning(disable:4996)
class BAKADLL BakaEnvironment;
using namespace D2D1;
SpriteBase *test;
std::vector<BakaEnvironment*> environmentSet;

//*******************************GLOBAL FUNCTION******************************************************************************//



void DebugBox(const char *format, ...) { //A Debug Tools
	char buffer[233];
	va_list args;      
	va_start(args, format);
	vsprintf(buffer, format, args);  
	va_end(args);      
	S_Debug(buffer);
}
void Wchar_tToString(std::string& szDst, const wchar_t *wchar) //trans str
{
	const wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char *psText;  
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}









//******************************BAKA ENVI******************************************************************************//
BakaEnvironment::BakaEnvironment(int x, int y,int wx,int wy){
	//set positions
	environmentSet.push_back(this);
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
	environmentSet.push_back(this);
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
	environmentSet.push_back(this);
	//BakaStart();


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
	GetClientRect(bakaHwnd, &__windowRect);
	LRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &bakaFactory);
	LRESULT hr2 = bakaFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(bakaHwnd, SizeU(__windowRect.right - __windowRect.left, __windowRect.bottom - __windowRect.top)), &bakaRenderTarget);
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
void BakaEnvironment::BeginDraw()
{
	this->bakaRenderTarget->BeginDraw();
}
void BakaEnvironment::EndDraw()
{
	this->bakaRenderTarget->EndDraw();
}
bool BakaEnvironment::BakaStart(){
	this->bakaGameControl->DoBegin();
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
	bakaRenderTarget->DrawRectangle(RectF(__windowRect.left + 100.0f, __windowRect.top + 100.0f, __windowRect.right - 100.0f, __windowRect.bottom - 100.0f), pBlackBrush);
	this->Render();
	//RenderSpriteGlobal(test, 200, 200);
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
		for (BakaEnvironment *baka : environmentSet) {
			if (baka->render!=NULL) {
				baka->render->RenderThis();
			}
			else {
				Warning("ERROR", "No Render attach to Game");
				
			}
		}
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
bool BakaEnvironment::RenderTexture(Texture* texture, int x, int y) {

	BakaBitmap *bbMap = *(texture->GetBitmap());
	D2D1_SIZE_F size = bbMap->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(x, y);
	this->RenderTexture(texture, x, y, size.width, size.height);
	return false;
}
bool BakaEnvironment::RenderTexture(Texture* texture, int x, int y, int resizeX, int resizeY) {
	BakaBitmap *bbMap = *(texture->GetBitmap());
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(x, y);
	bakaRenderTarget->DrawBitmap(
		bbMap,
		D2D1::RectF(
			upperLeftCorner.x,
			upperLeftCorner.y,
			upperLeftCorner.x + resizeX,
			upperLeftCorner.y + resizeY)
	);
	return false;
}
bool BakaEnvironment::RenderTexture(Texture* texture, int x, int y, int resizeX, int resizeY,float rotation) {
	BakaBitmap *bbMap = *(texture->GetBitmap());
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(x, y);
	bakaRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(
			rotation,
			D2D1::Point2F(x+resizeX/2, y+resizeY/2))
	);
	bakaRenderTarget->DrawBitmap(
		bbMap,
		D2D1::RectF(
			upperLeftCorner.x,
			upperLeftCorner.y,
			upperLeftCorner.x + resizeX,
			upperLeftCorner.y + resizeY)
	);
	return false;
}
bool BakaEnvironment::RenderSpriteGlobal(SpriteBase *bb,int x,int y){
	if (bb->sizeX == -1)
		return RenderTexture(bb->spriteTex, x, y);
	else if(bb->GetRotation()==0.0f)
		return RenderTexture(bb->spriteTex, x, y, bb->sizeX, bb->sizeY);
	return RenderTexture(bb->spriteTex, x, y, bb->sizeX, bb->sizeY,bb->GetRotation());
}
HRESULT BakaEnvironment::LoadBitmapFromFile(PCWSTR uri,ID2D1Bitmap **pBitmap) {
	HRESULT hr = S_OK;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	//create a decoder
	hr = bakaWicFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (FAILED(hr)) {
		std::wstring str = L"Failed to create Decoder\n path:";
		str.append(uri);
		std::string result;
		Wchar_tToString(result, str.c_str());
		Warning("Warning", result.c_str());
		result.clear();
		str.clear();
	}
	else {

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (FAILED(hr)) {

	}
	else {
		// Create the initial frame.
		hr = bakaWicFactory->CreateFormatConverter(&pConverter);
	}
	if (FAILED(hr))
	{
		Debug("Warning", "格式转换器创建失败");
	}
	else {
		//Initialize Converter
		hr = pConverter->Initialize(
			pFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeCustom
		);

	}
	if (FAILED(hr)) {
		Debug("警告", "转换器初始化失败");
	}
	else {
		hr = bakaRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			pBitmap
		);

	}if (FAILED(hr)) {
		Debug("警告", "位图转换失败");
	}

	// create Bitmap


	//get bimap size
	return hr;
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
void BakaEnvironment::Init() {
	textureManager = new TextureManager(this);
}
TextureManager* BakaEnvironment::getTextureManagerInstance() {
	if (textureManager == NULL) {
		Debug("错误", "环境未初始化");
		return NULL;
	}
	return textureManager;
}

void BakaEnvironment::SetGameController(GameControl * gameControl){
	this->bakaGameControl = gameControl;
}
