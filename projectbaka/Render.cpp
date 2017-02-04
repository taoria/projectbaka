#include"stdafx.h"
#include "bakamain.h"
#include "global.h"
#include "sprite.h"
#include "render_system.h"
void DebugInt(int x){
	char f[10];
	sprintf_s(f, "%d", x);
}
void Wchar_tToString(std::string& szDst, const wchar_t *wchar)
{
	const wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
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
		std::wstring str = L"Failed to create Decoder\n path:";
		str.append(uri);
		std::string result;
		Wchar_tToString(result, str.c_str());
		Warning("Warning",result.c_str());
		result.clear();
		str.clear();
	} else{

	// Create the initial frame.
	hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (FAILED(hr)){

	}
	else{
		// Create the initial frame.
		hr = bakaWicFactory->CreateFormatConverter(&pConverter);
	}
	if (FAILED(hr))
	{
		Debug("Warning", "格式转换器创建失败");
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
	//if (thisBack->GetColor() == 0){
	//	RenderSpriteGlobal(thisBack, 0,0);
	//}
	//for (int i = 0; i <= thisWorld->SIZE; i++){ 
	//	RenderSprite(thisCam, thisWorld->RenderList[i]);
	//}
	//SpriteBase *s;
	//for (int i = 0; i <= thisGlobal->SIZE; i++){
	//	s = thisGlobal->RenderList[i];
	//	RenderSpriteGlobal(s,s->realY, s->realY);
	//}
	return true;
}
void Render::RenderThis() {
}
Render::Render(BakaEnvironment *be) {
	this->be = be;
	be->render = this;
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
	this->be->BeginDraw();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
			be->RenderSprite(be->thisCam, sprite);
		}
	}
	this->be->EndDraw();
}
void FixedRender::RenderThis() {
	this->be->BeginDraw();
	for (auto iterator = renderGroup.begin(); iterator != renderGroup.end(); iterator++) {
		for (SpriteBase* sprite : (*iterator).second) {
		
			be->RenderSpriteGlobal(sprite, sprite->realX, sprite->realY);
		}
	}
	this->be->EndDraw();
}