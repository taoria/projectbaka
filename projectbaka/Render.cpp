#include"stdafx.h"
#include "bakamain.h"
#include "global.h"
#include "sprite.h"
#include "render_system.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}
HRESULT BakaEnvironment::LoadBitmapFromFile(
	LPCWSTR uri,
	ID2D1Bitmap **pBitmap){
	HRESULT hr=S_OK;
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
		hr = bakaWicFactory->CreateFormatConverter(&pConverter);
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
		hr = bakaRenderTarget->CreateBitmapFromWicBitmap(
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
bool BakaEnvironment::Render()
{
	if (thisBack->GetColor() == 0){
		RenderSpriteGlobal(thisBack, 0,0);
	}
	for (int i = 0; i <= thisWorld->SIZE; i++){ 
		RenderSprite(thisCam, thisWorld->RenderList[i]);
	}
	SpriteBase *s;
	for (int i = 0; i <= thisGlobal->SIZE; i++){
		s = thisGlobal->RenderList[i];
		RenderSpriteGlobal(s,s->realY, s->realY);
	}
	return true;
}
void Render::RenderThis() {
}
Render::Render(BakaEnvironment *be) {
	this->be = be;
}
Render* Render::getRender(BakaEnvironment *be,int state) {
	switch (state) {
		case Render::STATE_ACTIVE: 
			return new SpriteRender(be);
	
		case Render::STATE_FIXED: 
			return new FixedRender(be);
		default:
			return new Render(be);
	}
}
void SpriteRender::RenderThis() {
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->RenderSprite(be->thisCam, sprite);
		}
	}
}
void FixedRender::RenderThis() {
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->RenderSpriteGlobal(sprite, sprite->realX, sprite->realY);
		}
	}
}