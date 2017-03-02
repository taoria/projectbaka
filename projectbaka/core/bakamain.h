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
void BAKADLL DebugBox(const char* format, ...);
BAKADLL void DebugInt(int);
#pragma once
#include "stdafx.h"
#include "base_object.h"
#include "../algorithm/bmath.h"
typedef CHAR B_CHAR;
typedef int B_STATEMACHINE;
typedef unsigned int b_id;

class Render;
class BackGround;
class BAKADLL SpriteBase;
class BAKADLL RenderMachine;
class BAKADLL BaseContainer;
class BAKADLL EntityObjectBase;
class BAKADLL GameControl;
class BAKADLL TextureManager;
class BAKADLL Texture;
class BAKADLL ObjectBase;

/**
 * \brief Not used actually
 */
class EntityObjectBase : public ObjectBase {
private:
	b_id baseObjectId;
public:
	virtual ~EntityObjectBase();

	b_id ReturnHandleId() {
		return baseObjectId;
	}

	void setId(b_id id) {
		baseObjectId = id;
	}
};
/**
 * \brief not used  actually
 * 
 */
class BaseSystem : public ObjectBase {
private:
	b_id baseSystemId;
public:
	virtual ~BaseSystem() = default;
	b_id ReturnHandleId();
};
/**
 * \brief not yet completed and maybe will be deleted later
 */
class BAKADLL WorldPart : public ObjectBase {
public:
	SpriteBase* render_list[8192];
	int SIZE;
	WorldPart();
	virtual ~WorldPart();
	void AddRenderSprite(SpriteBase* s);

};
class BAKADLL Global;
/**
 * \brief 
 */
class BAKADLL WorldBase {
public:
	int sizeX; //the size of world,which is indicated by 
	int sizeY;

	WorldPart* WorldPart; //beta下只有一个渲染模块
	WorldBase(int, int); //构造函数 done
	bool AddSprite(int x, int y, SpriteBase& s);//添加精灵 undo
};
/**
 * \brief not yet completed ,as a camera，used by a render.
 */
class BAKADLL RenderCamera {
public:
	int camera_X; //摄像机中心
	int camera_Y;

	RenderCamera(int new_X, int new_Y) {
		camera_X = new_X;
		camera_Y = new_Y;
	}
};
/**
 * \brief not yet complete
 */
class StateMachine : public ObjectBase {
	int State;
};
/**
 * \brief baka environment ,which provide basic environment of render and logistics of the game.must be initialized in the begin of the game;
 */
class BAKADLL BakaEnvironment : public ObjectBase {
protected:
	float game_fps;
	~BakaEnvironment() = default;
private:
#ifdef baka_d2d
	ID2D1Factory* bakaFactory = nullptr; //directXFactory;
	ID2D1HwndRenderTarget* bakaRenderTarget = nullptr;
	ID2D1SolidColorBrush* pBlackBrush = nullptr;
	ID2D1BitmapBrush* bakaBitMapBrush = nullptr;
#endif
	RECT __windowRect;
	BakaBitmap* __BakaBitMap = nullptr;
	bool register_baka();
	bool set_default_settings();
	math::RIG* globalRandomGenerator;
public:
	int windowX; //position of windows
	int windowY;
	int width;
	int height;
	IWICImagingFactory* bakaWicFactory = nullptr;
	WorldPart* thisWorld = nullptr;
	RenderCamera* thisCam = nullptr;
	BackGround* thisBack = nullptr;
	Global* thisGlobal = nullptr;
	HWND bakaHwnd = nullptr;
	HICON bakaIcon = nullptr;
	void flush_windows();
	void draw_windwos();
	HCURSOR bakaCursor = nullptr;
	HINSTANCE bakaInstance = nullptr;
	HBRUSH bakaHBrush = nullptr;
	//basic information 
	B_CHAR title[250];
	B_CHAR classname[250];
	//绘制一个矩形
	void draw_a_rect_angle();
	void set_fps(float fps);
	void draw_begin();
	void draw_end();
	bool baka_start();
	//virtual void BakaAddSrpite();
	bool render_texture(Texture* t, int x, int);
	bool render_texture(Texture* texture, int x, int y, int resizeX, int resizeY);
	bool render_texture(Texture* texture, int x, int y, int resizeX, int resizeY, float rotation);
	bool render_sprite(RenderCamera* a, SpriteBase* b);
	bool render_sprite_global(SpriteBase* b, int x, int y);
	bool baka_create_window();
	bool refresh_window();
	bool baka_set_control(GameControl* g);
	BakaEnvironment(int, int, int, int);// the main construction allows users create windows
	BakaEnvironment(int, int, int, int, PCWSTR a);
	int set_back_ground(PCWSTR a);
	BakaEnvironment(int, int);
	TextureManager* get_texturemanager_instance();
	LRESULT static CALLBACK baka_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT load_bitmap(PCWSTR uri, ID2D1Bitmap** ppBitmap);
	//Closed
	float get_fixed_frames();

	int get_random_int(int min, int max);
};
