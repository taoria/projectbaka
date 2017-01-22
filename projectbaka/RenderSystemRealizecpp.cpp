#include"stdafx.h"
#include "bakamain.h"
#include "GlobalSystem.h"
#include "SpriteSystem.h"
#include "RenderSystem.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}
HRESULT Baka::LoadBitmapFromFile(
	LPCWSTR uri,
	ID2D1Bitmap **pBitmap){

	HRESULT hr=S_OK;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	//create a decoder
	hr = BakaWicFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);
	if (FAILED(hr)){
		Debug("警告", "解码器创建失败");
	} else{

	// Create the initial frame.
	hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (FAILED(hr)){
		Debug("警告", "帧数获取失败");
	}
	else{
		// Create the initial frame.
		hr = BakaWicFactory->CreateFormatConverter(&pConverter);
	}
	if (FAILED(hr))
	{
		Debug("警告", "格式转换器创建失败");
	}
	else{
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
	if (FAILED(hr)){
		Debug("警告", "转换器初始化失败");
	}
	else{
		hr = BakaRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			pBitmap
			);

	}if (FAILED(hr)){
		Debug("警告", "位图转换失败");
	}

	// create Bitmap


	//get bimap size
	return hr;
}
WorldPart::WorldPart()
{
	//Debug("test", "test");
	SIZE = -1;
}
WorldPart::~WorldPart()
{
	//Debug("test", "test");
	SIZE = -1;
}
bool BAKADLL abc = true;
bool Baka::Render()
{
	if (ThisBack->GetColor() == 0){
		RenderSpriteGlobal(ThisBack, 0,0);
	}
	for (int i = 0; i <= ThisWorld->SIZE; i++){ 
		RenderSprite(ThisCam, ThisWorld->RenderList[i]);
	}
	SpriteBase *s;
	for (int i = 0; i <= ThisGlobal->SIZE; i++){
		s = ThisGlobal->RenderList[i];
		RenderSpriteGlobal(s,s->realY, s->realY);
	}
	return true;
}
void Render::RenderThis() {
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase *sprite : (*iterator).second) {

		}
	}
}
void SpriteBase::RenderSelf() {

}
void SpriteBase::RenderSelf(RenderCamera camera) {

}