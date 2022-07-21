#pragma once
#include<DirectXMath.h>
#include<Windows.h>
#include <DirectXTex.h>
#include <tchar.h>



class WinApp {

public:
	// ウィンドウサイズ
	static const int kWindowWidth = 1280; // 横幅
	static const int kWindowHeight = 720; // 縦幅
	// ウィンドウクラス名
	static const wchar_t kWindowClassName[];

	enum class SizeChangeMode {
		kNone,        //!< サイズ変更不可
		kNormal,      //!< 自由変更
		kFixedAspect, //!< アスペクト比一定
	};

public://GetterSettter登録
	HWND GetHwnd() const { return hwnd_; }

	HINSTANCE GetHInstance() const { return wndClass_.hInstance; }
	

public://関数群
	void WinApiInitialize();

	static WinApp* GetInstance();

	void DebugOutputFormatString(const char* format, ...);
	static LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool ProcessMessage();
	void WinAppFinish();

private:
	WinApp();
	~WinApp();

private:
	

	WNDCLASSEX wndClass_{};
	RECT wrc;
	HWND hwnd_;
	MSG msg;
};